#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
size_t GetNextPrime(size_t capacty);
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