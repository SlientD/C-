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

template<class T>
struct RBIterator{
	typedef RBtreeNode<T> Node;
	typedef RBIterator<T> Self;
	RBIterator(Node *pNode=nullptr)
		:_pNode(pNode)
	{
	}

	//��������ָ��Ĳ���
	T& operator*(){
		return _pNode->_val;
	}
	T* operator->(){
		return &(_pNode->_val);
	}

	//�����ƶ�
	Self& operator++(){
		Increase();
		return *this;
	}

	Self operator++(int){
		Self tmp(_pNode);
		Increase();
		return tmp;

	}
	Self& operator--(){
		DeIncrease();
		return *this;
	}

	Self operator--(int){
		Self tmp(_pNode);
		DeIncrease();
		return tmp;

	}
	void Increase(){
		if (_pNode->_right){
			_pNode = _pNode->_right;
			while (_pNode->_left){
				_pNode = _pNode->_left;
			}
		}
		else{
			
			Node *parent = _pNode->_parent;
			while (_pNode == parent->_right){
				_pNode = parent;
				parent = parent->_parent;
			}
			//��ֹ������������ڵ�û��������
			if (_pNode->_right != parent){
				_pNode = parent;
			}
		}
	}
	void DeIncrease(){
		//���_pnode��end��λ��   �����һ������������ͷ���Ҳ�����Ǹ��ڵ�
		if (_pNode->_parent->_parent==_pNode&&_pNode->_col==RED){
			_pNode = _pNode->_right;
			return;
		}
		//���������ڣ��������������ģ����������Ҳ�ģ�
		if (_pNode->_left){
			_pNode = _pNode->_left;
			while (_pNode->_right){
				_pNode = _pNode->_right;
			}
		}
		else{
			Node *parent = _pNode->_parent;
			while (_pNode == parent->_left){
				_pNode = parent;
				parent = parent->_parent;
			}
			//��ֹ������������ڵ�û��������
			if (_pNode->_left != parent){
				_pNode = parent;
			}
		}
	}
	//�����Ƚ�
	bool operator==(const Self &s)const{
		return _pNode == s._pNode;
	}
	bool operator!=(const Self &s)const{
		return _pNode != s._pNode;
	}


	Node *_pNode;
};



//T:��ʾ������д洢Ԫ�ص�����
//KOFV:��Ԫ������ȡkey�ķ���
template <class T,class KOFV>
class RBtree{
	typedef RBtreeNode<T> Node;
public:
	typedef RBIterator<T> Iterator;
public:
	RBtree(){
		_phead = new Node;
		_phead->_left = _phead;
		_phead->_right = _phead;
		_size = 0;
	}
	Iterator begin(){
		return Iterator(_phead->_left);
	}
	Iterator end(){
		return Iterator(_phead);
	}
	pair<Iterator,bool> insert(const T &data){
		Node* pRoot = getRoot();
		//����
		if (nullptr == pRoot){
			pRoot = new Node(data, BLACK);
			
			pRoot->_parent = _phead;

			_phead->_left = pRoot;
			_phead->_right = pRoot;
			_phead->_parent = pRoot;
			_size++;
			return make_pair(Iterator(pRoot),true);
			
		}

		//�ǿգ����չ������
		Node *pCur = pRoot;
		Node *pParent = nullptr;
		while (pCur){
			pParent = pCur;
			if (KOFV()(data) >KOFV()( pCur->_val)){
				
				pCur = pCur->_right;
			}
			else if (KOFV()(data) <KOFV()(pCur->_val)){
				pCur = pCur->_left;
			}
			else{
				//data�Ѵ���
				return make_pair(Iterator(pCur),false);
			}
		}
		Node *NewNode = new Node(data);
		pCur = NewNode;
		if (KOFV()(data) <KOFV()(pParent->_val)){
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
		return  make_pair(Iterator(NewNode),true);
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

	bool empty(){
		return _size == 0;
			
	}
	size_t size()const{
		return _size;
	}
	Iterator Find(const T &val){
		Node *cur = getRoot();
		while (cur){
			if (KOFV()(val) ==KOFV()(cur->_val)){
				return Iterator(cur);
			}
			if (KOFV()(val) <KOFV()(cur->_val)){
				cur = cur->_left;
			}
			else{
				cur = cur->_right;
			}
		}
		return Iterator(nullptr);
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


#if 0
void TestRBTree(){
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };

	RBtree<int> t;
	for (auto e : a){
		t.insert(e);
	}
	auto it = t.begin();
	while (it != t.end()){
		cout << *it << "  ";
		it++;
	}
	cout << endl;
	while (it != t.begin()){
		it--;
		cout << *it << "  ";
	}
	cout << endl;
	
	cout<<t.isVaildRBTree()<<endl;
	cout << true << endl;
}

#endif