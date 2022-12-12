#pragma once
/*二叉树查找树
提供插入与查找功能，删除功能待完善
二叉树大部分算法可以采用递归方式实现，但递归算法，依赖于结构的对称性。
由于循环算法层级更简单，且不需要考虑函数间的传递问题，部分算法采取循环代替递归算法。利用循环方式实现递归。
故在树的建立过程中，若不存在对称性规则，则需要利用暂态（父节点、当前节点、子节点等）信息。
应特别注意根节点的处理：根没有父节点（NULL）；根的初始化问题
树结构将会保存原始数据，若为非标准数据类型，请重写拷贝构造函数。
若需要新的结构，请重写覆盖相关函数*/



template<typename Ele>
class LBXBSTree
{
public:
	struct Node
	{
		Ele data;
		Node* parent;
		Node* leftChild;
		Node* rightChild;
	};
protected://记录暂态
	Node* cur;
	Node* cur_parent;
	int level;//进入深度
protected:
	Node* root;//根节点
	int count;//节点总数
public:
	Node* GetRoot() {
		return root;
	}
	LBXBSTree() {
		cur = cur_parent = root = NULL;
		count = 0;
	}
	int Insert(Ele data) {
		//初始化暂态
		cur_parent = cur = root;
		level = 0;

		for (;true;) {
			if (cur == NULL) {
				cur = new Node;
				cur->data = data;
				cur->parent = cur_parent;
				cur->leftChild = cur->rightChild = NULL;
				if (cur_parent != NULL) {
					if (data < cur_parent->data) {
						cur_parent->leftChild = cur;
					}
					else {
						cur_parent->rightChild = cur;
					}
				}
				if (root == NULL) {
					root = cur;//赋值给根
				}
				count++;
				break;//终结循环
			}
			else {
				if (data < cur->data) {
					cur_parent = cur;
					cur = cur->leftChild;
				}
				else {
					cur_parent = cur;
					cur = cur->rightChild;
				}
				level++;
			}
		}
		return level;//返回进入深度
	}

	Node* Find(const Ele& data,int* pLevel) //函数返回当前节点指针，pLevel参数用于返回查找深度。
	{
		cur_parent = cur = root;
		level = 0;
		for (; true;) {
			if (cur == NULL) {
				return NULL;//返回空值，查找失败
			}
			if (data == cur->data) {
				if (pLevel != NULL) {
					*pLevel = level;//返回
				}
				return cur;
			}
			else {
				if (data < cur->data) {
					cur_parent = cur;
					cur = cur->leftChild;
				}
				else {
					cur_parent = cur;
					cur = cur->rightChild;
				}
				level++;
			}
		}
		
	}
	~LBXBSTree() {}
};

