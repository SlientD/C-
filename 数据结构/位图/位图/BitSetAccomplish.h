#pragma once

#include "common.h"

namespace My_BitSet{
	template<size_t N>
	class bitset{
	public:
		bitset()
			:_bit(N>>3+1)
			, _count(0)
		{}

		//置1
		bitset<N>& set(size_t num){
			if (num >= N){
				cout << "range out!!" << endl;
				return *this;
			}
			size_t index = num / 8;
			size_t pos = num % 8;
			if (!test(num)){
				_count++;
			}
			_bit[index] |= (1 << pos);
			
			return *this;
		}
		//置0：
		bitset<N>& reset(size_t num){
			if (num >= N){
				cout << "range out!!" << endl;
				return *this;
			}
			size_t index = num / 8;
			size_t pos = num % 8;
			if (test(num)){
				_count--;
			}
			_bit[index] &= ~(1 << pos);
			
			return *this;
		}
		bool test(size_t num)const{
			if (num >= N){
				cout << "range out!!" << endl;
				return false;
			}
			size_t index = num / 8;
			size_t pos = num % 8;
			return _bit[index] & (1 << pos);
		}
		//总位数
		size_t size()const{
			return N;
		}
		size_t count()const{
			return _count;
		}
	private:
		vector<unsigned char> _bit;
		size_t _count; 
	};
}

void Test(){
	My_BitSet::bitset<100> bt;
//	cout << "start:" << bt.to_string() << endl;  //to_string 以字符串形式返回该比特串，注顺序反了一下从前往后
	cout << "size:" << bt.size() << endl;     //size返回位图总个个数

	bt.set(12);   //将对应的比特位 置 1
	bt.set(12);   //本来是1的还是1不会变
	bt.set(0);   //将对应的比特位 置 1
	bt.set(20);   //将对应的比特位 置 1
	//bt.set(100);   //会触发越界异常
//	cout << "set:" << bt.to_string() << endl;
	cout << "count:" << bt.count() << endl;  //返回位置是1的个数
	if (bt.test(12)){       //该位是1返回true 是0返回false
		cout << "12 bit is 1" << endl;
	}
	else{
		cout << "12 bit is 0" << endl;
	}

	bt.reset(12);    //复位，即将是1的位置置为0 是0的还是0
	if (bt.test(12)){
		cout << "12 bit is 1" << endl;
	}
	else{
		cout << "12 bit is 0" << endl;
	}
}