#define _CRT_SECURE_NO_WARNINGS 1
//ZIP:先将语句中重复的语句用LZ77进行压缩---》哈希
//字节上还有重复---Huffman压缩
//以上的压缩算法都是无损的


#include "Hufftree.hpp"
#include "HuffCompress.hpp"



int main(){
	//TestHuffManTree();
	FileCompressHuff fc;
	//fc.CompressFile("testcom.txt");
	fc.UnCompressFile("2.txt");
	return 0;
}