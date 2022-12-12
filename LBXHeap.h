#pragma once
/*
�ṩ�󶥶ѡ�С���ѹ��ܣ�����1Ϊ�󶥶ѣ�0ΪС����
����Ҫ�������� <= �����
����RemoveTop�������봫��һ������dataֵ������ʹ���ڵ��Ϊ��ײ�ڵ㣨��0��infiniteϵ�У�
����root��ֵ��ͨ��GetRoot()�����õ��ڵ��ֶ��޸�
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
	bool pattern;//ģʽ��1Ϊ�󶥶ѣ�0ΪС����
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
			//�ִ�Ҷ
			return false;
		}
		bool staus = false;//����Ƿ�ı�
		if (node->rightChild == NULL) {
			//�ҽڵ�Ϊ�գ�ֻ����ڵ��
			if (CompareLessthan(node->data, node->leftChild->data)) {
				Exchange(node->data, node->leftChild->data);
				*bExchangeLeft = true;
				staus = true;
			}
		}
		else if (node->leftChild == NULL) {
			//��ڵ�Ϊ�գ�ֻ���ҽڵ��
			if (CompareLessthan(node->data, node->rightChild->data)) {
				Exchange(node->data, node->rightChild->data);
				*bExchangeLeft = false;
				staus = true;
			}
		}
		else {
			if (CompareLessthan(node->leftChild->data, node->rightChild->data)) {//�ҽڵ��
				if (CompareLessthan(node->data, node->rightChild->data)) {
					Exchange(node->data, node->rightChild->data);
					*bExchangeLeft = false;
					staus = true;
				}
			}
			else { //��ڵ��
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
		root = cur = cur_parent = NULL;//��̬�ĳ�ʼ����Ӧ������Ϊroot
		count = 0;
	}
	Node* GetRoot() { return root; }
	void Insert(Ele data) {
		count++;
		if (root == NULL) { //��������root
			root = new Node;
			root->data = data;
			root->parent = NULL;
			root->leftChild = NULL;
			root->rightChild = NULL;
			cur = root;
			cur_parent = root;
			return;
		}

		//����curλ���ṩ�����
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
				break;//�˳�ѭ��
			}
			//ͬ�����ƣ��������������
			if (cur_parent == root) {
				if (cur_parent->rightChild == NULL) {
					cur = cur_parent->rightChild;
					continue;
				}
				//�ִ���ڵ�������ֻ�ܿ����²�
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
				cur_parent = cur_parent->parent->rightChild;//parentΪ��ڵ�
				if (temp == cur_parent) {
					//parentΪ�ҽڵ㣬ͨ������·��(һֱѰ�Ҹ��ڵ�Sֱ��SΪ��һ�����ڵ����ڵ㣬Ȼ��S�л����ҽڵ㣬Ȼ������ͬ�����л�����)
					int step = 0;//�Ʋ�
					bool reachroot = false;
					while (cur_parent->leftChild != cur_parent) {
						cur_parent = cur_parent->parent;
						step++;
						if (cur_parent == root) {
							//��������������²�
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
			//�ִ�Ҷ
			return;
		}
		siftdown(node->leftChild);
		siftdown(node->rightChild);
		bool staus = true;//��־�Ƿ�ı�
		cur_parent = cur = node;
		while (staus)
		{
			if (cur == NULL) {
				//�ִ�Ҷ
				staus = false;
			}
			else {
				//����
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

