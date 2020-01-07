#define _CRT_SECURE_NO_WARNINGS 1
#include "HuffCompress.hpp"
#include "Hufftree.hpp"
#include <assert.h>
void FileCompressHuff::GenerateCode(HuffManTreeNode<CharInfo> * root){
	if (root == nullptr)
		return;
	if (root->parent != nullptr&&root == root->parent->left){
		root->weight.code = root->parent->weight.code + '1';
		if (root->left==nullptr&&root->right==nullptr)
		character[root->weight.ch].code = root->weight.code;
	}
	
	else if (root->parent != nullptr&&root == root->parent->right)
	{
		root->weight.code = root->parent->weight.code + '0';
		if (root->left == nullptr&&root->right == nullptr)
		character[root->weight.ch].code = root->weight.code;
	}
	
	GenerateCode(root->left);
	GenerateCode(root->right);
}

void FileCompressHuff :: CompressFile(const string &path){
	//1.打开文件
	FILE *fd = fopen(path.c_str(), "rb");      //第一个参数是字符串类型的
	if (fd == nullptr){
		assert(false);
		return;
	}
	//2.统计出现字符个数
	character.resize(256);
	for (int i = 0; i < 256; i++){
		character[i].ch = i;   //数组下标就是存放字母的asc值
		character[i].count = 0;
	}
	char buff[1024] ;
	int readSize = 0;
	while (1){
		memset(buff, 0, 1024);
		readSize=fread(buff, 1, 1024, fd);
		if (0==readSize){
			break;
		}
		for (int i = 0; i < readSize; i++){
			character[buff[i]].count++;
		}
	}

	//3.通过字符个数为权值来创建哈夫曼树
	HuffManTree<CharInfo> ft(character,CharInfo(0));

	//4.通过哈夫曼树来计算每个字符的编码
	GenerateCode(ft.GetRoot());

	//5.改写文件、同时要加一些文件信息
	FILE *fOut = fopen("2.txt", "wb");
	if (nullptr == fOut){
		assert(false);
	}
	string tmpCode;
	char ch=0;
	int count = 0;
	fseek(fd, 0,SEEK_SET);       //因为之前统计字符个数时，文件指针已经到末尾了，所以我们现在要重新设置文件指针到文件开头重新读
	while (1){
		memset(buff, 0, 1024);
		readSize = fread(buff, 1, 1024, fd);
		if (0 == readSize){
			break;
		}
		for (int i = 0; i < readSize; i++){
			                       //有下一个我才往前移
			tmpCode = character[buff[i]].code;
			for (int j = 0; j < tmpCode.size(); j++){
				ch <<= 1;
				if ('1' == tmpCode[j]){
					ch |= 1;
				}
				count++;
				if (8==count){
					fputc(ch,fOut);
					count = 0;
					ch = 0;
				}
				
			}
		}
	}
	if (count > 0){
		ch = ch << (8 - count);
		fputc(ch, fOut);
	}

	fclose(fOut);
	fclose(fd);
}

void FileCompressHuff::UnCompressFile(const string &path){
	



}