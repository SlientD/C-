#pragma once
#include <iostream>
#include <bitset>
using namespace std;


template<class K, size_t N, class HS1 = DFStr1, class HS2 = DFStr2, class HS3 = DFStr3, class HS4 = DFStr4, class HS5 = DFStr5>
class BloomFilter{
public:
	BloomFilter()
	{

	}
	void insert(const K &val){
		size_t BitsCount = N*5;
		size_t hashAddr1 = HS1()(val) % BitsCount;
		size_t hashAddr2 = HS2()(val) % BitsCount;
		size_t hashAddr3 = HS3()(val) % BitsCount;
		size_t hashAddr4 = HS4()(val) % BitsCount;
		size_t hashAddr5 = HS5()(val) % BitsCount;
	
		//将对应比特位置1
		_bst.set(hashAddr1);
		_bst.set(hashAddr2);
		_bst.set(hashAddr3);
		_bst.set(hashAddr4);
		_bst.set(hashAddr5);

		++_size;
	}

	//不支持直接删除：元素的比特位上可能有重叠，删除一个可能会影响其他元素
	//如何支持删除：比如一个比特位有n个元素再用，可将底层位图扩展成一个整形数组，整形数组中记录每个比特位被使用的元素个数，多一个使用加一，少一个减一，减为零将比特位置0
	//           缺陷：可能会发生计数回绕，某个比特位被使用次数太多，数字会溢出

	bool find(const K &val){
		size_t BitsCount = N * 5;
		size_t hashAddr = HS1()(val) % BitsCount;
		if (!_bst(hashAddr)){
			return false;
		}
		hashAddr = HS2()(val) % BitsCount;
		if (!_bst(hashAddr)){
			return false;
		}
		hashAddr = HS3()(val) % BitsCount;
		if (!_bst(hashAddr)){
			return false;
		}
		hashAddr = HS4()(val) % BitsCount;
		if (!_bst(hashAddr)){
			return false;
		}
		hashAddr = HS5()(val) % BitsCount;
		if (!_bst(hashAddr)){
			return false;
		}
		return true;
	}

private:
	bitset<5 * N> _bst;
	size_t _size;    //表示布隆过滤器中有效元素个数

};

//布隆过滤器优点：增加查找的时间复杂度为O(K) ，K为哈希函数个数，一般比较小，与数据量大小无关
//             哈希函数之间没有关系，方便硬件并行计算
//             不需要存储元素本身，保密
//             在能够承受一定的误判时，比其他数据结构有优势
//             数据量很大时，不灵过滤器可以表示全体，其他数据结构不行
//             使用同一组散列函数的布隆过滤器可以进行交，并，差运算

//        缺点：无法确定元素是否真的在布隆过滤器中 ，有误判率，存在假阳性（补救方法：再建立一个白名单，存储可能会误判的数据） 
//             通过布隆器无法获得元素本身
//             一般情况下不能从布隆过滤器中直接删除元素
//             如果采用计数删除方式，存在计数回绕问题






