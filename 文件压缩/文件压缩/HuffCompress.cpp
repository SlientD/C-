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
	//1.���ļ�
	FILE *fd = fopen(path.c_str(), "rb");      //��һ���������ַ������͵�   Ϊʲô�Զ�������ʽ������Ϊ�ı��ļ�FF��ϵͳ����Ϊ�Ƕ������ļ�ĩβ
	if (fd == nullptr){
		assert(false);
		return;
	}
	//2.ͳ�Ƴ����ַ�����
	character.resize(256);
	for (int i = 0; i < 256; i++){
		character[i].ch = i;   //�����±���Ǵ����ĸ��ascֵ
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

	//3.ͨ���ַ�����ΪȨֵ��������������
	HuffManTree<CharInfo> ft(character,CharInfo(0));

	//4.ͨ����������������ÿ���ַ��ı���
	GenerateCode(ft.GetRoot());

	//5.��д�ļ���ͬʱҪ��һЩ�ļ���Ϣ
	//���ڽ�ѹ����ʱ��Ҫ֪����ʲô���������н�ѹ�����������ǻ�Ҫ����һЩ��Ϣ���������ǽ�ѹ��

	FILE *fOut = fopen("2.txt", "wb");
	if (nullptr == fOut){
		assert(false);
	}

	WriteHead(fOut, "2.txt");
	string tmpCode;
	unsigned char ch=0;
	int count = 0;
	fseek(fd, 0,SEEK_SET);       //��Ϊ֮ǰͳ���ַ�����ʱ���ļ�ָ���Ѿ���ĩβ�ˣ�������������Ҫ���������ļ�ָ�뵽�ļ���ͷ���¶�
	while (1){
		memset(buff, 0, 1024);
		readSize = fread(buff, 1, 1024, fd);
		if (0 == readSize){
			break;
		}
		for (int i = 0; i < readSize; i++){
			                       //����һ���Ҳ���ǰ��
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
	//���һ���ֽ����ղ���8������λ����λ����
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
//��ô�������ǽ�ѹ����
//Ҫ��ԭ���Թ����������������л�ԭ���������ֻ��Ҫ��ÿ���ַ����ֵĴ����Ž����Ϳ���
//������������ݣ�Դ�ļ���׺ ��¼�����ַ���Ϣ������    �ַ�������Ϣ-->һ���ַ��ĳ��ִ�������Ϣ
void FileCompressHuff::WriteHead(FILE * fIn, const string &path){
	assert(fIn);
	//д�ļ���׺
	string postfix = GetPostFix(path);
	string InStr = postfix;   //����д����Ϣ
	InStr += "\n";
	
	//д�������ַ�
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
		character[i].ch = i;   //�����±���Ǵ����ĸ��ascֵ
		character[i].count = 0;
	}
	//1.��ȡͷ����Ϣ--�ַ�����
	//1.1�ļ���׺
	string postfix;
	GetLine(fIn, postfix);
	//1.2�ַ���Ϣ��������
	string SLineCount;
	GetLine(fIn, SLineCount);
	int LineCount = atoi(SLineCount.c_str());
	//1.3�ַ���Ϣ
	int total = 0;
	for (int i = 0; i < LineCount; i++){
		string ch;
		GetLine(fIn, ch);
		//���ַ�Ϊ��\n\r��ʱ    ����enter���ǻس�����
		if (ch.empty()){
			ch += "\n";
			GetLine(fIn, ch);
			

		}
		character[(unsigned char)ch[0]].count = atoi(ch.c_str() + 2);    //ch[0]����̫���Ϊ�����������Ч  string����ַ�����char���͵�
		total += character[(unsigned char)ch[0]].count;
	}
	//2.��ԭHuffman��
	HuffManTree<CharInfo> ft(character, CharInfo(0));

	//3.���������������н�ѹ��
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