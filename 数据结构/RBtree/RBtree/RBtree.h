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
		//空树
		if (nullptr == pRoot){
			pRoot = new Node(data, BLACK);
			
			pRoot->_parent = _phead;

			_phead->_left = pRoot;
			_phead->_right = pRoot;
			_phead->_parent = pRoot;
			_size++;
			return true;
			
		}

		//非空，按照规则插入
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
				//data已存在
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
		return  true;
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



void TestRBTree(){
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };

	RBtree<int> t;
	for (auto e : a){
		t.insert(e);
	}
	cout<<t.isVaildRBTree()<<endl;
	cout << true << endl;
}