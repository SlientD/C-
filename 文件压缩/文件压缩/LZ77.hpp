#define _CRT_SECURE_NO_WARNINGS 1
#include "common.hpp"
#include "LZHashTable.hpp"

//Q1:实现：<长度，距离>对，占长度1个字节距离2     距离没有必要再长，再长查找效率不高了
//Q1.1:如何判断是长度距离对还是源字符？    来个比特串，0表示源字符，遇到1的时候表示遇到了长度距离对，往后的三个字节都是长度距离对
//Q1.2:最小匹配字符MIN_MATCH :要达到替换要在替换后的字符串比替换前短，所以我这里采用4个字节
//Q1.3:长度范围 [0,255]  因为有MIN_MATACH，所以长度可表示【MIN_MATCH，255+MIN_MATCH】

//Q2:先行缓冲区中的数量什么时候停止匹配？
//考虑这个情况：若最后只剩下几个字符，都有匹配，且下一次加载到缓冲区中的数据中与其紧挨着的也是可以匹配并有可能匹配串达到258
//即窗口末尾中剩余字符比较少，那么本次匹配就暂时不进行，用MIN_LOOKAHEAD来表示先行缓冲区中的待压缩数据剩余到一定量不匹配的字符数
//那么这的MIN_LOOKAHEAD为多少合适？
//MIN_LOOKAHEAD=MAX_MATCH+MIN_MATCH+1  前者保证本次匹配达到最大，后者保证下一次还可以匹配
//如何加载下个数据还能保证匹配到上一次的哪了，将WSIZE2中的数据导入WSIZE1中，从待压缩文件中重新读取一个WSIZE的数据到WSIZE2中，更新哈希表
//所以真正的匹配距离并不是WSIZE,而是MAX_DIST=WSIZE-MIN_LOOKAHEAD???????

//WINDOWS:
class LZ77{
public:
	LZ77();
	~LZ77();
	void CompressFile(const string &strPath);
	void UNCompressFile(const string &strPath);

	void LongMatch(USH matchHead,UCH &curMatchLength,USH &curMatchDist);
	void WriteFlag(FILE* fOut, UCH chFlag, UCH bitCount, bool isChar);
private:
	UCH *_pWin;   //保存待压缩数据的缓冲区
	LZHashTable _ht;

};