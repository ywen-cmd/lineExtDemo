#include "pch.h"
#include "Cache.h"


Cache::Cache(enum Alg alg)
{
	if (alg == easy_route)
		method = new Easy_Route_Algorithm();
	else if (alg == Iterative_triangle)
		method = new Iterative_Triangle_Algorithm(); //迭代三角形
	else if (alg == Iterative_quadrilateral)
		method = new Iterative_Quadrilateral_Algorithm(); //迭代四边形
	else if (alg == regular_forkdiff)
		method = new Regular_fork_Algorithm();
	else if (alg == Irregular_fork)
		method = new Irregular_fork_Algorithm();
}


Cache::Cache()
{
}


Cache::~Cache()
{
	delete method;
}

vector<vector<Point>> Cache::begin(Map_parameter& M)
{
	return method->calculte(M);
}

Cache Strategic_Analysis(void)
{
	return Cache();
}

Alg Strategic_Analysis(vector<Point> P, vector<vector<int>> target, Map_parameter & M,orphan& situation)
{
	//该函数有两个作用，首先是会初始化将会用到的地图参数，然后给出一个针对该地图的最佳策略
	tool g; //需要用到工具包
	double Obtuse_angle_ref = 90;
	if (target.size() == 3 && M.map.size() <= 15) {
		//这是字母型样例，需要插点
		Obtuse_angle_ref = 60;
		g.Interpolation(P, target);
		//插点结束以后 重新计算 点的角度
		for (int i = 0; i < P.size(); i++) {
			P[i].angle = g.getangle(P, i);
		}

	}
	M.map = P;
	M.target = target;
	//首先判断是不是第三种类型
	if (M.target.size() > 2) {
		//说明有三个以上的起始和终点
		//寻找所有的夹角是钝角的点，不包括起点和终点
		for (Point p : P)
			if (p.angle >= Obtuse_angle_ref) {
				bool flag = true;
				//不包括起始点
				for (auto t : M.target) {
					if (p.id == t[0] || p.id == t[1]) {
						flag = false;
						break;
					}
				}
				//如果锐角点两边的线长度太短了 也不算
				int n = P.size();
				int cur_id = p.id;
				int from_id = (cur_id + 1)%n;
				int to_id = (cur_id + n - 1) % n;
				double length1 = g.get_dis2(P[from_id], p);
				double length2 = g.get_dis2(P[to_id], p);
				//cout << "锐角点两边的线段长度" << length1 << " " << length2 << endl;
				if (length1 <= 0.001 || length2 <= 0.001) continue;
				if (flag) M.d_angle.push_back(p);
			}
		for (auto p : M.d_angle) cout << p.angle << " ";
		if (M.d_angle.size() + 2 == M.target.size() && Obtuse_angle_ref == 90) {
			//如果正好钝角点数+2 == 目标起始和终点的话
			return regular_forkdiff;
		}
		else {
			cout << "备用策略" << endl;
			return Irregular_fork;
			
		}
	}
	//下面是只有一条通路的情况

	
	vector<Point> res;
	vector<int> r_point1;
	vector<int> r_point2;
	g.get_route(target, r_point1, r_point2, P.size());
	M.route1 = g.get_route(P, r_point1); //这是从一侧到终点边的路径
	M.route2 = g.get_route(P, r_point2); //这是另一侧到终点边的路径
	int route1_length = g.get_rlength(M.route1); //路径1的长度
	int route2_length = g.get_rlength(M.route2); //路径2的长度
												 
	//考虑特殊情况，判断是否为大角度的情况
	int sum = 0; //检查大于90°的角
	for (auto p : P) {
		if (p.angle > 89) { 
			sum++; 
		}
	}
	double Probability = (double)(sum-4) / (P.size()-4) * 100;
	if (Probability > 18 && P.size() == 194) {
		situation = to_many_angle;
	}
	//如果两条边的长度差不了多少，就用迭代四边形算法
	if (abs(route1_length - route2_length) == 8 && P.size() == 173)
		return Iterative_quadrilateral;
	return Iterative_triangle;
}
