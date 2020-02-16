#pragma once
#include <vector>
#include <iostream>
using namespace std;

template <class T,size_t M=3>
struct BTNode
{
	BTNode()
	:date(M)
	, child(M+1)
	, parent(nullptr)
	, size(0)
	{

	}
	//date
	vector<T> date;
	//child
	vector<BTNode<T, M> *> child;
	//parent
	BTNode<T, M> * parent;
	//size
	int size;        //��¼��ǰ��ЧԪ��
};

template <class T, size_t M = 3>
class BTree{
	typedef BTNode<T, M> Node;
public:
	//����
	BTree()
		:root(nullptr){

	}
	//����
	//Node *, int Find(..);    ������һ���ӷ���������
	//���ص�����ֵ��һ����ʾҪ����key���ڽڵ㣬һ����������ڲ��ڣ��ڵĻ�����λ�ã����ڵĻ�����-1
	pair<Node*, int> Find(const T &key){
		Node *pCur=root;
		Node *pParent = nullptr;
		while (pCur){
			int i = 0;
			for (i = 0; i < pCur->size; i++){
				if (key < pCur->date[i]){
					break;
				}
				else if (key == pCur->date[i]){
					return make_pair(pCur, i);
				}
			}
			pParent = pCur;
			pCur = pCur->child[i];
		}
		return make_pair(pParent, -1);

	}
	void InsertKey(Node *pnode, const T &key, Node *psub){
		//����
		for (int i = pnode->size; i > 0; i--){
			if (pnode->date[i - 1]<key){
				pnode->date[i] = key;
				pnode->child[i+1] = psub;
				break;
			}
			else{
				pnode->date[i] = pnode->date[i - 1];
				pnode->child[i+1] = pnode->child[i];
			}	
		}
		if (psub){
			psub->parent = pnode;
		}
		pnode->size++;
	}


	//����
	bool insert(T key){
		//������ֱ�Ӳ���
		if (root == nullptr){
			root = new Node;
			root->date[0] = key;
			root->size = 1;
			return true;
		}
		//�ǿգ�     
		else{
			
				//1.�Ҵ�����ڵ������е�λ��
				auto res = Find(key);
				//�Ѿ������Ԫ����
				if (res.second != -1){
					return false;
				}
				else{
					//2.����Ԫ��
					Node *cur = res.first;
					Node *subNode = nullptr;
					while (1){
					InsertKey(cur, key, subNode);
					//3.���Ƿ�����B��������
					if (cur->size != M){
						return true;
					}
					//4.������:����
					//4.1 �����½ڵ�
					Node* newNode = new Node;
					//4.2 ���м�ڵ�
					int mid = M / 2;

					//4.3 ���м�λ���Ҳ��Ԫ�ؼ�Ԫ�صĺ������½ڵ���а���
					int index = 0;
					int i = mid + 1;
					for (; i < cur->size; i++){
						newNode->date[index] = cur->date[i];
						newNode->child[index] = cur->child[i];
						if (cur->child[index])
						cur->child[index]->parent = newNode;
						index++;
					}
					//�����һ��
					newNode->child[index] = cur->child[i];
					if (cur->child[index])
					cur->child[index]->parent = newNode;
					newNode->size = index;
					//4.4 ����cur����ЧԪ��
					cur->size = cur->size - index - 1;
					//4.3��cur���м�λ�õ�Ԫ�ز���˫����
					//����˫��,�����ѵ��Ǹ�
					if (cur == root){
						root = new Node;
						root->date[0] = cur->date[mid];
						root->child[0] = cur;
						root->child[1] = newNode;
						root->size = 1;
						cur->parent = root;
						newNode->parent = root;
						
						return true;
					}
					else{
						key = cur->date[mid];
						cur = cur->parent;
						subNode = newNode;
					}
					

				}
			}
		}
		return false;
	}
//����
	void _inOrder(Node *root){
		if (root == nullptr){
			return;
		}
		for (int i = 0; i < root->size; i++){
			_inOrder(root->child[i]);
			cout << root->date[i]<<" ";

		}
		_inOrder(root->child[root->size]);
	}
	void inOrder(){
		_inOrder(root);
	}
private:
	Node *root;
};
void TestBtree(){
	int array[] = { 53, 139, 75, 49, 145, 36, 101 };
	BTree<int> t;
	for (auto e : array){
		t.insert(e);
	}
	t.inOrder();
}