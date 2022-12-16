#pragma once

//存在bug：由于并查集存在一定程度的单向性，故算法结果可能出现部分环路。


#include<vector>
#include"Union.h"
#include"KrxkSort.h"
using namespace std;

class KrxkEdge { //提供比较运算符重载功能，用于排序
private:
	int p1;
	int p2;
	int weight;
public:
	bool operator<=(KrxkEdge& e) {
		if (this->weight <= e.weight) {
			return true;
		}
		return false;
	}
	bool operator>=(KrxkEdge& e) {
		if (this->weight >= e.weight) {
			return true;
		}
		return false;
	}
	void set(int p1, int p2, int weight) {
		this->p1 = p1;
		this->p2 = p2;
		this->weight = weight;
	}
	void get(int& p1, int& p2, int& weight) {
		p1 = this->p1;
		p2 = this->p2;
		weight = this->weight;
	}
};

//边权重为-1表示infinte.
class KrxkWeightGraph {
protected:
	int num_node;
	int** AdArr;
	bool* mark;
	int edgeCount;
	vector<KrxkEdge>result;
public:
	KrxkWeightGraph(int num_node) {
		this->num_node = num_node;
		this->edgeCount = 0;
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
		edgeCount++;
	}
	void DeleteEdge(int p1, int p2) {
		AdArr[p1][p2] = -1;
		AdArr[p2][p1] = -1;
		edgeCount--;
	}
	void Kruskal(int num_vertice=0) { //若传入num_vertice=0,使用num_node作为默认值
		result.clear();
		if (num_vertice == 0) {
			num_vertice = num_node;
		}
		KrxkEdge* edge = new KrxkEdge[edgeCount];
		int cur = 0;
		for (int i = 0; i < num_node; i++) {
			for (int j = i + 1; j < num_node; j++) {
				if (AdArr[i][j] != -1) {
					edge[cur].set(i, j, AdArr[i][j]);
					cur++;
				}
			}
		}
		//以下对边进行升序排序，可修改排序算法。
		KrxkSort<KrxkEdge>bs(edge, edgeCount);
		bs.quick_sort(true);

		Union un(edgeCount);
		int recount = 0;
		int p1, p2, weight;
		for (int i = 0; i < edgeCount; i++) {
			edge[i].get(p1, p2, weight);
			if (un.findfather(p1) != un.findfather(p2) || un.findfather(p1) == -1) {
				un.add(p2, p1);
				result.push_back(edge[i]);
				recount++;
			}
			if (recount >= num_vertice - 1) {
				break;
			}
		}
	}
	void query_result(vector<KrxkEdge>&query) { query = result; }
};