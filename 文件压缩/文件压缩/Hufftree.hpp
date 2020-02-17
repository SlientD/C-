#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
#include <vector>
#include <queue>
//#include "HuffCompress.hpp"
using namespace std;

template <class T>
struct HuffManTreeNode
{
	HuffManTreeNode(const T& _weight=T())
	:weight(_weight)
	, left(nullptr)
	, right(nullptr)
	, parent(nullptr)
	{}

	T weight;           //权值
	HuffManTreeNode *left;
	HuffManTreeNode *right;
	HuffManTreeNode *parent;
}; 
template <class T>
class Less{
	typedef HuffManTreeNode<T> Node;
public:
	bool operator()(const Node* left, const Node* right){
		return ( left->weight > right->weight);   //在此比较的左右数都是const所以在函数重载的时候要将this也加上const修饰
	}
};

template <class T>
class HuffManTree{
	typedef HuffManTreeNode<T> Node;
public:
	HuffManTree(const vector<T> &v, const T &invalid)
		:root(nullptr)
	{
		CreateTree(v, invalid);
	}
	~HuffManTree(){
		DestroyTree(root);
	}
	void CreateTree(const vector<T> &v,const  T &invalid){
		//构建森林
		//按大小顺序排好
		priority_queue<Node *,vector<Node *>,Less<T>> q;
		for (auto e : v){             //后面的操作不会改变v中的值，只会改变哈夫曼树的值，对于code的生成也只是改变了哈夫曼树中结点成员的值
			if (e == invalid)
				continue;
			q.push(new Node(e));    
		}
		//构建
		while (q.size() > 1){
			Node *left = q.top();
			q.pop();
			Node *right = q.top();
			q.pop();
			root = new Node(left->weight + right->weight);
			root->left = left;
			root->right = right;
			left->parent = root;
			right->parent = root;
			q.push(root);
		}
		root = q.top();
	}
	
	Node * GetRoot(){
		return root;
	}

private:
	void DestroyTree(Node *& proot){
		if (proot){
			DestroyTree(proot->left);
			DestroyTree(proot->right);
			delete(proot);
		}
	}

private:
	Node *root;
};


//void TestHuffManTree(){
//	vector<int> v{ 3, 1, 7, 5 };
//	HuffManTree<int> htr(v);
//}


