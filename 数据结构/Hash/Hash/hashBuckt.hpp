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


template <class T,class DF=DFDef<T>>
class HashBucket{
public:
	typedef HushNode<T> Node;
	HashBucket(size_t capa=10)
	:_size(0)
	{
		_table.resize(GetNextPrime(capa));
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
	

	
	Node * find(const T &data){
		//1.����Ͱ��
		size_t bucketNo = HashFun(data);
		//2.�ҵ�
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
	//�ܲ��ܲ��ñ�ɢ�еķ�ʽ�����ķ�ʽ���������ݣ�
	//���ԣ����ǲ��Ƽ�����Ϊ���ַ�ʽ���ǻ����insert����new�½ڵ㣬���¿ռ���Դ���˷�
	//�������ǲ����ƶ��ڵ�Ϳ���
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