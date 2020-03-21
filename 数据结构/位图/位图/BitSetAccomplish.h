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

		//��1
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
		//��0��
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
		//��λ��
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
//	cout << "start:" << bt.to_string() << endl;  //to_string ���ַ�����ʽ���ظñ��ش���ע˳����һ�´�ǰ����
	cout << "size:" << bt.size() << endl;     //size����λͼ�ܸ�����

	bt.set(12);   //����Ӧ�ı���λ �� 1
	bt.set(12);   //������1�Ļ���1�����
	bt.set(0);   //����Ӧ�ı���λ �� 1
	bt.set(20);   //����Ӧ�ı���λ �� 1
	//bt.set(100);   //�ᴥ��Խ���쳣
//	cout << "set:" << bt.to_string() << endl;
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