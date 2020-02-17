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

	T weight;           //Ȩֵ
	HuffManTreeNode *left;
	HuffManTreeNode *right;
	HuffManTreeNode *parent;
}; 
template <class T>
class Less{
	typedef HuffManTreeNode<T> Node;
public:
	bool operator()(const Node* left, const Node* right){
		return ( left->weight > right->weight);   //�ڴ˱Ƚϵ�����������const�����ں������ص�ʱ��Ҫ��thisҲ����const����
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
		//����ɭ��
		//����С˳���ź�
		priority_queue<Node *,vector<Node *>,Less<T>> q;
		for (auto e : v){             //����Ĳ�������ı�v�е�ֵ��ֻ��ı����������ֵ������code������Ҳֻ�Ǹı��˹��������н���Ա��ֵ
			if (e == invalid)
				continue;
			q.push(new Node(e));    
		}
		//����
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


