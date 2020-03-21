#pragma once
#include "common.h"
#include <bitset>

void TestBitSet(){
	std::bitset<100> bt;
	cout <<"start:"<< bt.to_string() << endl;  //to_string ���ַ�����ʽ���ظñ��ش���ע˳����һ�´�ǰ����
	cout << "size:" << bt.size() << endl;     //size����λͼ�ܸ�����

	bt.set(12);   //����Ӧ�ı���λ �� 1
	bt.set(12);   //������1�Ļ���1�����
	bt.set(0);   //����Ӧ�ı���λ �� 1
	bt.set(20);   //����Ӧ�ı���λ �� 1
	//bt.set(100);   //�ᴥ��Խ���쳣
	cout << "set:" << bt.to_string() << endl;
	cout << "count:" << bt.count() << endl;  //����λ����1�ĸ���
	if (bt.test(12)){       //��λ��1����true ��0����false
		cout << "12 bit is 1" << endl;
	}
	else{
		cout << "12 bit is 0" << endl;
	}

	bt.reset(12);    //��λ��������1��λ����Ϊ0 ��0�Ļ���0
	if (bt.test(12)){       
		cout << "12 bit is 1" << endl;
	}
	else{
		cout << "12 bit is 0" << endl;
	}

	
	
}