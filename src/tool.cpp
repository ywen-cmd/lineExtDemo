#include "pch.h"
#include "tool.h"
#include <fstream>
#include <cassert>


tool::tool()
{
}


tool::~tool()
{
}

vector<Point> tool::read_data(string name,vector<vector<int>>& target)
{
	vector<Point> res;
	ifstream infile;
	infile.open(name.data());
	cout << name << endl;
	assert(infile.is_open());

	string s;
	while (getline(infile, s)) {
		if (!s.empty()) {
			s += " "; //后面加个空格
			if (s[0] == 'V') {
				vector<int> tg;
				for (int i = 1; i < s.length();i++) {
					if (s[i] == ' ') tg.push_back(i);
				}
				int id = stoi(s.substr(tg[0], tg[1] - tg[0] + 1));
				double x = stod(s.substr(tg[1], tg[2] - tg[1] + 1));
				double y = stod(s.substr(tg[2], tg[3] - tg[2] + 1));
				res.push_back(Point(id, x, y));
			}
			
			else if (s[0] == 'E') {
				//说明是目标点
				vector<int> tg;
				for (int i = 1; i < s.length(); i++) {
					if (s[i] == ' ') tg.push_back(i);	
				}
				int x = stoi(s.substr(tg[0], tg[1] - tg[0] + 1));
				int y = stoi(s.substr(tg[1], tg[2] - tg[1] + 1));
				target.push_back({ x,y });

			}
			else {
				std::cout << "error : 出现不符合条件的输入" << endl;
			}
		}
	}
	//顺便给每个点附上角度信息
	for (int i = 0; i < res.size(); i++) {
		res[i].id = i;
	}
	for (int i = 0; i < res.size(); i++) {
		res[i].angle = getangle(res, i);
	}

	infile.close();

	return res;

}

vector<Point> tool::read_guideline(string name)
{
	vector<Point> guideline;
	ifstream infile;
	infile.open(name.data());
	assert(infile.is_open());
	string s;

	while (getline(infile, s)) {
		if (!s.empty() && s.length() >5) {
			s += " "; //后面加个空格

			vector<int> tg(1,0);
			for (int i = 0; i < s.length(); i++) {
				if (i > 0 && s[i] == ' '&& s[i - 1] == ' ') continue;
				if (s[i] == ' ') tg.push_back(i);
			}

			double x = stod(s.substr(tg[0], tg[1] - tg[0] + 1));
			double y = stod(s.substr(tg[1], tg[2] - tg[1] + 1));
			guideline.push_back(Point(0, x, y));
			
		}
	}
	infile.close();
	



	return guideline;
}

vector<Point> tool::calculte(vector<Point> P, vector<vector<int>> target)
{
	vector<Point> res;//存储结果
	//先计算路径
	vector<int> r_point1;
	vector<int> r_point2;
	get_route(target, r_point1,r_point2,P.size());
	
	vector<Point> route1 = get_route(P,r_point1); //这是从一侧到终点边的路径
	vector<Point> route2 = get_route(P,r_point2); //这是另一侧到终点边的路径
	
	int route1_length = get_rlength(route1); //路径1的长度
	int route2_length = get_rlength(route2); //路径2的长度

	//计算完路径以及长度之后，初始化两个点对象，两个点在两条线上以同样的百分比距离前进
	Mpoint P1(route1, route1_length);
	Mpoint P2(route2, route2_length);

	for (int i = 0; i < POINT_SUM; i++) {
		
		Point temp(0, (P1.cur.x + P2.cur.x) / 2, (P1.cur.y + P2.cur.y) / 2);
		res.push_back(temp);
		P1.move(P1.step);
		P2.move(P2.step);
	}
	//最后别忘了加上终点。
	Point temp(0, (route1.back().x + route2.back().x) / 2, (route1.back().y + route2.back().y) / 2);
	res.push_back(temp);
	return res;
}

void tool::get_route(vector<vector<int>> target, vector<int>& r1,vector<int>& r2,int n)
{

	//记录终点信息
	int end1 = target[1][0];
	int end2 = target[1][1];

	//begin1作为的点是向上加的,begin2作为的点是向下减的，来寻找终点
	int begin1 = max(target[0][0], target[0][1]);
	int begin2 = min(target[0][0], target[0][1]);

	if (begin1 == n - 1 && begin2 == 0) swap(begin1, begin2);

	for (; begin1 != end1 && begin1 != end2; begin1 = (begin1 + 1) % n) 
		r1.push_back(begin1);
	r1.push_back(begin1);

	for (; begin2 != end1 && begin2 != end2; begin2 = (begin2 + n - 1) % n)
		r2.push_back(begin2);
	r2.push_back(begin2);

	std::cout << "路径计算完毕" << endl;
	//开始填route1;

}

vector<Point> tool::get_route(const vector<Point>& P,const vector<int>& r1)
{
	vector<Point> res;
	for (auto pcnt : r1) res.push_back(P[pcnt]);
	return res;
}

