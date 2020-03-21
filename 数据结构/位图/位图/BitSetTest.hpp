#pragma once
#include "common.h"
#include <bitset>

void TestBitSet(){
	std::bitset<100> bt;
	cout <<"start:"<< bt.to_string() << endl;  //to_string 以字符串形式返回该比特串，注顺序反了一下从前往后
	cout << "size:" << bt.size() << endl;     //size返回位图总个个数

	bt.set(12);   //将对应的比特位 置 1
	bt.set(12);   //本来是1的还是1不会变
	bt.set(0);   //将对应的比特位 置 1
	bt.set(20);   //将对应的比特位 置 1
	//bt.set(100);   //会触发越界异常
	cout << "set:" << bt.to_string() << endl;
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