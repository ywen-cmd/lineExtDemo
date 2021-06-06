// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#include <iostream>  
#include "tool.h"
#include "Cache.h"
#include<ctime>
using namespace std;
int POINT_SUM; //表示一次迭代准备找几个点


int main(int argc,char *argv[])
{	
	string input_name(argv[1]);
	string save_name = "./centerline";
	int index_ = 0;
	for (int i = input_name.size()-1; i >= 0; i--) if (input_name[i] == '_') { index_ = i; break; }
	string tail = input_name.substr(index_);


	string output_name = save_name + tail;
	cout<<output_name<<endl;
	//string guideline_name = "referline_"; //参考答案文件
	//guideline_name += tail;
		
		//linux
		//string input_name = "/home/routing_test/case/boundary_9.txt";
		//string output_name = "../resource/centerline_9";
		//string guideline_name = "/home/routing_test/case/referline_9.txt"; //参考答案文件


		tool g;     //用于算法实现的工具包
		vector<Point> P;  //该数组中记录了输入的点坐标
		vector<vector<int>> Target; //该数组中记录了起始和结束的两条边
		vector<vector<Point>> result; //该数组记录了中线的路径
		vector<Point> guideline; //参考答案
		orphan situation = normal;

		Map_parameter M;  //储存所有关于地图的参数，为了减少计算量，只计算一次并储存在里面

		P = g.read_data(input_name, Target); //从TXT文档中读取数据
		if (Target.empty()) {
			Target = g.get_begin_end(P, situation); //如果是没有给出起始和终点的话，就自己补上
			if(situation == normal && P.size()>9)
				situation = type_2; //并将这些样例标记为二号样例类型
		}

		//guideline = g.read_guideline(guideline_name); //如果有标准答案的话就把标准答案读入
		//cout << "Reference answer points:" << guideline.size() << endl;

		//首先判断用选择用何种策略,为了减少计算量，复用参数都记录在M中
		Alg strategy = Strategic_Analysis(P, Target, M, situation);
		cout << "Current strategy:" << strategy << endl;
		Cache cache(strategy); //根据策略生成相应的算法

		//然后计算路径
		result = cache.begin(M); //策略模式

		//去掉冗余点
		g.remove_redundancy_point(result); //该函数用于去除本来就处在一条直线上的点,或者重复的点
		if (situation == to_many_angle)
			g.handle_to_many_angle(result);  //处理某个孤儿样例用的,他是真正的孤儿！

		////曲线拟直
		if (strategy == regular_forkdiff || strategy == Irregular_fork) {
			//对于多岔路 只使用相对去点法
			g.curve_to_straight_relatively(result);
			//多岔路最终就要粘点
			g.path_merge(result);
			
		}else if (situation == wire) {
			//面对天线型样例 只使用觉得去点法
			g.curve_to_straight(result, situation); //绝对去点法更适合单一路线
		}else {
			vector<vector<Point>> result1 = result;
			g.curve_to_straight_relatively(result1); //相对
			g.curve_to_straight(result, situation); //绝对去点法更适合单一路线
			if (result1[0].size() * 1.5 < result[0].size()) {
				swap(result, result1);
				cout << "使用:相对去点法" << endl;
			}
			else {
				cout << "使用:绝对去点法" << endl;
			}
		}

		if (result.size() == 0) {
			cout << "error" << endl;
			system("pause");
		}
		cout << "最终点数" << result[0].size() << "---------------";
		cout << "参考点数" << guideline.size();
		if (result[0].size() > guideline.size()) cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!";
		cout << endl;
		////////////////////////////////////////////
		g.output_route(output_name, result); //保存结果
		//cout << "The program has finished running" << endl;

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
