#pragma once
#include "Algorithm.h"
enum Alg{easy_route, Iterative_triangle, Iterative_quadrilateral, regular_forkdiff, Irregular_fork};
class Cache
{
	//该结构体负责路径生成算法
	Algorithm *method;
public:
	Cache(enum Alg alg);
	Cache();
	~Cache();
	vector<vector<Point>> begin(Map_parameter& M);
};

Alg Strategic_Analysis(vector<Point> P, vector<vector<int>> target,Map_parameter& M,orphan& situation); //策略分析函数，顺便计算地图参数
