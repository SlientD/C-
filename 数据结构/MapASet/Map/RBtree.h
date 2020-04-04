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

	//具有类似指针的操作
	T& operator*(){
		return _pNode->_val;
	}
	T* operator->(){
		return &(_pNode->_val);
	}

	//可以移动
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
			//防止特殊情况：根节点没有右子树
			if (_pNode->_right != parent){
				_pNode = parent;
			}
		}
	}
	void DeIncrease(){
		//如果_pnode在end的位置   满足第一个条件可能是头结点也可能是根节点
		if (_pNode->_parent->_parent==_pNode&&_pNode->_col==RED){
			_pNode = _pNode->_right;
			return;
		}
		//左子树存在，找左子树中最大的（左子树最右侧的）
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
			//防止特殊情况：根节点没有左子树
			if (_pNode->_left != parent){
				_pNode = parent;
			}
		}
	}
	//可作比较
	bool operator==(const Self &s)const{
		return _pNode == s._pNode;
	}
	bool operator!=(const Self &s)const{
		return _pNode != s._pNode;
	}


	Node *_pNode;
};



//T:表示红黑树中存储元素的类型
//KOFV:从元素中提取key的方法
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
		//空树
		if (nullptr == pRoot){
			pRoot = new Node(data, BLACK);
			
			pRoot->_parent = _phead;

			_phead->_left = pRoot;
			_phead->_right = pRoot;
			_phead->_parent = pRoot;
			_size++;
			return make_pair(Iterator(pRoot),true);
			
		}

		//非空，按照规则插入
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
				//data已存在
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

		//检测是否违反红黑树的性质--红色不能挨着
		//新节点的默认颜色是红色，如果新节点的双亲颜色是红色，那么违反了红黑树的特性
		//需要对红黑树进行调整
		while (pParent!=_phead&&RED == pParent->_col){
			Node *grandFather = pParent->_parent;
			if (pParent == grandFather->_left)
			{
				Node *uncle = grandFather->_right;
				if (uncle&&RED == uncle->_col){
					pParent->_col = BLACK;
					uncle->_col = BLACK;
					grandFather->_col = RED;

					//grandFater可能有双亲，所以要继续往上看
					pCur = grandFather;
					pParent = grandFather->_parent;
				}

				else{
					//如果pcur在parent的右侧，则对以parent为pcur根节点的子树进行左单旋处理,变成pcur在parent的左侧的情况
					if (pParent->_right == pCur){
						RotateLeft(pParent);
						swap(pParent, pCur);
					}
					//pcur在parent的左侧，或不存在uncle的情况，都是将双亲变黑，祖父变红，对祖父进行右单旋就可解决问题
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

					//grandFater可能有双亲，所以要继续往上看
					pCur = grandFather;
					pParent = grandFather->_parent;
				}

				else{
					//如果pcur在parent的左侧，则对以parent为pcur根节点的子树进行右单旋处理,变成pcur在parent的右侧的情况
					if (pParent->_left == pCur){
						RotateRight(pParent);
						swap(pParent, pCur);
					}
					//pcur在parent的右侧，或不存在uncle的情况，都是将双亲变黑，祖父变红，对祖父进行左单旋就可解决问题
					pParent->_col = BLACK;
					grandFather->_col = RED;
					RotateLeft(grandFather);
				}

			}
		}
		_phead->_parent->_col = BLACK;
		//如果双亲是黑色则不违反

		//更新头结点的左右指向
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
		//空树也是红黑树
		if (nullptr == pRoot)
			return true;

		//树非空

		//检测性质1：根节点是黑色的
		if (BLACK != pRoot->_col){
			cout << "根节点是红色的，但根节点应该是黑色的所以不是红黑树！！" << endl;
			return false;
		}

		//检测性质2：每条路径中黑色结点个数必须要相同
		//从根节点出发，到各个末枝的结点总数都相同那么每个分支上的两边的结点也一定相同
		//因为如果一个节点两边的黑色两边不同，这个结点以上对于两个分支又是相同的，那么从根节点到这两个分支的黑色数也不同
		//所以只需要判断从根节点到每个叶子结点的黑色数目是否相同就行
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
			cout <<pCur->_val<<" and "<<pCur->_parent->_val<< "都是红色结点且两个连在一起，红黑树不应该出现有红色结点连在一起的情况！！" << endl;
			return false;
		}
		if (pCur->_left == nullptr&&pCur->_right == nullptr){
			if (path != blackcount){
				
				cout << "各个分支黑色结点个数不同，红黑树应保证每个分支的黑色结点数相同！" << endl;
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



		if (grandFather == _phead){  //SubR变成了根节点
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


		if (grandFather == _phead){  //SubR变成了根节点
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

		//找最左侧节点
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

		//找最左侧节点
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