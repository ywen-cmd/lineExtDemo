#pragma once
#include "tool.h"
class Algorithm
{
public:
	virtual vector<vector<Point>> calculte(Map_parameter& M) = 0;
	Algorithm();
	~Algorithm();
};

class Easy_Route_Algorithm : public Algorithm{
public:
	vector<vector<Point>> calculte(Map_parameter& M);
};

class Iterative_Triangle_Algorithm : public Algorithm {
public:
	vector<vector<Point>> calculte(Map_parameter& M);
};

class Iterative_Quadrilateral_Algorithm : public Algorithm {
public:
	vector<vector<Point>> calculte(Map_parameter& M);
};

class Regular_fork_Algorithm : public Algorithm {
public:
	vector<vector<Point>> calculte(Map_parameter& M);
};

class Irregular_fork_Algorithm : public Algorithm {
public:
	vector<vector<Point>> calculte(Map_parameter& M);
};