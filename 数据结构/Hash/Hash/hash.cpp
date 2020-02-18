#define _CRT_SECURE_NO_WARNINGS 1

#include "hash.hpp"
using namespace std;

//代码缺陷，不针对所有元素类型
//何时扩容？---通过负载因子  ：元素个数、表格容量，称为负载因子  控制在0.7以内，如何扩容？
//如何快速找到接近两倍

enum STATE{EMPTY,DELETE,EXIST};
template <class T>
struct Elem{
	Elem(){
		_state = EMPTY;
	}
	T _data;
	STATE _state;
};

//让一个类的对象可以让他按照函数的方式来进行调用
template <class T>
class DFDef{
public:
	T operator()(const T& data){
		return data;
	}
};


class DFStr{
public:
	size_t operator()(const string& str){
		return BKDRHash(str.c_str());
	}
private:
	size_t BKDRHash(const char *str){
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++){
			hash = hash * 131 + ch;
		}
		return hash;
	}
};


//T:代表元素类型，   DF:将T类型转换为整数数据方法的类型
//IsLine表示按照线性还是二次冲突处理
template <class T, class DF = DFDef<T>, bool IsLine = true>
class HashTable{
public:
	HashTable(size_t capacity=10)
		:_size(0)
		, _capacity(capacity)
	{
		_table.resize(GetNextPrime(capacity));
		
		
	}
	bool Insert(const T& data){
		CheckCapacity();
		//1.通过哈希函数，计算哈希地址
		size_t hashAddr = HashFunc(data);
		//2.找合适位置
		int i = 0;
		while (_table[hashAddr]._state == EXIST){    
			if (_table[hashAddr]._state == EXIST&&_table[hashAddr]._data == data){
				return false;
			}
			
			//线性探测
			if (IsLine){
				hashAddr++;
				//方式一
				//hashAddr %= _table.capacity();  //每次都要计算pass掉
				//方式二：
				if (hashAddr == _table.capacity()){
					hashAddr = 0;
				}
			}
			
			//二次线性探测
			else{
				i++;
				hashAddr = (hashAddr + 2 * i + 1) % _table.capacity();
			}
			
			
		}
		//找到了一个空位置，插入元素
		_table[hashAddr]._data = data;
		_table[hashAddr]._state = EXIST;
		_size++;
		return true;
		
	}


	int Find(const T& data){
		//1.通过哈希函数，计算元素在表格中的位置
		size_t hashAddr = HashFunc(data);
		while (_table[hashAddr]._state != EMPTY){  
			if (_table[hashAddr]._state == EXIST&&_table[hashAddr]._data == data){
				return hashAddr;

			}
			//需要往后线性探测
			hashAddr++;
			if (hashAddr == _table.capacity()){
				hashAddr = 0;
			}
		}
		return -1;
	}

	bool Erase(const T & data){
		int pos = Find(data);
		if (pos == -1){
			return false;
		}
		_table[pos]._state = DELETE;
		_size--;
	}
	int size(){
		return _size;
	}
	void Swap(HashTable<T, DF, IsLine>& ht){
		_table.swap(ht._table);//比下面的交换效率高，在里面的实现是交换了start、finish，end_of_storage指针
		swap(_size, ht._size);
		_capacity = _table.capacity();
	}
private:
	void CheckCapacity(){

		if (_size * 10 / _table.capacity() == 7){
			//重新创建一个哈希表，将旧哈希表状态为存在的元素向新哈希表格中插入
			
			
			//1.新创一个哈希表
			HashTable<T, DF, IsLine> newHT(GetNextPrime(_table.capacity()));
			//2.将旧哈希表中的状态为存在的元素向新哈希表格中插入
			for (auto e : _table){
				if (e._state == EXIST)
					newHT.Insert(e._data);
			}
			Swap(newHT);
		}
	}
	int HashFunc(const T & data){

		return (DF()(data)) % 11;
	}




private:
	int _size;
	int _capacity;
	vector<Elem<T>> _table;

};


