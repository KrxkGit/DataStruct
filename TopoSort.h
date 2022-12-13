#pragma once

#include<vector>
#include<queue>
using namespace std;
//warning: The class won't check if the input is valid, please check that on your own.
//Tip: Search based on row,(a,b)=1 means that a can reach b.



class KrxkGraph {
protected:
	int num_node;
	bool** AdArr;
	bool* mark;
	bool bDirected;
	vector<int>TopoResult;
public:
	KrxkGraph(int num_node, bool bDirected = false) { //默认为无向图模式
		this->num_node = num_node;
		this->bDirected = bDirected;
		if (num_node == 0) {
			AdArr = NULL;
		}
		else {
			AdArr = new bool*[num_node];
			mark = new bool[num_node];
			for (int i = 0; i < num_node; i++) {
				AdArr[i] = new bool[num_node];
			}

			for (int i = 0; i < num_node; i++) { //初始化邻接矩阵,标记矩阵，全置零
				mark[i] = false;
				for (int j = 0; j < num_node; j++) {
					AdArr[i][j] = false;
				}
			}
		}
	}
	~KrxkGraph() {
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
	void InsertEdge(int p1, int p2) {
		AdArr[p1][p2] = true;
		if (!bDirected) {
			AdArr[p2][p1] = true;
		}
	}
	void DeleteEdge(int p1, int p2) {
		AdArr[p1][p2] = false;
		if (!bDirected) {
			AdArr[p2][p1] = false;
		}
	}
	int queryInDegree(int p) {
		int degree = 0;
		for (int i = 0; i < num_node; i++) {
			if (i == p) {
				continue;
			}
			if (AdArr[i][p]) {
				degree++;
			}
		}
		return degree;
	}
	int queryOutDegree(int p) {
		int degree = 0;
		for (int i = 0; i < num_node; i++) {
			if (i == p) {
				continue;
			}
			if (AdArr[p][i]) {
				degree++;
			}
		}
		return degree;
	}
	int queryTotalDegree(int p) {
		int total = queryInDegree(p) + queryOutDegree(p);
		if (bDirected) {
			return total;
		}
		else {
			return total / 2;
		}
	}
	void TopoSort() { //拓扑排序
		int* InDegree = new int[num_node];
		int* OutDegree = new int[num_node];
		for (int i = 0; i < num_node; i++) {
			InDegree[i] = queryInDegree(i);
			OutDegree[i] = queryOutDegree(i);
		}
		queue<int>tempQueue;
		for (int startPos = 0; startPos < num_node; startPos++) {
			int tDegree = InDegree[startPos] + OutDegree[startPos];
			if (!bDirected) { //处理无向图
				tDegree /= 2;
			}
			if (tDegree <= 1) {
				TopoResult.push_back(startPos);
				tempQueue.push(startPos);
				mark[startPos] = true;
			}
		}
		for (int i = 0; i<num_node; i++) {
			if (InDegree[i] <= 0 && mark[i] == false) {
				tempQueue.push(i);
				TopoResult.push_back(i);
				mark[i] = true;
			}
		}
		for (; tempQueue.size()>0;) {
			int cur = tempQueue.front();
			tempQueue.pop();
			for (int i = 0; i < num_node; i++) {
				if (i == cur) {
					continue;
				}
				if (AdArr[cur][i]) {
					InDegree[i]--;
					if (InDegree[i] == 0 && mark[i] == false) {
						tempQueue.push(i);
						TopoResult.push_back(i);
						mark[i] = true;
					}
				}
			}
		}
	}
	void queryTopoResult(vector<int>& result) {
		result = TopoResult;
	}
};