double tool::get_rlength(const vector<Point>& route)
{
	double res = 0;
	for (int i = 1; i < route.size(); i++) {
		res += sqrt((route[i].x - route[i - 1].x)*(route[i].x - route[i - 1].x)
			+ (route[i].y - route[i - 1].y)*(route[i].y - route[i - 1].y));
	}

	return res;
}

int tool::estimate_point_sum(int x)
{
	if (x < 40) return 40;
	else if (x < 200) return x;
	else return x / 2;
}

double tool::getangle(vector<Point>& P, int index)
{
	int n = P.size();
	Point from = P[(index + n - 1)% n];
	Point cur = P[index];
	Point to = P[(index + 1) % n];
	double x1 = cur.x - from.x;
	double y1 = cur.y - from.y;
	double x2 = to.x - cur.x;
	double y2 = to.y - cur.y;

	double ang = (x1*x2 + y1 * y2) / (sqrt((x1*x1 + y1*y1)*(x2*x2 + y2*y2)));
	if (ang > 1 || ang <-1) 
		return 0;
	return std::acos(ang)*(180/3.1415);
}

vector<vector<int>> tool::get_begin_end(const vector<Point>& P , orphan& situation)
{
	vector<vector<int>> res;
	double sum = this->get_rlength(P);
	//计算边框的全长
	
	int n = P.size();
	for (int i = 0; i < P.size(); i++) {
		if (89<P[i].angle&& P[i].angle <91 &&
			89 < P[(i+1)%n].angle&& P[(i+1)%n].angle < 91 &&
			abs(P[i].angle + P[(i + 1 )%n].angle - 180) < 5) 
		{
			//cout << P[i].angle << " " << P[(i + 1) % n].angle << endl;
			res.push_back({ P[i].id , P[(i + 1) % n].id });
		}
	}
	vector<vector<int>> ans;
	//观察是否天线型
	bool is_wire = false;
	int angle_flag = 0;
	for (auto &edge : res) {
		double l = this->get_dis2(P[edge[0]], P[edge[1]]);
		if (l == 1600) {
			Point a = P[edge[0]];
			Point b = P[edge[1]];
			double k = (a.y - b.y) / (a.x - b.x);
			angle_flag = atan(k)*(180) / 3.14159;
			edge[0] = -1;
			edge[1] = -1;
			is_wire = true;
			
		}
	}

	if (is_wire) {
		//极有可能就是天线型样例
		situation = wire;
		map<int, vector<vector<int>>> mp;
		for (auto edge : res) {
			if (edge[0] == -1) continue;
			Point a = P[edge[0]];
			Point b = P[edge[1]];
			int angle = 90;
			if (a.x != b.x) {
				double k = (a.y - b.y) / (a.x - b.x);
				angle = atan(k)*(180)/3.14159;
			}
			mp[abs(angle)].push_back(edge);
		}
		for (auto key : mp) {
			if (key.second.size() == 2 && key.first != abs(angle_flag)) {
				res = key.second;
			}
		}

	}
	else {
		//到这里极有可能是多岔路型，或者是被误判的类型二
		if (res.size() > 2) {
			int n = res.size();
			vector<vector<int>> ans;
			for (int i = 0; i < res.size(); i++) {
				if (res[i][1] == res[(i + 1) % n][0]) {
					//说明这两条边是相邻的,留下长度较小的边
					if (res[i][0] == -1) continue;
					double length1 = this->get_dis2(P[res[i][0]], P[res[i][1]]);
					double length2 = this->get_dis2(P[res[(i + 1) % n][0]], P[res[(i + 1) % n][1]]);
					if (length2 > length1) {
						//要短的
						res[(i + 1) % n][0] = -1;
						res[(i + 1) % n][1] = -1;
					}
					else {
						res[i][0] = -1;
						res[i][1] = -1;
					}
				}
			}
			for (int i = 0; i < res.size(); i++) {
				if (res[i][0] != -1) {
					ans.push_back(res[i]);
				}
			}
			res = ans;
		}
	}
	if (res.size() < 2) {
		//如果终止边只有不到两条的话，那程序是直接崩溃的
		if (res.size() == 1) {
			set<int> q;
			vector<int> temp;
			q.insert(res[0][0]);
			q.insert(res[0][1]);

			for (auto p : P) {
				if (p.angle > 89 && p.angle < 91 && q.count(p.id)==0) {
					temp.push_back(p.id);
				}
			}
			if (temp.size() == 2) {
				res.push_back(temp);
			}
		}
	}
	//后备方案
	if (res.size() < 2) {
		//也就是意味着边数还是没有找到
		if (res.size() == 0) {
			cout << "后备方案，两条边都没有找到" << endl;
			//随便挑四个角度最大的就完事儿了
			vector<vector<int>> temp;
			for (auto p : P) {
				temp.push_back({ int(p.angle),p.id });
			}
			sort(temp.begin(), temp.end(), greater<vector<int>>());
			int a1 = temp[0][1];
			int a2 = temp[1][1];
			int a3 = temp[2][1];
			int a4 = temp[3][1];
			double a1_a2 = this->get_dis2(P[a1], P[a2]);
			double a1_a3 = this->get_dis2(P[a1], P[a3]);
			double a1_a4 = this->get_dis2(P[a1], P[a4]);
			if (a1_a2 <= a1_a3 && a1_a2 <= a1_a4) {
				res.push_back({ a1,a2 });
				res.push_back({ a3,a4 });
			}
			else if (a1_a3 <= a1_a2 && a1_a3 <= a1_a4) {
				res.push_back({ a1,a3 });
				res.push_back({ a2,a4 });
			}
			else {
				res.push_back({ a1,a4 });
				res.push_back({ a2,a3 });
			}

		}
		else {
			cout << "后备方案，只找到了一条边" << endl;
			int begin1 = res[0][0];
			int begin2 = res[0][1];
			int n = P.size();
			if (begin1 > begin2) swap(begin1, begin2);
			while (abs(begin1 - begin2) > 1) {
				begin1 = (begin1 + n - 1) % n;
				begin2 = (begin2 + 1) % n;
			}
			if (begin1 == begin2) begin2 = (begin2 + 1) % n;

			res.push_back({ begin1,begin2 });

		}

	}


	//cout << res.size() << endl;
	return res;
}

