#define _CRT_SECURE_NO_WARNINGS 1
//ZIP:�Ƚ�������ظ��������LZ77����ѹ��---����ϣ
//�ֽ��ϻ����ظ�---Huffmanѹ��
//���ϵ�ѹ���㷨���������


#include "Hufftree.hpp"
#include "HuffCompress.hpp"



int main(){
	//TestHuffManTree();
	FileCompressHuff fc;
	//fc.CompressFile("testcom.txt");
	fc.UnCompressFile("2.txt");
	return 0;
}