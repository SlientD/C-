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
	FILE *fd = fopen(path.c_str(), "rb");      //��һ���������ַ������͵�
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

	//3.ͨ���ַ�����ΪȨֵ��������������
	HuffManTree<CharInfo> ft(character,CharInfo(0));

	//4.ͨ����������������ÿ���ַ��ı���
	GenerateCode(ft.GetRoot());

	//5.��д�ļ���ͬʱҪ��һЩ�ļ���Ϣ
	FILE *fOut = fopen("2.txt", "wb");
	if (nullptr == fOut){
		assert(false);
	}
	string tmpCode;
	char ch=0;
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
	if (count > 0){
		ch = ch << (8 - count);
		fputc(ch, fOut);
	}

	fclose(fOut);
	fclose(fd);
}

void FileCompressHuff::UnCompressFile(const string &path){
	



}