#define _CRT_SECURE_NO_WARNINGS 1
#include "LZ77.hpp"
LZ77::LZ77()
:_pWin(new UCH[WSIZE * 2])
, _ht(WSIZE)
{}

LZ77::~LZ77(){
	delete[] _pWin;
	_pWin = nullptr;
}


void LZ77::CompressFile(const std::string& strFilePath){
	//1.打开源文件
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	//2.文件打开失败
	if (nullptr==fIn){
		cout << "open fail" << endl;
		return;
	}
	//获取文件大小   
	fseek(fIn, 0, SEEK_END); //文件指针移动到SEEK_END再偏移0个位置的地方
	ULL fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	//3.如果源文件大小小于MIN_MATCH则不进行处理
	if (fileSize <= MIN_MATCH){
		cout << " file too small" << endl;
		return;
	}

	//从压缩文件中读取一个缓冲区的数据到窗口中;,lookHead表示先行缓冲区的个数
	USH lookAhead=fread(_pWin, 1, 2 * WSIZE, fIn);

	USH hashAddr = 0;
	//设置起始的hashAddr，处理前两个字节
	for (USH i = 0; i < MIN_MATCH - 1; i++){
		_ht.HashFunc(hashAddr, _pWin[i]);
	}

	//压缩：
	FILE* fOUT = fopen("2.lzp", "wr");
	assert(fOUT);
	USH start = 0;   //开始匹配的位置
	USH matchHead = 0;
	UCH curMatchLength = 0;
	USH curMatchDist = 0;
	while (lookAhead){
		//将当前三个字符查到哈希表中，并获取匹配链的头
		_ht.Insert(matchHead, _pWin[start + 2], start, hashAddr);

		//2.验证在查找缓冲区中是否找到匹配
		if (matchHead){
			//顺着匹配链找最长匹配
			//开始找的位置（入参），匹配的长度（出参），匹配的距离（出参）
			LongMatch(matchHead, curMatchLength, curMatchDist);
		}

		//3.验证是否找到匹配
		if (curMatchLength < MIN_MATCH){
			//在查找缓冲区未找到重复的字符串或未找到大于MIN_MATCH的字符串

			//将star位置的字符写入到压缩文件中（1）个
			fputc(_pWin[start], fOUT);
			//写当前源字符对应的标记

			++start;
			lookAhead--;
		}
		else{
			//找到匹配

			//将长度距离对写入到插入文件
			fputc(curMatchDist, fOUT);
			fwrite(&curMatchDist, sizeof(curMatchDist), 1, fOUT);
			//更新先行缓冲区剩余字节数
			lookAhead -= curMatchLength;

			//将已经匹配的字符串按照三个一组查到哈希表中
			--curMatchLength;  //当前字符已经插入了
			while (curMatchLength){
				_ht.Insert(matchHead,_pWin[start],start,hashAddr);


			}
		}

	}
}

void LZ77::LongMatch(USH matchHead, UCH &curMatchLength, USH &curMatchDist){

}

void LZ77::WriteFlag(FILE* fOut, UCH chFlag, UCH bitCount, bool isChar){

}