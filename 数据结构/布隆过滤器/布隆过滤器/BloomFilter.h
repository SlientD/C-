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
	
		//����Ӧ����λ��1
		_bst.set(hashAddr1);
		_bst.set(hashAddr2);
		_bst.set(hashAddr3);
		_bst.set(hashAddr4);
		_bst.set(hashAddr5);

		++_size;
	}

	//��֧��ֱ��ɾ����Ԫ�صı���λ�Ͽ������ص���ɾ��һ�����ܻ�Ӱ������Ԫ��
	//���֧��ɾ��������һ������λ��n��Ԫ�����ã��ɽ��ײ�λͼ��չ��һ���������飬���������м�¼ÿ������λ��ʹ�õ�Ԫ�ظ�������һ��ʹ�ü�һ����һ����һ����Ϊ�㽫����λ��0
	//           ȱ�ݣ����ܻᷢ���������ƣ�ĳ������λ��ʹ�ô���̫�࣬���ֻ����

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
	size_t _size;    //��ʾ��¡����������ЧԪ�ظ���

};

//��¡�������ŵ㣺���Ӳ��ҵ�ʱ�临�Ӷ�ΪO(K) ��KΪ��ϣ����������һ��Ƚ�С������������С�޹�
//             ��ϣ����֮��û�й�ϵ������Ӳ�����м���
//             ����Ҫ�洢Ԫ�ر�������
//             ���ܹ�����һ��������ʱ�����������ݽṹ������
//             �������ܴ�ʱ��������������Ա�ʾȫ�壬�������ݽṹ����
//             ʹ��ͬһ��ɢ�к����Ĳ�¡���������Խ��н�������������

//        ȱ�㣺�޷�ȷ��Ԫ���Ƿ�����ڲ�¡�������� ���������ʣ����ڼ����ԣ����ȷ������ٽ���һ�����������洢���ܻ����е����ݣ� 
//             ͨ����¡���޷����Ԫ�ر���
//             һ������²��ܴӲ�¡��������ֱ��ɾ��Ԫ��
//             ������ü���ɾ����ʽ�����ڼ�����������






