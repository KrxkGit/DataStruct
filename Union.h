#pragma once

//���ǵ�ͼ����ʹ��������ǽڵ㣬��ʹ�����ͱ�������ָ�롣
//�Ƴ��㷨��Ҫ�ƶ����飬���Ӷȸߣ�������ʹ�ã����ݲ��ṩ��
// ����Ϊ-1��ʾ����Ϊ�սڵ�
class Union { //���鼯&·��ѹ��
private:
	int* father;
	int* arr;
	int size;
public:
	Union(int size) {
		size += 1;//���ǵ�һ��ͼ������1��ʼ����arr[0]=father[0]=-1��Ȼ���λ��1��ʼ�������ݡ�
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