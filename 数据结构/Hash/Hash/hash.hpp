#define _CRT_SECURE_NO_WARNINGS 1
#include "common.hpp"

//��ϣ��ԭ����Ԫ���������±꽨��ӳ���ϵ�������ڲ��Ƚϵ������ֱ��ͨ�������ҵ�Ԫ��


//ɾ����λ���ܲ���ֱ��ɾ��Ԫ�أ����ܵĻ���ν����ɾ����λ���ܲ���ֱ�Ӳ��룿���Եģ�
//��ʱ���ݣ�---ͨ����������  ��Ԫ�ظ����������������Ϊ��������  ������0.7���ڣ�������ݣ�
//��ο����ҵ��ӽ�������������
//����ɢ�о�����ͻ��ô�죿
//��ν���������͵Ĵ洢��string���������أ�

enum STATE{ EMPTY, DELETE, EXIST };
template <class T>
struct Elem{
	Elem(){
		_state = EMPTY;
	}
	T _data;
	STATE _state;
};

//��һ����Ķ�������������պ����ķ�ʽ�����е���



//T:����Ԫ�����ͣ�   DF:��T����ת��Ϊ�������ݷ���������
//IsLine��ʾ�������Ի��Ƕ��γ�ͻ����
template <class T, class DF = DFDef<T>, bool IsLine = true>
class HashTable{
public:
	HashTable(size_t capacity = 10)
		:_size(0)
		, _capacity(capacity)
	{
		_table.resize(GetNextPrime(capacity));


	}
	bool Insert(const T& data){
		CheckCapacity();
		//1.ͨ����ϣ�����������ϣ��ַ
		size_t hashAddr = HashFunc(data);
		//2.�Һ���λ��
		int i = 0;
		while (_table[hashAddr]._state == EXIST){
			if (_table[hashAddr]._state == EXIST&&_table[hashAddr]._data == data){
				return false;
			}

			//����̽��
			if (IsLine){
				hashAddr++;
				//��ʽһ
				//hashAddr %= _table.capacity();  //ÿ�ζ�Ҫ����pass��
				//��ʽ����
				if (hashAddr == _table.capacity()){
					hashAddr = 0;
				}
			}

			//��������̽��
			else{
				i++;
				hashAddr = (hashAddr + 2 * i + 1) % _table.capacity();
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
		return true;
	}
	int size(){
		return _size;
	}
	void Swap(HashTable<T, DF, IsLine>& ht){
		_table.swap(ht._table);//���������Ľ�����˵��������Ľ���Ч�ʸߣ��������ʵ���ǽ�����start��finish��end_of_storageָ��
		swap(_size, ht._size);
		_capacity = _table.capacity();
	}
private:
	//������ֱ����vector�����ݻ��ƣ������Ļ������ڵ�Ԫ�ش洢��ʽ���������µĹ�ϣ����
	void CheckCapacity(){

		if (_size * 10 / _table.capacity() == 7){
			//���´���һ����ϣ�����ɹ�ϣ��״̬Ϊ���ڵ�Ԫ�����¹�ϣ����в���


			//1.�´�һ����ϣ��
			HashTable<T, DF, IsLine> newHT(GetNextPrime(_table.capacity()));
			//2.���ɹ�ϣ���е�״̬Ϊ���ڵ�Ԫ�����¹�ϣ����в���
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


