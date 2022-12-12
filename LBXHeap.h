#pragma once
/*
提供大顶堆、小顶堆功能，其中1为大顶堆，0为小顶堆
若需要，请重载 <= 运算符
对于RemoveTop函数，请传入一个特殊data值，用于使顶节点成为最底层节点（如0或infinite系列）
设置root的值可通过GetRoot()函数得到节点手动修改
*/



template<typename Ele>
class LBXHeap
{
public:
	struct Node
	{
		Ele data;
		Node* parent;
		Node* leftChild;
		Node* rightChild;
	};
protected:
	Node* root;
	Node* cur;
	Node* cur_parent;
	int count;

protected:
	bool pattern;//模式，1为大顶堆，0为小顶堆
	bool CompareLessthan(Ele a, Ele b) {
		if (!pattern) {
			return a <= b;
		}
		else {
			return !(a <= b);
		}
	}
	void Exchange(Ele& a, Ele& b) {
		Ele temp = a;
		a = b;
		b = temp;
	}
	bool FindMaxChildAndChange(Node* node, bool* bExchangeLeft) {
		if (node->leftChild == NULL && node->rightChild==NULL) {
			//抵达叶
			return false;
		}
		bool staus = false;//标记是否改变
		if (node->rightChild == NULL) {
			//右节点为空，只能左节点大
			if (CompareLessthan(node->data, node->leftChild->data)) {
				Exchange(node->data, node->leftChild->data);
				*bExchangeLeft = true;
				staus = true;
			}
		}
		else if (node->leftChild == NULL) {
			//左节点为空，只能右节点大
			if (CompareLessthan(node->data, node->rightChild->data)) {
				Exchange(node->data, node->rightChild->data);
				*bExchangeLeft = false;
				staus = true;
			}
		}
		else {
			if (CompareLessthan(node->leftChild->data, node->rightChild->data)) {//右节点大
				if (CompareLessthan(node->data, node->rightChild->data)) {
					Exchange(node->data, node->rightChild->data);
					*bExchangeLeft = false;
					staus = true;
				}
			}
			else { //左节点大
				if (CompareLessthan(node->data, node->leftChild->data)) {
					Exchange(node->data, node->leftChild->data);
					*bExchangeLeft = true;
					staus = true;
				}
			}
		}
		return staus;
	}
public:
	LBXHeap(bool patBig) {
		pattern = !patBig;
		root = cur = cur_parent = NULL;//暂态的初始化都应该设置为root
		count = 0;
	}
	Node* GetRoot() { return root; }
	void Insert(Ele data) {
		count++;
		if (root == NULL) { //单独处理root
			root = new Node;
			root->data = data;
			root->parent = NULL;
			root->leftChild = NULL;
			root->rightChild = NULL;
			cur = root;
			cur_parent = root;
			return;
		}

		//根据cur位置提供插入点
		while (true) {
			if (cur == NULL) {
				cur = new Node;
				cur->data = data;
				cur->parent = cur_parent;
				cur->leftChild = cur->rightChild = NULL;
				if (cur_parent->leftChild == NULL) {
					cur_parent->leftChild = cur;
				}
				else {
					cur_parent->rightChild = cur;
				}
				break;//退出循环
			}
			//同层右移；若满则找最左点
			if (cur_parent == root) {
				if (cur_parent->rightChild == NULL) {
					cur = cur_parent->rightChild;
					continue;
				}
				//抵达根节点且满，只能开辟新层
				cur = cur_parent;
				while (cur != NULL) {
					cur_parent = cur;
					cur = cur->leftChild;
				}
			}
			if (cur_parent->leftChild == cur) {
				cur = cur_parent->rightChild;
			}
			else if (cur_parent->rightChild == cur) {
				Node* temp = cur_parent;
				cur_parent = cur_parent->parent->rightChild;//parent为左节点
				if (temp == cur_parent) {
					//parent为右节点，通过筝形路线(一直寻找父节点S直至S为上一级父节点的左节点，然后S切换到右节点，然后走相同步数切换回来)
					int step = 0;//计步
					bool reachroot = false;
					while (cur_parent->leftChild != cur_parent) {
						cur_parent = cur_parent->parent;
						step++;
						if (cur_parent == root) {
							//最右情况，开辟新层
							cur_parent = root;
							reachroot = true;
							break;
						}
					}
					if (reachroot) {
						continue;
					}
					cur_parent = cur_parent->parent->rightChild;
					while (step--) {
						cur_parent = cur_parent->leftChild;
					}
				}
				cur = cur_parent->leftChild;
			}

		}
	}

	void siftdown(Node* node) {
		if (node == NULL) {
			//抵达叶
			return;
		}
		siftdown(node->leftChild);
		siftdown(node->rightChild);
		bool staus = true;//标志是否改变
		cur_parent = cur = node;
		while (staus)
		{
			if (cur == NULL) {
				//抵达叶
				staus = false;
			}
			else {
				//交换
				bool bExchangeLeft;
				staus = FindMaxChildAndChange(cur, &bExchangeLeft);
				cur_parent = cur;
				if (bExchangeLeft) {
					cur_parent = cur;
					cur = cur->leftChild;
				}
				else {
					cur_parent = cur;
					cur = cur->rightChild;
				}
			}
		}

	}
	Ele RemoveTop(const Ele& special) {
		count--;
		Ele result = root->data;

		root->data = special;
		siftdown(root);

		cur = cur_parent->parent;
		if (cur != NULL) {
			if (cur->leftChild == cur_parent) {
				cur->leftChild = NULL;
			}
			else {
				cur->rightChild = NULL;
			}
		}
		delete cur_parent;
		return result;
	}
	bool IsEmpty() {
		return (count <= 0)? true : false;
	}
	int GetCount() {
		return count;
	}
	~LBXHeap() {}
};