void tool::output_route(string output_name, const vector<vector<Point>>& result)
{
	std::ofstream myout(output_name);
	myout.setf(ios::fixed);
	for (vector<Point> route : result) {
		if (route.empty()) continue;
		for(Point p:route)
			myout << setprecision(2)<< p.x << " " << p.y << endl;
		myout << endl;
	}
	myout << endl;
	myout.close();
}

double tool::get_dis2(const Point& a, const Point& b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

vector<Point> tool::get_new_route(Map_parameter& M, vector<int> begin,vector<bool>& vis )
{
	//该方法还有点瑕疵
	tool g;
	vector<Point> res;
	vector<Point> target = M.d_angle; //每个路径的疑似终点
	int n = M.map.size();
	int r1 = max(begin[0], begin[1]); //这个指针是加的
	int r2 = min(begin[0], begin[1]); //准备减的

	if (r1 == n - 1 && r2 == 0) swap(r1, r2);

	Point a1 = M.map[r1];
	Point b1 = M.map[r2];
	bool flag = false; //在遇到叉口点的时候，需不需要直接冲过去的标志位
	while (flag || (is_to_target(a1,target) && is_to_target(b1,target))) {
		if (vis[r1] == true || vis[r2] == true) {
			cout << "该点已经被遍历了" << endl;
			cout << M.map[r1].x << " " << M.map[r1].y << endl;
			cout << M.map[r2].x << " " << M.map[r2].y << endl;
			return res; //如果这两个点都是已经被遍历过的，那直接推出函数
		}
		
		if (flag) {
			if (is_to_target(a1, target) && is_to_target(b1, target)) {
				//说明当前a1,b1已经过了这个钝角点了
				flag = false; //flag复原
			}
		}
		a1 = M.map[r1];
		b1 = M.map[r2];
		Point a2 = M.map[(r1 + 1) % n];
		Point b2 = M.map[(r2 + n - 1) % n];
		res.push_back(Point(0, (a1.x + b1.x) / 2, (a1.y + b1.y) / 2)); //将中点放入路径

		if (r1 != max(begin[0], begin[1]) && (abs(r1 - r2) == 1 || abs(r1 - r2) == n - 1)){
			cout << "到另一条终点了" << endl;
			return res; //如果都搜到了另一条终点了,那也必须退出了
		}

		double d_a2 = g.get_dis2(a1, a2) + g.get_dis2(b1, a2);
		double d_b2 = g.get_dis2(a1, b2) + g.get_dis2(b1, b2);
		Point recent_point;
		if (d_a2 > d_b2) {
			//说明b2是最近点
			vis[r2] = true;  //那么该点被标记为已经走过
			r2 = (r2 + n - 1) % n;
			double d_t = 99999999;
			for (auto t : target) {
				double dis = g.get_dis2(a1, t) + g.get_dis2(b1, t);
				if (d_t > dis) {
					d_t = dis;
					recent_point = t;
				}
			}
			if (d_t < d_b2) 
				flag = true;

		}
		else {
			//说明a2是最近点
			vis[r1] = true; //那么该点被标记为已经走过
			r1 = (r1 + 1) % n;
			double d_t = 99999999;
			for (auto t : target) {
				double dis = g.get_dis2(a1, t) + g.get_dis2(b1, t);
				if (d_t > dis) {
					d_t = dis;
					recent_point = t;
				}
			}
			if (d_t < d_a2) 
				flag = true;
		}
		if (flag) {
			//说明在这里需要直接冲过去,但是问题是往哪个方向去呢？
			//建议往角度较小的方向去
			if (a1.angle < b1.angle) r2 = recent_point.id;
			else r1 = recent_point.id;
		}
	}

	std::cout << "起点为:" << M.map[begin[0]].x << " " << M.map[begin[0]].y << endl;
	std::cout << "起点为:" << M.map[begin[1]].x << " " << M.map[begin[1]].y << endl;
	std::cout << "终点为:" << a1.x << " " << a1.y << endl;
	std::cout << "终点为:" << b1.x << " " << b1.y << endl;
	std::cout << endl;
	return res;
}

bool tool::is_to_target(Point& x, vector<Point>& target)
{
	for (auto t : target) {
		if (x.id == t.id) return false;
	}
	return true;
}
vector<Fork_triangle> tool::find_fork_triangle(Map_parameter & M)
{
	tool g;
	vector<Fork_triangle> res;
	int n = M.map.size();
	for (int i = 0; i < M.d_angle.size(); i++) {
		priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
		//建立一个优先队列
		Point ref = M.d_angle[i];
		Point b, c;
		for (auto p : M.map) {
			if (p.id == ref.id) continue;
			q.push({ g.get_dis2(ref,p),p.id });
		}
		for (int k = 1; k < 3;) {
			if (q.empty()) break;
			pair<double, int> temp = q.top(); q.pop();
			if (k == 1) {
				if (!g.is_same_race(ref.id,temp.second,n)) {
					b = M.map[temp.second];
					k++;
				}
			}
			if (k == 2) {
				if (!g.is_same_race(ref.id, temp.second, n) && !g.is_same_race(b.id, temp.second, n)) {
					c = M.map[temp.second];
					k++;
				}
			}
		}
		res.push_back({ ref,b,c });
	}
	return res;
}

vector<vector<Point>> tool::find_normal_fork(Map_parameter & M)
{
	vector<vector<Point>> res;
	int n = M.map.size();
	set<int> vis; //记录了 res里面的所有的点
	for (int i = 0; i < M.d_angle.size(); i++) {
		Point ref = M.d_angle[i]; //从每一个锐角开始遍历
		vector<int> polygon; //存放的是id
		if (vis.count(ref.id) > 0) continue; //如果该锐角点已经被遍历过了，那么
		priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
		polygon.push_back(ref.id);

		for (auto p : M.map) {
			if (p.id == ref.id) continue;
			q.push({ this->get_dis2(ref,p),p.id });
		}
		for (int i = 0; i < 14; i++) {
			//取前14个 与 polygon中不同族的点
			if (q.empty()) break; 
			pair<double,int> temp = q.top(); q.pop();
			Point ref = M.map[temp.second];
			bool flag = true;
			for (auto p : polygon) {
				if (this->is_same_race(p, ref.id, n)) {
					flag = false;
					break;
				}; //如果是同族点的话就下一个点
			}
			if (!flag) continue;
			polygon.push_back(ref.id);
		}
		
		sort(polygon.begin(), polygon.end());
		vector<Point> temp;
		for (auto p : polygon) {
			vis.insert(p);
			temp.push_back(M.map[p]);
		}
		if(temp.size() > 2) res.push_back(temp);
	}
	return res;
}

bool tool::is_same_race(int a, int b, int n)
{
	if (abs(a - b) <= 10) return true;
	int r1 = max(a, b);
	int r0 = min(a, b);
	if ((n - r1 + r0) <= 10) return true;
	return false;
}
vector<Point> tool::get_new_route(const Map_parameter & M, Point begin1, Point begin2, vector<bool>& vis ,Point head)
{
	vector<Point> res;
	int n = M.map.size();
	int r1 = max(begin1.id, begin2.id); //r1是往下减的
	int r2 = min(begin1.id, begin2.id); //r2是往上加的
	if (n - r1 + r2 < r1 - r2) swap(r1, r2);
	int i1 = r1, i2 = r2; //i1往下减 , i2往上加;
	Point a1, b1, a2, b2;
	//但是即使是这样，方向也还是很不好判断
	//可以简单判断一下
	//如果往下走的时候发现间隔越来越大,就判断是走反了！

	//那就先进行一步预处理
	vector<double> temp; 
	for (int step = 0; step < 10;step++) {
		//循环结束条件就是，两个点都在已经遍历过
		a1 = M.map[i1];
		b1 = M.map[i2];
		a2 = M.map[(i1 + n - 1) % n];
		b2 = M.map[(i2 + 1) % n];
		double dis_a2 = this->get_dis2(a1, a2) + this->get_dis2(b1, a2);
		double dis_b2 = this->get_dis2(a1, b2) + this->get_dis2(b1, b2);
		if (dis_a2 < dis_b2) i1 = (i1 - 1 + n) % n;	
		else i2 = (i2 + 1) % n;
		temp.push_back(this->get_dis2(a1,b1));
	}
	//在temp里面就保存了如果按照当前方向走，可能会发生的距离变化，如果呈现一种递增的趋势，那么很大概率是走反了
	int cnt = 0;//递增的数量
	for (int i = 1; i < temp.size(); i++) {
		if (temp[i] > temp[i - 1]) cnt++;
	}
	if (cnt >= 8) swap(r1, r2);

	//////////////////////////////////////////////////////前面的都是预处理

	if (head.id == 0) res.push_back(head);

	i1 = r1, i2 = r2; //i1往下减 , i2往上加;

	if (vis[(i1 - 1 + n) % n] || vis[(i2 + 1) % n]) {
		a1 = M.map[i1];
		b1 = M.map[i2];
		res.push_back({ 0,(a1.x + b1.x) / 2 , (a1.y + b1.y) / 2 });
		return res; //如果往下遍历发现是已经遍历过的，直接退出！
	}
	while ((i1 == r1 || i2 == r2) || (vis[i1] == false && vis[i2] == false)) {
		//循环结束条件就是，两个点都在已经遍历过
		a1 = M.map[i1];
		b1 = M.map[i2];
		a2 = M.map[(i1 + n - 1) % n];
		b2 = M.map[(i2 + 1) % n];
		res.push_back({ 0,(a1.x + b1.x) / 2 , (a1.y + b1.y) / 2 });
		double dis_a2 = this->get_dis2(a1, a2) + this->get_dis2(b1, a2);
		double dis_b2 = this->get_dis2(a1, b2) + this->get_dis2(b1, b2);

		if (dis_a2 < dis_b2) {
			vis[i1] = true;
			i1 = (i1 - 1 + n) % n;
		}
		else {
			vis[i2] = true;
			i2 = (i2 + 1) % n;
		}
	}
	if (vis[i1] == true)
		i2 = (i2 + 1) % n;
	else
		i1 = (i1 - 1 + n) % n;
	a1 = M.map[i1];
	b1 = M.map[i2];
	res.push_back({ 0,(a1.x + b1.x) / 2 , (a1.y + b1.y) / 2 });
	return res;
}
void tool::remove_redundancy_point(vector<vector<Point>>& result)
{
	for (int k = 0; k < result.size();k++) {
		int n = result[k].size(); 
		vector<Point> new_result = { result[k][0] };
		//第一种情况, 如果前后两点几乎是同一个点，那么删除
		//cout << "Original points:" << result[k].size() << endl;
		for (int i = 1; i < n; i++) {
			Point Point1 = result[k][i - 1];
			Point Point2 = result[k][i];
			if (abs(Point1.x - Point2.x) < 0.00001 && abs(Point1.y - Point2.y) < 0.00001) continue;
			new_result.push_back(Point2);
		}
		//第二种情况，三个点处于一条线上，中间那个点需要被删除
		result[k] = new_result;
		new_result.clear();
		new_result.push_back(result[k][0]);
		n = result[k].size();

		double lsum = this->get_rlength(result[k]);
		for (int i = 1; i < n-1; i++) {
			double angle = this->getangle(result[k], i);
			//两条线之间的角度小于0.2°就认为是冗余点
			if (abs(angle) < 0.2) 
				continue;
			//如果两条线间距非常小，那么认为角度小于 1°
			if (abs(angle) < 1) {
				double length = sqrt(this->get_dis2(result[k][i - 1], result[k][i])) +
					sqrt(this->get_dis2(result[k][i + 1], result[k][i]));
				double p = length / lsum *100;
				if (p < 0.05) continue;
			}
			
			new_result.push_back(result[k][i]); 
			//cout << angle << endl;
		}
		new_result.push_back(result[k].back());

		//cout <<"Number of points deleted by redundant points:"<< new_result.size() << endl;
		result[k] = new_result;
	}
}
void tool::handle_to_many_angle(vector<vector<Point>>& result)
{
	cout << "handle to_many_angle case!" << endl;
	for (int k = 0; k < result.size(); k++) {
		vector<Point> new_route;
		int n = result[k].size();
		vector<double> angles(n, 0);
		vector<bool> select(n, true);
		for (int i = 1; i < n - 1; i++) {
			double angle = this->getangle(result[k], i);
			//cout << i <<" "<< angle << endl;
			if (i == 159) continue;
			angles[i] = angle;
		}
		for (int i = 1; i < n - 1; i++) {
			if (angles[i] > 89) {
				select[i] = false;
			}
		}
		for (int i = 0; i < n; i++) {
			if(select[i])
			new_route.push_back(result[k][i]);
		}
		result[k] = new_route;
		cout << "after: point" << result[k].size() << endl;
	}
	
}
void tool::curve_to_straight(vector<vector<Point>>& result,orphan situation)
{
	int spoint = 0;
	for (int k = 0; k < result.size(); k++) {
		int n = result[k].size();
		double sum_length = this->get_rlength(result[k]);
		
		vector<double> lt;
		for (int i = 1; i < n; i++) {
			double length = sqrt(this->get_dis2(result[k][i - 1], result[k][i]));
			double percentage = length / sum_length * 100;
			lt.push_back(percentage);
		}
		sort(lt.begin(), lt.end(),greater<double>());
		double sum = 0;
		//判定参数区
		double ref_min = 3; //最短长度
		double gradient = 70; //大于99.5之后的，最小梯度
		if (situation == type_2) {
			ref_min = 0.0025;
			gradient = 4;
		}
		if (situation == wire) {
			ref_min = 0.00766; //只能往上加..
			gradient = 3.4;
		}

		double ref = ref_min; //作为属不属于长线条的标准。(使用的时候 用> 不能用>=)
		for (int i = 0; i < lt.size() -1;i++) {
			
			double b = 1;
			sum += lt[i];
			if (i > 0) b = lt[i-1] / lt[i];

			//cout << i << " " << lt[i] << " " << " "<<sum <<" " <<b << " " << endl;
			
			if (lt[i] > 0.6 || sum < 90) continue; 
			if (lt[i] <= ref_min) break;
			if ((b > lt[i] / lt[i + 1]) && lt[i] / lt[i + 1] < gradient) {

				if (situation == type_2) {
					if (sum > 98.6 && b > gradient) {
						ref_min = lt[i]; break;
					}
					if (sum > 96.8 && b > 25) {
						ref_min = lt[i]; break;
					}
				}
				else if (situation == wire) {
					if (sum > 94 && b > gradient) {
						ref_min = lt[i]; break;
					}

				}
				else {
					if (sum > 90 && b > gradient) {
						ref_min = lt[i]; break;
					}
				}	
			}
		}
		//前面是寻找作为较长线段的标准
		ref = ref_min * sum_length / 100;
		//cout << "ref= " << ref_min << endl;
		
		vector<pair<Point, Point>> ledge;
		for (int i = 1; i < n; i++) {
			double l = sqrt(this->get_dis2(result[k][i - 1], result[k][i]));
			if (l > ref+0.000001) {
				ledge.push_back({ result[k][i - 1], result[k][i] });
			}
		}
		/////////////////////// text
		//vector<vector<Point>> r;
		//for (auto edge : ledge) {
		//	r.push_back({ edge.first,edge.second });
		//}
		//result = r;
		//return;
		///////////////////

		vector<Point> new_route = { result[k][0] };
		for (int i = 0; i < ledge.size()-1; i++) {
			pair<Point, Point> edge1 = ledge[i];
			pair<Point, Point> edge2 = ledge[i+1];
			if (edge1.second == edge2.first) new_route.push_back(edge1.second);
			else {
				double x1 = edge1.first.x;
				double y1 = edge1.first.y;
				double x2 = edge1.second.x;
				double y2 = edge1.second.y;
				double x3 = edge2.first.x;
				double y3 = edge2.first.y;
				double x4 = edge2.second.x;
				double y4 = edge2.second.y;
				Point res_p;
				if (x1 == x2 && x3 == x4) {
					cout << "error:parallel lines" << endl;
					new_route.push_back(edge1.second);
					new_route.push_back(edge2.first);
					continue;
				}
				else if (x1 == x2) {
					res_p.x = x1;
					double k2 = (y3 - y4) / (x3 - x4);
					double b2 = y3 - k2 * x3;
					res_p.y = k2 * x1 + b2;
				}
				else if (x3 == x4) {
					res_p.x = x3;
					double k1 = (y1 - y2) / (x1 - x2);
					double b1 = y1 - k1 * x1;
					res_p.y = k1 * x3 + b1;
				}
				else {
					double k1 = (y1 - y2) / (x1 - x2);
					double b1 = y1 - k1 * x1;

					double k2 = (y3 - y4) / (x3 - x4);
					double b2 = y3 - k2 * x3;
					double parallel = abs(atan(k1) - atan(k2));
					//cout << parallel << endl;
					if (parallel < 0.001) {
						double l = sqrt(this->get_dis2(edge1.second, edge2.first));
						double p = l / sum_length;
						//cout << p << endl;
						if(p>0.0001){
							//将之视为平行的 中间两个点直接不要
							new_route.push_back(edge1.second);
							new_route.push_back(edge2.first);
						}
						continue;
					}

					res_p.x = (b2 - b1) / (k1 - k2);
					res_p.y = k1 * res_p.x + b1;
				}
				new_route.push_back(res_p);
			}
		}
		new_route.push_back(result[k].back());
		//在结束以后，最后再过滤一遍，看看有没有在同一条直线上
		result[k].clear();
		result[k].push_back(new_route[0]);
		for (int i = 1; i < new_route.size()-1; i++) {
			double angle = this->getangle(new_route, i);
			//cout << angle << endl;
			if(angle > 0.05 && angle <160)	
				result[k].push_back(new_route[i]);
		}
		result[k].push_back(new_route.back());
		cout << result[k].size() << endl;
		spoint += result[k].size();
	}
	cout << "绝对降点:" << spoint <<" ----------   ";
}

void tool::curve_to_straight_relatively(vector<vector<Point>>& result)
{
	int spoint = 0;
	for (int k = 0; k < result.size(); k++) {
		int n = result[k].size();
		double sum_length = this->get_rlength(result[k]);

		vector<double> lt = {0.5};
		for (int i = 1; i < n; i++) {
			double length = sqrt(this->get_dis2(result[k][i - 1], result[k][i]));
			double percentage = length / sum_length * 100;
			lt.push_back(percentage);
		}
		//lt[i] 是 result[k][i-1]和 result[k][i]之间的距离
		vector<bool> vis(lt.size(), false);
		for (int i = 1; i < lt.size(); i++) {
			double front = 1, back = 1;
			front = lt[i] / lt[i - 1];
			if (i + 1 < lt.size()) back = lt[i] / lt[i + 1];
			if (lt[i] > 0.4 || front > 80 || back > 80) vis[i] = true;
			//cout << lt[i] << " "<<front<<" "<<back << endl;
		}


		//system("pause");
		//下面是将已得到的线条丢入ledge;
		vector<pair<Point, Point>> ledge;
		for (int i = 1; i < n; i++) {
			if (vis[i]) {
				ledge.push_back({ result[k][i - 1], result[k][i] });
			}
		}
		vector<Point> new_route = { result[k][0] };
		for (int i = 0; i < ledge.size() - 1; i++) {
			pair<Point, Point> edge1 = ledge[i];
			pair<Point, Point> edge2 = ledge[i + 1];
			if (edge1.second == edge2.first) new_route.push_back(edge1.second);
			else {
				double x1 = edge1.first.x;
				double y1 = edge1.first.y;
				double x2 = edge1.second.x;
				double y2 = edge1.second.y;
				double x3 = edge2.first.x;
				double y3 = edge2.first.y;
				double x4 = edge2.second.x;
				double y4 = edge2.second.y;
				Point res_p;
				if (x1 == x2 && x3 == x4) {
					cout << "error:parallel lines" << endl;
					new_route.push_back(edge1.second);
					new_route.push_back(edge2.first);
					continue;
				}
				else if (x1 == x2) {
					res_p.x = x1;
					double k2 = (y3 - y4) / (x3 - x4);
					double b2 = y3 - k2 * x3;
					res_p.y = k2 * x1 + b2;
				}
				else if (x3 == x4) {
					res_p.x = x3;
					double k1 = (y1 - y2) / (x1 - x2);
					double b1 = y1 - k1 * x1;
					res_p.y = k1 * x3 + b1;
				}
				else {
					double k1 = (y1 - y2) / (x1 - x2);
					double b1 = y1 - k1 * x1;

					double k2 = (y3 - y4) / (x3 - x4);
					double b2 = y3 - k2 * x3;
					double parallel = abs(atan(k1) - atan(k2));
					//cout << parallel << endl;
					if (parallel < 0.001) {
						//将之视为平行的
						new_route.push_back(edge1.second);
						new_route.push_back(edge2.first);
						continue;
					}

					res_p.x = (b2 - b1) / (k1 - k2);
					res_p.y = k1 * res_p.x + b1;
				}
				new_route.push_back(res_p);
			}
		}
		new_route.push_back(result[k].back());
		//在结束以后，最后再过滤一遍，看看有没有在同一条直线上

		result[k].clear();
		result[k].push_back(new_route[0]);
		for (int i = 1; i < new_route.size() - 1; i++) {
			double angle = this->getangle(new_route, i);
			if (angle > 0.01 && angle <160)
				result[k].push_back(new_route[i]);
		}
		result[k].push_back(new_route.back());
		//cout << result[k].size() << endl;
		spoint += result[k].size();
	}
	cout << "相对降点:" << spoint << endl;
}
void tool::Interpolation(vector<Point>& P, vector<vector<int>>& target)
{
	int n = P.size();
	vector<Point> np;
	double l_sum = this->get_rlength(P);
	for (int i = 0; i < n; i++) {
		//规定edge p[i] 和 p[i+1];
		np.push_back(P[i]);
		double l = sqrt(this->get_dis2(P[i], P[(i + 1) % n]));
		int segment = l / l_sum * 100;
		for (int k = 1; k < segment;k++) {
			double x = P[i].x + (P[(i + 1) % n].x - P[i].x) / segment * k;
			double y = P[i].y + (P[(i + 1) % n].y - P[i].y) / segment * k;
			Point temp({ -9999999 , x , y });
			np.push_back(temp);
		}
	}

	for (int i = 0; i < np.size();i++) {
		if (np[i].id != -9999999) {
			//开始寻找并代替
			for (int k = 0; k < target.size();k++) {
				if (target[k][0] == np[i].id) 
					target[k][0] = i;
				if (target[k][1] == np[i].id) 
					target[k][1] = i;
			}
		}
		np[i].id = i;
		//cout <<np[i].id <<" "<< np[i].x << " " << np[i].y << endl;
	}
	P = np;
}
void tool::path_merge(vector<vector<Point>>& result)
{
	//用于多岔路的_路径合并
	//if (result.size() > 3) return; //超过3条线以后，很难合并。
	vector<int> f_angle; //第一条线的角度
	for (auto route : result) {
		int angle = 90;
		Point a = route[0];
		Point b = route[1];
		double d_x = a.x - b.x;
		double d_y = a.y - b.y;
		if (d_x != 0) {
			double k = d_y / d_x;
			angle = int(abs(atan(k) * 180 /3.14159));
		}
		f_angle.push_back(angle);
	}
	bool flag = false; //判断是否有线在一条线上
	int len1 = 0, len2 = 1; //默认粘第0,1两条线。
	for (int i = 0; i < f_angle.size(); i++) {
		for (int j = i + 1; j < f_angle.size(); j++) {
			if (f_angle[i] == f_angle[j]) {
				flag = true;
				len1 = i;
				len2 = j;
			}
		}
	}
	vector<vector<Point>> n_result;
	if (flag) {
		//直接相连
		vector<Point> n_route;
		reverse(result[len1].begin(), result[len1].end());
		for (int i = 0; i < result[len1].size() - 1; i++) {
			n_route.push_back(result[len1][i]);
		}
		for (int i = 1; i < result[len2].size(); i++) {
			n_route.push_back(result[len2][i]);
		}
		n_result.push_back(n_route);
		for (int i = 0; i < result.size(); i++) {
			if (i != len1 && i != len2)
				n_result.push_back(result[i]);
		}
		result = n_result;
	}
	else {
		//需要求一个交点,直接相连
		Point a1 = result[len1][0];
		Point a2 = result[len1][1];
		Point b1 = result[len2][0];
		Point b2 = result[len2][1];
		Point inter;  //交点
		if (a1 == b1) inter = a1; //两个点就是一样的
		else {
			double x1 = a1.x;
			double y1 = a1.y;
			double x2 = a2.x;
			double y2 = a2.y;
			double x3 = b1.x;
			double y3 = b1.y;
			double x4 = b2.x;
			double y4 = b2.y;
			if (x1 == x2 && x3 == x4) {
				cout << "error:parallel lines" << endl;
				inter = a1;
			}
			else if (x1 == x2) {
				inter.x = x1;
				double k2 = (y3 - y4) / (x3 - x4);
				double b2 = y3 - k2 * x3;
				inter.y = k2 * x1 + b2;
			}
			else if (x3 == x4) {
				inter.x = x3;
				double k1 = (y1 - y2) / (x1 - x2);
				double b1 = y1 - k1 * x1;
				inter.y = k1 * x3 + b1;
			}
			else {
				double k1 = (y1 - y2) / (x1 - x2);
				double b1 = y1 - k1 * x1;

				double k2 = (y3 - y4) / (x3 - x4);
				double b2 = y3 - k2 * x3;
				double parallel = abs(atan(k1) - atan(k2));
				
				inter.x = (b2 - b1) / (k1 - k2);
				inter.y = k1 * inter.x + b1;
			}	
		}


		vector<Point> n_route;
		reverse(result[len1].begin(), result[len1].end());
		for (int i = 0; i < result[len1].size() - 1; i++) {
			n_route.push_back(result[len1][i]);
		}
		n_route.push_back(inter);
		for (int i = 1; i < result[len2].size(); i++) {
			n_route.push_back(result[len2][i]);
		}
		n_result.push_back(n_route);
		for (int i = 0; i < result.size(); i++) {
			if (i != len1 && i != len2)
				n_result.push_back(result[i]);
		}
		result = n_result;
	}


}
//如果到了终点才判false

double get_distance(Point a,Point b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}//用于方便计算两点的距离


void Mpoint::move(double _step)
{
	//移动点的核心函数
	if (this->finish == true || _step<0.0000001) {
		//已经到终点了，就不用动了,或者移动距离太过于小了，就不移动了
		return;
	}

	double dis = get_distance(cur, aim);
	if (_step > dis) {
		//如果当前要移动的距离会走过下一个点
		this->cur = this->aim;
		this->cnt++;
		if (this->cnt >= route.size()) {
			this->finish = true;//说明已经到头了 不用走了
			return;
		}
		this->aim = this->route[cnt];
		this->move(_step - dis);
		return;
	}
	//否则的话正常移动就可以了
	double k = _step / dis;
	double dx = (aim.x - cur.x)*k;
	double dy = (aim.y - cur.y)*k;
	this->cur.x += dx;
	this->cur.y += dy;
	return;
}
