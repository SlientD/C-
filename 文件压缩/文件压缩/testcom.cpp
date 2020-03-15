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
	FILE *fd = fopen(path.c_str(), "rb");      //第一个参数是字符串类型的   为什么以二进制形式读？因为文本文件FF会系统会以为是读到了文件末尾
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
	unsigned char buff[1024] ;
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
	//由于解压缩的时候，要知道按什么规则来进行解压缩，所以我们还要保存一些信息来帮助我们解压缩

	FILE *fOut = fopen("2.txt", "wb");
	if (nullptr == fOut){
		assert(false);
	}

	WriteHead(fOut, "2.txt");
	string tmpCode;
	unsigned char ch=0;
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
	//最后一个字节若凑不够8个比特位，移位保存
	if (count > 0){
		ch = ch << (8 - count);
		fputc(ch, fOut);
	}
	
	
    
	fclose(fOut);
	fclose(fd);
}
string FileCompressHuff::GetPostFix(const string &str){
	return str.substr(str.rfind('.'));
}
//怎么帮助我们解压缩？
//要还原可以哈夫曼树来对他进行还原，因而我们只需要把每个字符出现的次数放进来就可以
//其他保存的内容：源文件后缀 记录关于字符信息的行数    字符次数信息-->一个字符的出现次数的信息
void FileCompressHuff::WriteHead(FILE * fIn, const string &path){
	assert(fIn);
	//写文件后缀
	string postfix = GetPostFix(path);
	string InStr = postfix;   //保存写的信息
	InStr += "\n";
	
	//写行数和字符
	size_t count = 0;
	char trans[32];
	string ChStr;
	for (int i = 0; i < 256; i++){
		if (character[i].count>0){
			count++;
			ChStr += character[i].ch;
			ChStr += ':';
			_itoa(character[i].count, trans, 10);
			ChStr += trans;
			ChStr += '\n';
		}

	}
	_itoa(count, trans, 10);
	InStr += trans;
	InStr += '\n';
	InStr += ChStr;
	fwrite(InStr.c_str(), 1, InStr.size(), fIn);
}
void FileCompressHuff::GetLine(FILE *file, string &str){
	assert(file);
	unsigned char ch;
	while (!feof(file)){
		ch = fgetc(file);
		if (ch == '\n')
			return;
		str += ch;
	}
}
void FileCompressHuff::UnCompressFile(const string &path){
	FILE *fIn = fopen(path.c_str(), "rb");
	assert(fIn);
	character.resize(256);
	for (int i = 0; i < 256; i++){
		character[i].ch = i;   //数组下标就是存放字母的asc值
		character[i].count = 0;
	}
	//1.获取头部信息--字符次数
	//1.1文件后缀
	string postfix;
	GetLine(fIn, postfix);
	//1.2字符信息的总行数
	string SLineCount;
	GetLine(fIn, SLineCount);
	int LineCount = atoi(SLineCount.c_str());
	//1.3字符信息
	int total = 0;
	for (int i = 0; i < LineCount; i++){
		string ch;
		GetLine(fIn, ch);
		//当字符为‘\n\r’时    按下enter键是回车换行
		if (ch.empty()){
			ch += "\n";
			GetLine(fIn, ch);
			

		}
		character[(unsigned char)ch[0]].count = atoi(ch.c_str() + 2);    //ch[0]可能太大变为负数，变得无效  string存的字符都是char类型的
		total += character[(unsigned char)ch[0]].count;
	}
	//2.还原Huffman树
	HuffManTree<CharInfo> ft(character, CharInfo(0));

	//3.依靠哈夫曼树进行解压缩
	FILE* fOut = fopen("3.txt", "w");
	HuffManTreeNode<CharInfo> Node;
	HuffManTreeNode<CharInfo> *pCur=ft.GetRoot();
	assert(fOut);
	unsigned char buff[1024];
	string Instr;


	while (1){
		memset(buff, 0, sizeof(buff));
		int read = fread(buff, 1, 1024, fIn);
		if (0 == read){
			break;
		}
		for (int cpos = 0; cpos < read; cpos++){
				
				for (int inpos = 0; inpos < 8; inpos++){
					
					if (1 == (buff[cpos] & 0x80) >> 7){
						pCur = pCur->left;
					}
					else if (0 == (buff[cpos] & 0x80) >> 7){
						pCur = pCur->right;
					}
					else{
						printf("error\n");
						return;
					}
					if (pCur->left == nullptr&&pCur->right == nullptr){
						if (total == 0)
							break;
						Instr += pCur->weight.ch;
						pCur = ft.GetRoot();
						total--;
					}
					buff[cpos] <<= 1;
				}
			}
			
			
		

	}
	fwrite(Instr.c_str(), Instr.size(), 1, fOut);


	fclose(fIn);
	fclose(fOut);
}