#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <iostream>
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
	int _data;
	STATE _state;
};

template <class T>
class HashTable{
public:
	HashTable(const vector<T> & v, size_t capacity=11)
		:_size(0)
		, _capacity(capacity)
	{
		_table.resize(_capacity);
		for (int i = 0; i < v.size(); i++){
			Insert(v[i]);
		}
	}
	bool Insert(const T& data){
		//1.通过哈希函数，计算哈希地址
		size_t hashAddr = HashFunc(data);
		//2.找合适位置
		while (_table[hashAddr]._state != EMPTY){
			if (_table[hashAddr]._state == EXIST&&_table[hashAddr]._data == data){
				return false;
			}
			//线性探测
			hashAddr++;
			//方式一
			//hashAddr %= _table.capacity();  //每次都要计算pass掉
			//方式二：
			if (hashAddr == _table.capacity()){
				hashAddr = 0;
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

private:
	int HashFunc(const T & data){
		return data % 11;
	}




private:
	int _size;
	int _capacity;
	vector<Elem<T>> _table;

};

void TestHashTable(){
	vector<int> arr { 21, 67, 112, 99, 5, 13, 44 };
	HashTable<int> hash(arr);

	cout << hash.size() << endl;
	hash.Insert(87);
	cout << hash.size() << endl;
	hash.Erase(44);
	cout << hash.size() << endl;
}

int main(){
	TestHashTable();
	system("pause");
	return 0;
}