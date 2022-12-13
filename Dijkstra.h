#pragma once

#include<vector>
#include"Union.h"
using namespace std;

//边权重为-1表示infinte.
class KrxkWeightGraph {
protected:
	int num_node;
	int** AdArr;
	bool* mark;
	vector<int>result;
public:
	KrxkWeightGraph(int num_node) {
		this->num_node = num_node;
		if (num_node == 0) {
			AdArr = NULL;
		}
		else {
			AdArr = new int*[num_node];
			mark = new bool[num_node];
			for (int i = 0; i < num_node; i++) {
				AdArr[i] = new int[num_node];
			}

			for (int i = 0; i < num_node; i++) { //初始化邻接矩阵,标记矩阵，全置零
				mark[i] = false;
				for (int j = 0; j < num_node; j++) {
					AdArr[i][j] = -1;
				}
			}
		}
	}
	~KrxkWeightGraph() {
		if (num_node == 0) {
			return;
		}
		else {
			for (int i = 0; i < num_node; i++) {
				delete[] AdArr[i];
			}
			delete[]AdArr;
		}
	}
	void InsertEdge(int p1, int p2, int weight) {
		AdArr[p1][p2] = weight;
		AdArr[p2][p1] = weight;
	}
	void DeleteEdge(int p1, int p2) {
		AdArr[p1][p2] = -1;
		AdArr[p2][p1] = -1;
	}
	int Dijkstra(int start, int end) {
		Union S(num_node);//S means joined.
		vector<int> nodeS;
		S.add(start, -1);
		nodeS.push_back(start);

		for (; S.findfather(end) != S.findfather(start);) {
			int tempPoint = -1;
			int tempWeight = -1;
			for (vector<int>::iterator it = nodeS.begin(); it != nodeS.end(); it++) {
				for (int i = 0; i < num_node; i++) {
					if (S.findfather(start) == S.findfather(i)) {
						continue;
					}
					if (tempWeight == -1 || (AdArr[*it][i] < tempWeight &&AdArr[*it][i] != -1)) {
						tempWeight = AdArr[*it][i];
						tempPoint = i;
					}
				}
			}
			nodeS.push_back(tempPoint);
			S.add(tempPoint, start);
		}
		//calculate the shortest path weight
		int totalweight = 0;
		for (vector<int>::iterator it = nodeS.begin(); true;) {
			int cur = *it;
			it++;
			if (it == nodeS.end()) {
				break;
			}
			totalweight += AdArr[cur][*it];
		}
		result = nodeS;//save the result
		return totalweight;
	}
	void query_result(vector<int>&query) { query = result; }
};