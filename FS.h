#pragma once
//This file include the algorithm of DFS and BFS.

#include<iostream>
#include<stack>
#include<queue>
using namespace std;


//warning: The class won't check if the input is valid, please check that on your own.
//Tip: Search based on row,(a,b)=1 means that a can reach b.

class KrxkGraph {
protected:
	int num_node;
	bool** AdArr;
	bool* mark;
public:
	KrxkGraph(int num_node) {
		this->num_node = num_node;
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
		AdArr[p2][p1] = true;
	}
	void DeleteEdge(int p1, int p2) {
		AdArr[p1][p2] = false;
		AdArr[p2][p1] = false;
	}
};


class KrxkDFSGraph :public KrxkGraph {
private:
	int startNode;
public:
	KrxkDFSGraph(int num_node, int startNode) :KrxkGraph(num_node) { this->startNode = startNode; };
	void DFS_Output();
};


class KrxkBFSGraph :public KrxkGraph {
private:
	int startNode;
public:
	KrxkBFSGraph(int num_node, int startNode) :KrxkGraph(num_node) { this->startNode = startNode; };
	void BFS_Output();
};

void KrxkDFSGraph::DFS_Output()
{
	stack<int> Krstack;
	int w = 0;
	Krstack.push(startNode);

	//Output
	cout << startNode << " ";
	w++;

	while (Krstack.size() > 0) {
		int cur = Krstack.top();
		mark[cur] = true;

		bool bStatus = false;//Init the status.
		for (int j = 0; j < num_node; j++) {
			if (mark[j] != true && AdArr[cur][j] == true) {
				Krstack.push(j);

				//Output
				cout << j;
				w++;
				if (w == num_node) {
					cout << endl;
				}
				else {
					cout << " ";
				}

				bStatus = true;//Indicate that the node has adjacency node
				break;//important
			}
		}

		if (!bStatus) { // Child don't exist.
			Krstack.pop();
		}
	}
}

void KrxkBFSGraph::BFS_Output()
{
	queue<int>Krqueue;
	int w = 0;
	Krqueue.push(startNode);
	while (Krqueue.size() > 0) {
		int cur = Krqueue.front();
		mark[cur] = true;
		Krqueue.pop();
		w++;

		//Output
		cout << cur;
		if (w == num_node) {
			cout << endl;
		}
		else {
			cout << " ";
		}

		for (int j = 0; j < num_node; j++) {
			if (mark[j] != true && AdArr[cur][j] == true) {
				mark[j] = true; //important
				Krqueue.push(j);
			}
		}
	}
}