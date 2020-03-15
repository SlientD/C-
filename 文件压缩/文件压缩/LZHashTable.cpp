#define _CRT_SECURE_NO_WARNINGS 1

#include "LZHashTable.hpp"

const USH HASH_BITS=15;  //哈希地址位数
const USH HASH_SIZE = (1 << HASH_BITS); //桶数
const USH HASH_MASK = HASH_SIZE - 1;   //掩码保证不会越界

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


//本次的哈希地址是在上一次的基础上计算的
void LZHashTable::HashFunc(USH& hashAddr, UCH ch)
{ 
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK; 
}
USH LZHashTable::H_SHIFT()
{ 
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}



//matchHead为匹配头：当前三个字符在查找缓冲区中找到的最近的一个
//ch为匹串的最后一个字符
//hashAddr:前一次计算出的哈希地址
void LZHashTable::Insert(USH &matchHead, UCH ch,USH pos, USH &hashAddr){
	HashFunc(hashAddr, ch);

	//找当前三个字符在查找缓冲区当中找到的最近的一个：即匹配头
	matchHead = _head[hashAddr];
	//pos可能会超过32K，&MASK的目的就是为了不越界
	_prev[pos&HASH_MASK] = _head[hashAddr];
	_head[hashAddr] = pos;



}