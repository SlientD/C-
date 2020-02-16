#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <iostream>
using namespace std;

//����ȱ�ݣ����������Ԫ������
//��ʱ���ݣ�---ͨ����������  ��Ԫ�ظ����������������Ϊ��������  ������0.7���ڣ�������ݣ�
//��ο����ҵ��ӽ�����

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
		//1.ͨ����ϣ�����������ϣ��ַ
		size_t hashAddr = HashFunc(data);
		//2.�Һ���λ��
		while (_table[hashAddr]._state != EMPTY){
			if (_table[hashAddr]._state == EXIST&&_table[hashAddr]._data == data){
				return false;
			}
			//����̽��
			hashAddr++;
			//��ʽһ
			//hashAddr %= _table.capacity();  //ÿ�ζ�Ҫ����pass��
			//��ʽ����
			if (hashAddr == _table.capacity()){
				hashAddr = 0;
			}
		}
		//�ҵ���һ����λ�ã�����Ԫ��
		_table[hashAddr]._data = data;
		_table[hashAddr]._state = EXIST;
		_size++;
		return true;
		
	}


	int Find(const T& data){
		//1.ͨ����ϣ����������Ԫ���ڱ���е�λ��
		size_t hashAddr = HashFunc(data);
		while (_table[hashAddr]._state != EMPTY){  
			if (_table[hashAddr]._state == EXIST&&_table[hashAddr]._data == data){
				return hashAddr;

			}
			//��Ҫ��������̽��
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