#pragma once
/*������������
�ṩ��������ҹ��ܣ�ɾ�����ܴ�����
�������󲿷��㷨���Բ��õݹ鷽ʽʵ�֣����ݹ��㷨�������ڽṹ�ĶԳ��ԡ�
����ѭ���㷨�㼶���򵥣��Ҳ���Ҫ���Ǻ�����Ĵ������⣬�����㷨��ȡѭ������ݹ��㷨������ѭ����ʽʵ�ֵݹ顣
�������Ľ��������У��������ڶԳ��Թ�������Ҫ������̬�����ڵ㡢��ǰ�ڵ㡢�ӽڵ�ȣ���Ϣ��
Ӧ�ر�ע����ڵ�Ĵ�����û�и��ڵ㣨NULL�������ĳ�ʼ������
���ṹ���ᱣ��ԭʼ���ݣ���Ϊ�Ǳ�׼�������ͣ�����д�������캯����
����Ҫ�µĽṹ������д������غ���*/



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
protected://��¼��̬
	Node* cur;
	Node* cur_parent;
	int level;//�������
protected:
	Node* root;//���ڵ�
	int count;//�ڵ�����
public:
	Node* GetRoot() {
		return root;
	}
	LBXBSTree() {
		cur = cur_parent = root = NULL;
		count = 0;
	}
	int Insert(Ele data) {
		//��ʼ����̬
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
					root = cur;//��ֵ����
				}
				count++;
				break;//�ս�ѭ��
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
		return level;//���ؽ������
	}

	Node* Find(const Ele& data,int* pLevel) //�������ص�ǰ�ڵ�ָ�룬pLevel�������ڷ��ز�����ȡ�
	{
		cur_parent = cur = root;
		level = 0;
		for (; true;) {
			if (cur == NULL) {
				return NULL;//���ؿ�ֵ������ʧ��
			}
			if (data == cur->data) {
				if (pLevel != NULL) {
					*pLevel = level;//����
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

