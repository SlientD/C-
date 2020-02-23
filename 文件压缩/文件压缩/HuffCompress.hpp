#pragma once
#include "common.hpp"


typedef struct CharInfo{        //存放每个字符的信息
	CharInfo()
	{

	}
	CharInfo(size_t _count)
	:count(_count)
	{

	}

	CharInfo operator+(CharInfo & x){
		return CharInfo(count + x.count);   //权值是一个charinfo结构体，这里创建的结构体只有count，其他两个属性没有值？？   可以没有用到啥保存啥就可以
	}
	bool operator>(const CharInfo & x)const{
		return count > x.count;
	}

	bool operator==(const CharInfo & x){
		return count == x.count;
	}
	unsigned char ch;                //Q1>>>一共256个字符，如果是char的范围是-128~127   之后的没有办法表达
	string code;     //编码
	size_t count;   //字符个数

	
	
	
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
	//压缩
	void CompressFile(const string &path);
	//解压缩
	void UnCompressFile(const string &path);

private:
	void GenerateCode(HuffManTreeNode<CharInfo> * root);
	void WriteHead(FILE * fIn, const string &path);
	string GetPostFix(const string &str);
	void GetLine(FILE *file, string &str);
private:
	vector<CharInfo> character;         
	//CharInfo* character;//在堆内开辟一整段空间，每个空间存放一个的结构体变量
	//想要搞一个存放结构体指针的数组，创建后在数组中的每个指针在使用的时候都要new一下。。那释放的时候要每个都delete一下吗？？
	//一个数组里存放结构体指针，每一个指针都必须单独开辟空间和释放空间吗？
};
