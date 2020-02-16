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
	int size;        //记录当前有效元素
};

template <class T, size_t M = 3>
class BTree{
	typedef BTNode<T, M> Node;
public:
	//构造
	BTree()
		:root(nullptr){

	}
	//查找
	//Node *, int Find(..);    不可以一下子返回两个数
	//返回的两个值，一个表示要插入key所在节点，一个是这个数在不在，在的话返回位置，不在的话返回-1
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
		//插排
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


	//插入
	bool insert(T key){
		//空树：直接插入
		if (root == nullptr){
			root = new Node;
			root->date[0] = key;
			root->size = 1;
			return true;
		}
		//非空：     
		else{
			
				//1.找待插入节点在树中的位置
				auto res = Find(key);
				//已经有这个元素了
				if (res.second != -1){
					return false;
				}
				else{
					//2.插入元素
					Node *cur = res.first;
					Node *subNode = nullptr;
					while (1){
					InsertKey(cur, key, subNode);
					//3.看是否满足B树的性质
					if (cur->size != M){
						return true;
					}
					//4.不满足:分裂
					//4.1 建立新节点
					Node* newNode = new Node;
					//4.2 找中间节点
					int mid = M / 2;

					//4.3 将中间位置右侧的元素即元素的孩子向新节点进行搬移
					int index = 0;
					int i = mid + 1;
					for (; i < cur->size; i++){
						newNode->date[index] = cur->date[i];
						newNode->child[index] = cur->child[i];
						if (cur->child[index])
						cur->child[index]->parent = newNode;
						index++;
					}
					//多搬移一个
					newNode->child[index] = cur->child[i];
					if (cur->child[index])
					cur->child[index]->parent = newNode;
					newNode->size = index;
					//4.4 更新cur的有效元素
					cur->size = cur->size - index - 1;
					//4.3将cur的中间位置的元素插入双亲中
					//若无双亲,即分裂的是根
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
//遍历
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