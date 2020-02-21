#define _CRT_SECURE_NO_WARNINGS 1
#include "common.hpp"

const int PRIMECOUNT = 16;
const size_t primeList[PRIMECOUNT] = {
	11ul,53ul, 97ul, 193u, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 39324ul, 786433ul
};

size_t GetNextPrime(size_t capacity){
	for (auto e : primeList){
		if (e > capacity)
		{
			return e;
		}
	}
	return primeList[PRIMECOUNT - 1];
}