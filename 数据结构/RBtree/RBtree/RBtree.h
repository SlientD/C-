#pragma once
#include <iostream>
using namespace std;
enum Color{RED,BLACK};

template <class T>
struct RBtreeNode
{
	RBtreeNode(T val = T(), Color col = RED)
	:_val(val)
	, _col(col)
	, _parent(nullptr)
	, _left(nullptr)
	, _right(nullptr)
	{

	}
	T _val;
	Color _col;
	RBtreeNode *_parent;
	RBtreeNode *_left;
	RBtreeNode *_right;
};

template <class T>
class RBtree{
	typedef RBtreeNode<T> Node;
public:
	RBtree(){
		_phead = new Node;
		_phead->_left = _phead;
		_phead->_right = _phead;
		_size = 0;
	}
	bool insert(const T &data){
		Node* pRoot = getRoot();
		//����
		if (nullptr == pRoot){
			pRoot = new Node(data, BLACK);
			
			pRoot->_parent = _phead;

			_phead->_left = pRoot;
			_phead->_right = pRoot;
			_phead->_parent = pRoot;
			_size++;
			return true;
			
		}

		//�ǿգ����չ������
		Node *pCur = pRoot;
		Node *pParent = nullptr;
		while (pCur){
			pParent = pCur;
			if (data > pCur->_val){
				
				pCur = pCur->_right;
			}
			else if (data < pCur->_val){
				pCur = pCur->_left;
			}
			else{
				//data�Ѵ���
				return false;
			}
		}
		pCur = new Node(data);
		if (data < pParent->_val){
			pParent->_left = pCur;
		}
		else{
			pParent->_right = pCur;
		}
		pCur->_parent = pParent;

		//����Ƿ�Υ�������������--��ɫ���ܰ���
		//�½ڵ��Ĭ����ɫ�Ǻ�ɫ������½ڵ��˫����ɫ�Ǻ�ɫ����ôΥ���˺����������
		//��Ҫ�Ժ�������е���
		while (pParent!=_phead&&RED == pParent->_col){
			Node *grandFather = pParent->_parent;
			if (pParent == grandFather->_left)
			{
				Node *uncle = grandFather->_right;
				if (uncle&&RED == uncle->_col){
					pParent->_col = BLACK;
					uncle->_col = BLACK;
					grandFather->_col = RED;

					//grandFater������˫�ף�����Ҫ�������Ͽ�
					pCur = grandFather;
					pParent = grandFather->_parent;
				}

				else{
					//���pcur��parent���Ҳ࣬�����parentΪpcur���ڵ������������������,���pcur��parent���������
					if (pParent->_right == pCur){
						RotateLeft(pParent);
						swap(pParent, pCur);
					}
					//pcur��parent����࣬�򲻴���uncle����������ǽ�˫�ױ�ڣ��游��죬���游�����ҵ����Ϳɽ������
					pParent->_col = BLACK;
					grandFather->_col = RED;
					RotateRight(grandFather);
				}
				
			}
			else if (pParent == grandFather->_right){
				Node *uncle = grandFather->_left;
				if (uncle&&RED == uncle->_col){
					pParent->_col = BLACK;
					uncle->_col = BLACK;
					grandFather->_col = RED;

					//grandFater������˫�ף�����Ҫ�������Ͽ�
					pCur = grandFather;
					pParent = grandFather->_parent;
				}

				else{
					//���pcur��parent����࣬�����parentΪpcur���ڵ�����������ҵ�������,���pcur��parent���Ҳ�����
					if (pParent->_left == pCur){
						RotateRight(pParent);
						swap(pParent, pCur);
					}
					//pcur��parent���Ҳ࣬�򲻴���uncle����������ǽ�˫�ױ�ڣ��游��죬���游���������Ϳɽ������
					pParent->_col = BLACK;
					grandFather->_col = RED;
					RotateLeft(grandFather);
				}

			}
		}
		_phead->_parent->_col = BLACK;
		//���˫���Ǻ�ɫ��Υ��

		//����ͷ��������ָ��
		_phead->_left = LeftMost();
		_phead->_right = RightMost();
		_size++;
		return  true;
	}
	Node*& getRoot(){
		return _phead->_parent;
	}
	bool isVaildRBTree(){
		Node *pRoot = getRoot();
		//����Ҳ�Ǻ����
		if (nullptr == pRoot)
			return true;

		//���ǿ�

		//�������1�����ڵ��Ǻ�ɫ��
		if (BLACK != pRoot->_col){
			cout << "���ڵ��Ǻ�ɫ�ģ������ڵ�Ӧ���Ǻ�ɫ�����Բ��Ǻ��������" << endl;
			return false;
		}

		//�������2��ÿ��·���к�ɫ����������Ҫ��ͬ
		//�Ӹ��ڵ������������ĩ֦�Ľ����������ͬ��ôÿ����֧�ϵ����ߵĽ��Ҳһ����ͬ
		//��Ϊ���һ���ڵ����ߵĺ�ɫ���߲�ͬ�����������϶���������֧������ͬ�ģ���ô�Ӹ��ڵ㵽��������֧�ĺ�ɫ��Ҳ��ͬ
		//����ֻ��Ҫ�жϴӸ��ڵ㵽ÿ��Ҷ�ӽ��ĺ�ɫ��Ŀ�Ƿ���ͬ����
		size_t blackcount = 0;
		Node *pCur = getRoot();
		while (pCur->_left){
			pCur = pCur->_left;
			if (BLACK == pCur->_col){
				blackcount++;
			}
		}
		blackcount++;
		return JudgeBlackCount(pRoot,0,blackcount);


	}
private:
	bool JudgeBlackCount(Node *pCur,size_t path,size_t blackcount){
		if (pCur == nullptr){
			return true;
		}
		if (BLACK==pCur->_col){
			path++;
		}
		if (RED == pCur->_parent->_col &&RED == pCur->_col){
			cout <<pCur->_val<<" and "<<pCur->_parent->_val<< "���Ǻ�ɫ�������������һ�𣬺������Ӧ�ó����к�ɫ�������һ����������" << endl;
			return false;
		}
		if (pCur->_left == nullptr&&pCur->_right == nullptr){
			if (path != blackcount){
				
				cout << "������֧��ɫ��������ͬ�������Ӧ��֤ÿ����֧�ĺ�ɫ�������ͬ��" << endl;
				return false;
			}

				
			return true;
		}
		return JudgeBlackCount(pCur->_left, path, blackcount) &&
			JudgeBlackCount(pCur->_right, path, blackcount);

	}
	void RotateRight(Node *parent){
		Node *grandFather = parent->_parent;
		Node *SubL = parent->_left;
		Node *SubLR = SubL->_right;

		if (SubLR)
			SubLR->_parent = parent;
		parent->_left = SubLR;
		parent->_parent = SubL;
		SubL->_right = parent;



		if (grandFather == _phead){  //SubR����˸��ڵ�
			grandFather->_parent = SubL;
		}
		else{
			if (parent == grandFather->_left){
				grandFather->_left = SubL;
			}
			else{
				grandFather->_right = SubL;
			}
		}

		SubL->_parent = grandFather;

	}
	void RotateLeft(Node *parent){
		Node *grandFather = parent->_parent;
		Node *SubR = parent->_right;
		Node *SubRL = SubR->_left;
		
		if (SubRL)
			SubRL->_parent = parent;
		parent->_right = SubRL;
		parent->_parent = SubR;
		SubR->_left = parent;


		if (grandFather == _phead){  //SubR����˸��ڵ�
			grandFather->_parent = SubR;
		}
		else{
			if (parent == grandFather->_left){
				grandFather->_left = SubR;
			}
			else{
				grandFather->_right = SubR;
			}
		}
		
		SubR->_parent = grandFather;


	}
	Node* LeftMost(){
		Node *pRoot = getRoot();
		if (nullptr == pRoot)
			return _phead;

		//�������ڵ�
		Node *pCur = pRoot;
		while (pCur->_left){
			pCur = pCur->_left;
		}
		return pCur;
	}
	Node* RightMost(){
		Node *pRoot = getRoot();
		if (nullptr == pRoot)
			return _phead;

		//�������ڵ�
		Node *pCur = pRoot;
		while (pCur->_right){
			pCur = pCur->_right;
		}
		return pCur;
	}
	Node* _phead;
	size_t _size;
};



void TestRBTree(){
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };

	RBtree<int> t;
	for (auto e : a){
		t.insert(e);
	}
	cout<<t.isVaildRBTree()<<endl;
	cout << true << endl;
}