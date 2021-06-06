#include "pch.h"
#include "Algorithm.h"


Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

vector<vector<Point>> Easy_Route_Algorithm::calculte(Map_parameter& M)
{
	//作为最简单的一种计算中心线的模式，适合于简单对象，在工具包中就有简单的算法实现。
	tool g;
	vector<Point> P = M.map;
	vector<vector<int>> target = M.target;
	POINT_SUM = g.estimate_point_sum(P.size());
	vector<vector<Point>> route;
	route.push_back(g.calculte(P, target));
	return route;
}

vector<vector<Point>> Iterative_Triangle_Algorithm::calculte(Map_parameter& M)
{
	tool g;
	vector<Point> res;
	vector<vector<Point>> route;
	vector<Point> route1 = M.route1; //这是从一侧到终点边的路径
	vector<Point> route2 = M.route2; //这是另一侧到终点边的路径
	
	int rc1 = 0;
	int rc2 = 0;
	//结果中放入起点
	Point temp(0, (route1[0].x + route2[0].x) / 2, (route1[0].y + route2[0].y) / 2);
	res.push_back(temp);

	while (rc1+1 <route1.size() && rc2+1 < route2.size()) {
		Point a1 = route1[rc1];
		Point a2 = route1[rc1 + 1];
		Point b1 = route2[rc2];
		Point b2 = route2[rc2 + 1];
		double disa1_b2 = g.get_dis2(a1, b2);
		double disa2_b1 = g.get_dis2(a2, b1);
		if (disa1_b2 <= disa2_b1) {
			rc2++;
			Point temp(0, (a1.x + b2.x)/2 , (a1.y + b2.y)/2);
			res.push_back(temp);
		}
		else {
			rc1++;
			Point temp(0, (a2.x + b1.x) / 2, (a2.y + b1.y) / 2);
			res.push_back(temp);
		}
	}
	//结果中放入终点
	res.push_back(Point(0, (route1.back().x + route2.back().x) / 2, (route1.back().y + route2.back().y) / 2));
	route.push_back(res);
	return route;
}


vector<vector<Point>> Iterative_Quadrilateral_Algorithm::calculte(Map_parameter& M)
{	
	tool g; //需要用到工具包
	vector<Point> res;
	vector<vector<Point>> route;
	vector<Point> route1 = M.route1; //这是从一侧到终点边的路径
	vector<Point> route2 = M.route2; //这是另一侧到终点边的路径

	int rc1 = 0;
	int rc2 = 0;
	//结果中放入起点
	Point temp(0, (route1[0].x + route2[0].x) / 2, (route1[0].y + route2[0].y) / 2);
	res.push_back(temp);

	while (rc1 + 1 < route1.size() && rc2 + 1 < route2.size()) {
		Point a1 = route1[rc1];
		Point a2 = route1[rc1 + 1];
		Point b1 = route2[rc2];
		Point b2 = route2[rc2 + 1];
		double disa1_b2 = g.get_dis2(a1, b2);
		double disa2_b1 = g.get_dis2(a2, b1);
		double disa1_b1 = g.get_dis2(a1, b1);
		if (disa1_b1 <= disa1_b2*0.5 && disa1_b1 <= disa2_b1*0.5) {
			//当a1,b1特别近的时候，可以考虑取a1,b1的中点
			rc1++;
			rc2++;
			Point temp(0, (a1.x + b1.x) / 2, (a1.y + b1.y) / 2);
			res.push_back(temp);
		}
		else if (disa1_b2 <= disa2_b1) {
			rc2++;
			Point temp(0, (a1.x + b2.x) / 2, (a1.y + b2.y) / 2);
			res.push_back(temp);
		}
		else {
			rc1++;
			Point temp(0, (a2.x + b1.x) / 2, (a2.y + b1.y) / 2);
			res.push_back(temp);
		}
	}
	//结果中放入终点
	res.push_back(Point(0, (route1.back().x + route2.back().x) / 2, (route1.back().y + route2.back().y) / 2));
	route.push_back(res);
	return route;

}

vector<vector<Point>> Regular_fork_Algorithm::calculte(Map_parameter & M)
{
	tool g;
	int n = M.map.size();
	vector<vector<Point>> route; //记录了多条路径
	vector<bool> vis(n, false); //在vis中记录可能会停止的终点

	//找到所有的分叉三角形的
	vector<Fork_triangle> triangle = g.find_fork_triangle(M);
		
	for (auto t : M.target) {vis[t[0]] = true; vis[t[1]] = true;}
	for (auto t : triangle) {vis[t.a.id] = true; vis[t.b.id] = true; vis[t.c.id] = true;} //给所有的终点打好标记
	
	for (auto t: triangle) {
		//从三角形的每个边开始，找到另一个终点或者，另一个三角形
		Point head({ 0,(t.c.x + t.b.x) / 2,(t.c.y + t.b.y) / 2 });
		vector<Point> res = g.get_new_route(M, t.c, t.b, vis, head);
		if(res.size() > 2) route.push_back(res);
		res = g.get_new_route(M, t.a, t.c, vis, head);
		if (res.size() > 2) route.push_back(res);
		res = g.get_new_route(M, t.a, t.b, vis, head);
		if (res.size() > 2) route.push_back(res);
	}
	return route;
}

vector<vector<Point>> Irregular_fork_Algorithm::calculte(Map_parameter & M)
{
	tool g;
	int n = M.map.size();
	vector<vector<Point>> route; //记录了多条路径
	vector<bool> vis(n, false); //在vis中记录可能会停止的终点

	//找到所有的分叉多边形的
	vector<vector<Point>> polygons = g.find_normal_fork(M);


	for (auto t : M.target) { vis[t[0]] = true; vis[t[1]] = true; }
	for (auto polygon : polygons) {
		for (auto p : polygon) vis[p.id] = true;
	} //给所有的终点打好标记

	for (auto polygon : polygons) {
		//先求中点
		double x=0, y=0;
		int n = polygon.size();
		for (auto p : polygon) {
			x += p.x;
			y += p.y;
		}
		Point head({ 0,x / n , y / n });
		for (int i = 0; i < n; i++) {
			Point cur = polygon[i];
			Point next = polygon[(i + 1) % n];
			Point centre(0, (cur.x + next.x) / 2, (cur.y + next.y) / 2);

			route.push_back(g.get_new_route(M, cur, next, vis, centre));
		}
	}
	return route;
}
