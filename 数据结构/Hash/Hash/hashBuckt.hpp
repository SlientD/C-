#pragma once
#include "common.hpp"

//哈希桶：与哈希的不同是，每个数组中存的是一个链表，这个链表中的数据通过哈希函数算出的下标都是这个桶序号，/
//这样就实现了完全的与哈希函数计算出的值一一对应

//扩容怎么扩？
//什么情况下，哈希桶的性能最好？:如果哈希桶中所存储的元素个数和桶的个数相等时
//  因为：哈希桶的最佳状态时每个桶中存储一个元素
//  每个桶中都有一个元素，再插肯定会发生冲突，同时保正利用率大一点
//  

template <class T>
struct HushNode{
	HushNode(const T &data)
	:_data(data)
	, _next(nullptr)
	{
	}

	T _data;
	HushNode<T> *_next;
};
template <class T, class DF = DFDef<T>>
class HashBucket ;
//迭代器   原生态指针   对原生态指针进行封装 

template <class T, class DF = DFDef<T>>
struct HBIterator
{
	typedef HushNode<T> Node;
	HBIterator(Node *pNode,HashBucket<T,DF> *hb){
		_pNode = pNode;
		_hb = hb;
	}
	//具有指针类似的操作
	//能够移动
	//前置++
	//后置+++
	//比较
	bool operator!=(Node &s){

	}
	bool operator==(Node &s){

	}
	void Next(){
		if (_pNode->_next){
			//_pNode对应的链表后序还有节点
			_pNode = _pNode->_next;
		}
		else{
			//_pNode是所在链上的最后一个节点
			//要找_pNode后序的第一个非空的桶
			//如何知道pnode在哪个桶中？如果拿到哈希函数就可以，怎么拿到哈希函数呢？在维护一个哈希表啊
			size_t bucketNo = _ht->HashFunc();
			for (; bucketNo < _ht->table.cap(); ++bucketNo){
				if (_ht->table[bucketNo]){
					//非空桶已找到
					_pNode = _ht->table[bucketNo];
					return;
				}
				_pNode = nullptr;
			}
		}
	}
	Node * _pNode;
	HashBucket<T, DF> *_hb;
};
//迭代器如何与类结合？
// 1.为该类定义迭代器
// 2.在类中重新给迭代器命名
// 3/增加begin end接口
template <class T,class DF=DFDef<T>>
class HashBucket{
	typedef HushNode<T> Node;
	friend class HBIterator<T, DF>;
	typedef HBIterator<T, DF> iterator;
public:

	HashBucket(size_t capa=10)
	:_size(0)
	{
		_table.resize(GetNextPrime(capa));
	}

	//表示哈希桶元素唯一
	bool InsertUnique(const T& data){
		CheckCap();
		//1.计算桶号
		size_t bucketNo = HashFun(data);

		//2.检测值为data的元素在哈希桶中是否存在
		Node *pCur = _table[bucketNo];
		while (pCur){
			if (pCur->_data == data)
				return false;
			pCur = pCur->_next;
		}

		//3.创建、插入新节点--采用头插的方式
		Node *pNew=new Node(data);
		pNew->_next = _table[bucketNo];
		_table[bucketNo] = pNew;
		++_size;
		return true;
	}

	//表示哈希桶元素可重复
	bool InsertRepeate(const T& data){
		CheckCap();
		//1.计算桶号
		size_t bucketNo = HashFun(data);

		//2.创建、插入新节点--采用头插的方式
		Node *pNew = new Node(data);
		pNew->_next = _table[bucketNo];
		_table[bucketNo] = pNew;
		++_size;
		return true;
	}

	bool EraseOne(const T& data){
		//1.计算桶号
		size_t bucketNo = HashFun(data);
		//2.找到
		Node *pCur = _table[bucketNo];
		Node *pPre = nullptr;
		while (pCur){
			if (pCur->_data == data)
			{
				if (pPre == nullptr){
					_table[bucketNo] = pCur->_next;
				}
				else{
					pPre->_next = pCur->_next;
				}		
				delete pCur;
				--_size;
				return true;
			}
			pPre = pCur;
			pCur = pCur->_next;
		}
		return false;
		
	}
	void EraseAll(const T& data){
		//1.计算桶号
		size_t bucketNo = HashFun(data);
		
		Node *pCur = _table[bucketNo];
		Node *pPre = nullptr;
		while (pCur){
			if (pCur->_data == data)
			{
				if (pPre == nullptr){
					_table[bucketNo] = pCur->_next;
					delete pCur;
					
					pCur = _table[bucketNo];
				}
				else{
					pPre->_next = pCur->_next;
					delete pCur;
					
					pCur = pPre->_next;
				}
				--_size;
				continue;
			}
			pPre = pCur;
			pCur = pCur->_next;
		}




		////2.找到
		//Node *pCur == _table[bucketNo];
		//while (pCur->_data == data){
		//	_table[bucketNo] = pCur->_next;
		//	delete pCur;
		//	pCur = _table[bucketNo];
		//}
		//while (pCur){
		//	if (pCur->_next->_data == data)
		//	{
		//		Node *tmp = pCur->_next;
		//		pCur->_next = tmp->_next;
		//		delete tmp;
		//	}
		//	pCur = pCur->_next;
		//}	
	}
	

	
	Node * find(const T &data){
		//1.计算桶号
		size_t bucketNo = HashFun(data);
		//2.找到
		Node *pCur = _table[bucketNo];
		while (pCur){
			if (pCur->_data == data)
			{
				return pCur;
			}
			pCur = pCur->_next;
		}
		return nullptr;
	}
	iterator begin(){
		//找第一个非空桶
		for (size_t bucket = 0; bucket < _table.size();bucket++){
			if (_table[bucket])
				return iterator(_table[bucket], this);

		}
		return end();
	}
	iterator end(){
		return iterator(nullptr, this);
	}




	//in test
	void HashBucketPrint(){
		for (int i = 0; i < _table.size(); i++){
			Node *pCur = _table[i];
			cout << "BNO." << i << ":";
			while (pCur){
				cout << pCur->_data << " --> ";
				pCur = pCur->_next;
			}
				
			
			cout<<"NULL" << endl;
		}
	}
private:
	size_t HashFun(const T& data){
		return DF()(data)%_table.capacity();
	}
	//能不能采用闭散列的方式交换的方式来进行扩容？
	//可以，但是不推荐，因为这种方式还是会调用insert函数new新节点，导致空间资源的浪费
	//所以我们采用移动节点就可以
	void CheckCap(){
		if (_table.size() > _size)
			return;
		vector<Node *> Newtable(GetNextPrime(_table.size()));
		_table.swap(Newtable);
		size_t bucketNo;
		for (int i = 0; i < Newtable.size(); i++){
			Node *pCur = Newtable[i];
			Node *pNew;
			while (pCur){
				pNew = pCur;
				pCur = pCur->_next;

				bucketNo = HashFun(pNew->_data);
				pNew->_next = _table[bucketNo];
				_table[bucketNo] = pNew;		
			}
		}
		cout << "Expend Capacity successfully" << endl;
	}
private:
	vector<Node *> _table;
	size_t _size;

};