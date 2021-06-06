#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include <queue>
#include <set>
#include <map>
using namespace std;

//该文件是工具包文件，包括了各种方便计算的函数

//代表了 最终的中线有多少个点
extern int POINT_SUM;

enum orphan{ normal , to_many_angle ,type_2 , wire}; //针对不具有一般化的点的 特殊照顾手段
struct Point {
	int id;
	double x;
	double y;
	double angle;
	Point() {};
	Point(int _id, double _x, double _y) :id(_id), x(_x), y(_y),angle(0) {};
	bool operator==(Point& b){
		if (abs(this->x - b.x)<0.0000001 && abs(this->y - b.y)< 0.0000001) return true;
		else return false;
	}
};//该对象存储的结构是本程序所有平面点上的格式

//这是用于算法easy_route算法时的移动点数据结构
struct Mpoint
{
	Point cur;	//表示当前点坐标
	Point aim;	//表示下一个目标点
	Point end;
	double step;//表示步长
	bool finish;//表示已经移动到终点了，不能再继续移动了
	
	int cnt;//记录当前的aim在route中所在的位置
	vector<Point> route; //表示将要走的路径
	void move(double _step); //表示单次移动

	Mpoint(vector<Point> _route,double route_length) :route(_route) {
		this->cur = route[0];
		this->cnt = 1;
		this->aim = route[1];
		this->end = route.back();
		this->step = route_length / POINT_SUM;
		this->finish = false;
	}

};//该对象是可以移动的点对象，负责在两条路径上缓慢移动

//保存有地图的参数
struct Map_parameter {
	vector<Point> map; //地图点集
	vector<vector<int>> target; //记录地图的起点和终点
	vector<Point> route1; //这是从一侧到终点边的路径
	vector<Point> route2; //这是另一侧到终点边的路径
	vector<Point> d_angle; //记录夹角钝角的点
};

struct Fork_triangle {
	Point a; //这个就是那个钝角点
	Point b;
	Point c;
	Fork_triangle() {};
	Fork_triangle(Point _a, Point _b, Point _c) :a(_a), b(_b), c(_c) {};
};
class tool
{
public:
	tool();
	~tool();
	vector<Point> read_data(string name, vector<vector<int>>& target);
	
	vector<Point> read_guideline(string name);
	
	vector<Point> calculte(vector<Point> P, vector<vector<int>> target);
	//get_route 得到从初始边 到 终点的 点路径 
	
	void get_route(vector<vector<int>> target, vector<int>& r1, vector<int>& r2, int n);
	vector<Point> get_route(const vector<Point>& P,const vector<int>& r1);
	
	double get_rlength(const vector<Point>& route); //得到路径长度

	int estimate_point_sum(int x);  //预估所需要的大概点数

	double getangle(vector<Point>& P, int index); //得到每个点的角度
	
	vector<vector<int>> get_begin_end(const vector<Point>& P , orphan& situation); //得到终点与起点

	void output_route(string output_name,const vector<vector<Point>>& result); //将结果输出到文件夹

	double get_dis2(const Point& a, const Point& b);

	vector<Point> get_new_route(Map_parameter& M , vector<int> begin , vector<bool>& vis); 
	//该函数用于处理多岔路的情况，会返回每个起点到岔口的路径
	
	bool is_to_target(Point& x, vector<Point>& target); 
	//用于处理岔路的情况，判断有没有到达岔口
	
	vector<Fork_triangle> find_fork_triangle(Map_parameter& M);
	//用于处理寻找三岔路的情况

	vector<vector<Point>> find_normal_fork(Map_parameter & M);
	//用于寻找多岔路的岔口



	bool is_same_race(int a, int b , int n); //用来找分叉路口的三角形的，如果两个点距离很近，又不是同族点的话，就很容易找出来

	vector<Point> get_new_route(const Map_parameter& M, Point begin1, Point begin2, vector<bool>& vis,Point head);

	void remove_redundancy_point(vector<vector<Point>>& result);
	void handle_to_many_angle(vector<vector<Point>>& result);

	//以绝对长度为标准的去除短线条大法
	void curve_to_straight(vector<vector<Point>>& result , orphan situation);

	//以相对长度为标准的去除短线条大法
	void curve_to_straight_relatively(vector<vector<Point>>& result);

	void Interpolation(vector<Point>& P , vector<vector<int>>& target);

	void path_merge(vector<vector<Point>>& result);
};

