#pragma once

//考虑到图论中使用整数标记节点，故使用整型变量代替指针。
//移除算法需要移动数组，复杂度高，不建议使用，故暂不提供。
// 父亲为-1表示父亲为空节点
class Union { //并查集&路径压缩
private:
	int* father;
	int* arr;
	int size;
public:
	Union(int size) {
		size += 1;//考虑到一般图论中以1开始，设arr[0]=father[0]=-1，然后从位置1开始储存数据。
		this->size = size;
		arr = new int[size];
		father = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = father[i] = -1;
		}
	}
	~Union() {
		delete[]arr;
		delete[]father;
	}
	int findfather(int node) {
		if (father[node] == -1) {
			return node;
		}
		else {
			father[node] = findfather(father[node]);
			return father[node];
		}
	}

	int add(int node, int father) {


		arr[node] = node;
		this->father[node] = father;

		return 0;//success.
	}
	
	int* getarr() { return arr; }
	int* getfa() { return father; }
};