#pragma once
#include "common.hpp"

class LZHashTable{
public:
	LZHashTable(USH size);

	~LZHashTable();
	void Insert(USH &matchHead, UCH ch, USH pos, USH &hashAddr);
	void HashFunc(USH& hashAddr, UCH ch);


private:
	
	USH H_SHIFT();

private:
	USH *_prev;
	USH *_head;

};