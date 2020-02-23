#pragma once
#include "common.hpp"


typedef struct CharInfo{        //���ÿ���ַ�����Ϣ
	CharInfo()
	{

	}
	CharInfo(size_t _count)
	:count(_count)
	{

	}

	CharInfo operator+(CharInfo & x){
		return CharInfo(count + x.count);   //Ȩֵ��һ��charinfo�ṹ�壬���ﴴ���Ľṹ��ֻ��count��������������û��ֵ����   ����û���õ�ɶ����ɶ�Ϳ���
	}
	bool operator>(const CharInfo & x)const{
		return count > x.count;
	}

	bool operator==(const CharInfo & x){
		return count == x.count;
	}
	unsigned char ch;                //Q1>>>һ��256���ַ��������char�ķ�Χ��-128~127   ֮���û�а취���
	string code;     //����
	size_t count;   //�ַ�����

	
	
	
}CharInfo;

class FileCompressHuff
{
public:
	/*FileCompressHuff()
		:character(new CharInfo[255])
	{

	}
	~FileCompressHuff()
	{
		delete[] character;
	}*/
	//ѹ��
	void CompressFile(const string &path);
	//��ѹ��
	void UnCompressFile(const string &path);

private:
	void GenerateCode(HuffManTreeNode<CharInfo> * root);
	void WriteHead(FILE * fIn, const string &path);
	string GetPostFix(const string &str);
	void GetLine(FILE *file, string &str);
private:
	vector<CharInfo> character;         
	//CharInfo* character;//�ڶ��ڿ���һ���οռ䣬ÿ���ռ���һ���Ľṹ�����
	//��Ҫ��һ����Žṹ��ָ������飬�������������е�ÿ��ָ����ʹ�õ�ʱ��Ҫnewһ�¡������ͷŵ�ʱ��Ҫÿ����deleteһ���𣿣�
	//һ���������Žṹ��ָ�룬ÿһ��ָ�붼���뵥�����ٿռ���ͷſռ���
};
