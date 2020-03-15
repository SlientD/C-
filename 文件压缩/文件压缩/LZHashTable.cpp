#define _CRT_SECURE_NO_WARNINGS 1

#include "LZHashTable.hpp"

const USH HASH_BITS=15;  //��ϣ��ַλ��
const USH HASH_SIZE = (1 << HASH_BITS); //Ͱ��
const USH HASH_MASK = HASH_SIZE - 1;   //���뱣֤����Խ��

LZHashTable::LZHashTable(USH size)
:_prev(new USH[size*2])
, _head(_prev+size)
{
	memset(_prev, 0, size * 2 * sizeof(USH));
}

LZHashTable::~LZHashTable(){
	delete[] _prev;
	_prev = nullptr;
	_head = nullptr;
}


//���εĹ�ϣ��ַ������һ�εĻ����ϼ����
void LZHashTable::HashFunc(USH& hashAddr, UCH ch)
{ 
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK; 
}
USH LZHashTable::H_SHIFT()
{ 
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}



//matchHeadΪƥ��ͷ����ǰ�����ַ��ڲ��һ��������ҵ��������һ��
//chΪƥ�������һ���ַ�
//hashAddr:ǰһ�μ�����Ĺ�ϣ��ַ
void LZHashTable::Insert(USH &matchHead, UCH ch,USH pos, USH &hashAddr){
	HashFunc(hashAddr, ch);

	//�ҵ�ǰ�����ַ��ڲ��һ����������ҵ��������һ������ƥ��ͷ
	matchHead = _head[hashAddr];
	//pos���ܻᳬ��32K��&MASK��Ŀ�ľ���Ϊ�˲�Խ��
	_prev[pos&HASH_MASK] = _head[hashAddr];
	_head[hashAddr] = pos;



}