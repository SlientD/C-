#pragma once
#include "common.hpp"

//��ϣͰ�����ϣ�Ĳ�ͬ�ǣ�ÿ�������д����һ��������������е�����ͨ����ϣ����������±궼�����Ͱ��ţ�/
//������ʵ������ȫ�����ϣ�����������ֵһһ��Ӧ

//������ô����
//ʲô����£���ϣͰ��������ã�:�����ϣͰ�����洢��Ԫ�ظ�����Ͱ�ĸ������ʱ
//  ��Ϊ����ϣͰ�����״̬ʱÿ��Ͱ�д洢һ��Ԫ��
//  ÿ��Ͱ�ж���һ��Ԫ�أ��ٲ�϶��ᷢ����ͻ��ͬʱ���������ʴ�һ��
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
//������   ԭ��ָ̬��   ��ԭ��ָ̬����з�װ 

template <class T, class DF = DFDef<T>>
struct HBIterator
{
	typedef HushNode<T> Node;
	typedef HBIterator<T, DF> Self;
	HBIterator(Node *pNode,HashBucket<T,DF> *hb){
		_pNode = pNode;
		_hb = hb;
	}
	//����ָ�����ƵĲ���
	//�ܹ��ƶ�
	//ǰ��++
	//����+++
	//�Ƚ�
	bool operator!=(Self &s){
		return _pNode != s._pNode;
	}
	bool operator==(Self &s){
		return _pNode == s._pNode;
	}
	T& operator*(){
		return _pNode->_data;
	}
	T* operator->(){
		return &(_pNode->_data);   ///??????????????????????????
	}
	Self& operator++(){
		Next();
		return *this;
	}
	Self operator++(int){
		Self tmp(*this);
		Next();
		return tmp;
	}
	void Next(){
		if (_pNode->_next){
			//_pNode��Ӧ����������нڵ�
			_pNode = _pNode->_next;
		}
		else{
			//_pNode���������ϵ����һ���ڵ�
			//Ҫ��_pNode����ĵ�һ���ǿյ�Ͱ
			//���֪��pnode���ĸ�Ͱ�У�����õ���ϣ�����Ϳ��ԣ���ô�õ���ϣ�����أ���ά��һ����ϣ��
			size_t bucketNo = _ht->HashFunc();
			for (; bucketNo < _ht->table.cap(); ++bucketNo){
				if (_ht->table[bucketNo]){
					//�ǿ�Ͱ���ҵ�
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
//��������������ϣ�
// 1.Ϊ���ඨ�������
// 2.���������¸�����������
// 3/����begin end�ӿ�
template <class T,class DF=DFDef<T>>
class HashBucket{
	typedef HushNode<T> Node;
	friend struct HBIterator<T, DF>;
	
public:
	typedef HBIterator<T, DF> iterator;
	HashBucket(size_t capa=10)
	:_size(0)
	{
		_table.resize(GetNextPrime(capa));
	}
	~HashBucket(){
		clear();
	}


	pair<iterator,bool> insert(const T& data){
		CheckCap();
		//1.����Ͱ��
		size_t bucketNo = HashFun(data);

		//2.���ֵΪdata��Ԫ���ڹ�ϣͰ���Ƿ����
		Node *pCur = _table[bucketNo];
		while (pCur){
			if (DF()(pCur->_data) == DF()(data))
				return make_pair(iterator(pCur,this),false);
			pCur = pCur->_next;
		}

		//3.�����������½ڵ�--����ͷ��ķ�ʽ
		Node *pNew = new Node(data);
		pNew->_next = _table[bucketNo];
		_table[bucketNo] = pNew;
		++_size;
		return make_pair(iterator(pNew, this), true);;
	}


	//��ʾ��ϣͰԪ��Ψһ
	bool InsertUnique(const T& data){
		CheckCap();
		//1.����Ͱ��
		size_t bucketNo = HashFun(data);

		//2.���ֵΪdata��Ԫ���ڹ�ϣͰ���Ƿ����
		Node *pCur = _table[bucketNo];
		while (pCur){
			if (pCur->_data == data)
				return false;
			pCur = pCur->_next;
		}

		//3.�����������½ڵ�--����ͷ��ķ�ʽ
		Node *pNew=new Node(data);
		pNew->_next = _table[bucketNo];
		_table[bucketNo] = pNew;
		++_size;
		return true;
	}

	//��ʾ��ϣͰԪ�ؿ��ظ�
	bool InsertRepeate(const T& data){
		CheckCap();
		//1.����Ͱ��
		size_t bucketNo = HashFun(data);

		//2.�����������½ڵ�--����ͷ��ķ�ʽ
		Node *pNew = new Node(data);
		pNew->_next = _table[bucketNo];
		_table[bucketNo] = pNew;
		++_size;
		return true;
	}
	size_t erase(const T& data){
		//1.����Ͱ��
		size_t bucketNo = HashFun(data);
		//2.�ҵ�
		Node *pCur = _table[bucketNo];
		Node *pPre = nullptr;
		while (pCur){
			if (DF()(pCur->_data) == DF()(data))
			{
				if (pPre == nullptr){
					_table[bucketNo] = pCur->_next;
				}
				else{
					pPre->_next = pCur->_next;
				}
				delete pCur;
				--_size;
				return 1;
			}
			pPre = pCur;
			pCur = pCur->_next;
		}
		return 0;

	}
	bool EraseOne(const T& data){
		//1.����Ͱ��
		size_t bucketNo = HashFun(data);
		//2.�ҵ�
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
		//1.����Ͱ��
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




		////2.�ҵ�
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
	

	
	iterator find(const T &data){
		//1.����Ͱ��
		size_t bucketNo = HashFun(data);
		//2.�ҵ�
		Node *pCur = _table[bucketNo];
		while (pCur){
			if (DF()(pCur->_data) == DF()(data))
			{
				return iterator(pCur, this);
			}
			pCur = pCur->_next;
			
		}
		return iterator(nullptr, this);
	}
	iterator begin(){
		//�ҵ�һ���ǿ�Ͱ
		for (size_t bucket = 0; bucket < _table.size();bucket++){
			if (_table[bucket])
				return iterator(_table[bucket], this);

		}
		return end();
	}
	iterator end(){
		return iterator(nullptr, this);
	}

	void clear(){
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); bucketNo++){
			Node *cur = _table[bucketNo];
			
			while(cur){
				_table[bucketNo] = cur->_next;
				delete cur;
				cur = _table[bucketNo];	
			}
		}
	}
	//����ͨ���ܸ���
	size_t bucket_count()const{
		return _table.size();
	}

	//����ĳ��Ͱ�н�����
	size_t bucket_size(size_t bucketNo)const{
		if (bucketNo >= bucket_count()){
			return 0;
		}
		size_t count = 0;
		Node *cur = _table[bucketNo];
		while (cur){
			count++;
			cur = cur->_next;
		}
		return count;
	}

	//����key����Ͱ��
	int bucket(const T &data){

		int pos= HashFun(data);
		Node *cur = _table[pos];
		while (cur){
			if (DF()(cur->_data) ==DF()(data)){
				return pos;
			}
		}
		return -1;
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
	void swap(HashBucket<T, DF> &ht){//�����ǿ��Է���������˽�г�Ա��
		_table.swap(ht._table);
		std::swap(_size, ht._size);
	}
	bool empty(){
		if (_size == 0){
			return true;
		}
		return false;
	}
	size_t size()const{
		return _size;
	}
private:
	size_t HashFun(const T& data){
		return DF()(data)%_table.capacity();
	}
	//�ܲ��ܲ��ñ�ɢ�еķ�ʽ�����ķ�ʽ���������ݣ�
	//���ԣ����ǲ��Ƽ�����Ϊ���ַ�ʽ���ǻ����insert����new�½ڵ㣬���¿ռ���Դ���˷�
	//�������ǲ����ƶ��ڵ�Ϳ���
	void CheckCap(){
		if (_table.size() > _size)
			return;
		vector<Node *> Oldtable(GetNextPrime(_table.size()));
		_table.swap(Oldtable);
		size_t bucketNo;
		for (int i = 0; i < Oldtable.size(); i++){
			Node *pCur = Oldtable[i];
			while (pCur){
				bucketNo = HashFun(pCur->_data);
				Oldtable[i] = pCur->_next;
				pCur->_next = _table[bucketNo];
				_table[bucketNo] = pCur;
				pCur = Oldtable[i];
			}
		}
		cout << "Expend Capacity successfully" << endl;
	}
private:
	vector<Node *> _table;
	size_t _size;

};