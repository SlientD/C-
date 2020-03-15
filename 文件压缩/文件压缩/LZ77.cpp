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
	//1.��Դ�ļ�
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	//2.�ļ���ʧ��
	if (nullptr==fIn){
		cout << "open fail" << endl;
		return;
	}
	//��ȡ�ļ���С   
	fseek(fIn, 0, SEEK_END); //�ļ�ָ���ƶ���SEEK_END��ƫ��0��λ�õĵط�
	ULL fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	//3.���Դ�ļ���СС��MIN_MATCH�򲻽��д���
	if (fileSize <= MIN_MATCH){
		cout << " file too small" << endl;
		return;
	}

	//��ѹ���ļ��ж�ȡһ�������������ݵ�������;,lookHead��ʾ���л������ĸ���
	USH lookAhead=fread(_pWin, 1, 2 * WSIZE, fIn);

	USH hashAddr = 0;
	//������ʼ��hashAddr������ǰ�����ֽ�
	for (USH i = 0; i < MIN_MATCH - 1; i++){
		_ht.HashFunc(hashAddr, _pWin[i]);
	}

	//ѹ����
	FILE* fOUT = fopen("2.lzp", "wr");
	assert(fOUT);
	USH start = 0;   //��ʼƥ���λ��
	USH matchHead = 0;
	UCH curMatchLength = 0;
	USH curMatchDist = 0;
	while (lookAhead){
		//����ǰ�����ַ��鵽��ϣ���У�����ȡƥ������ͷ
		_ht.Insert(matchHead, _pWin[start + 2], start, hashAddr);

		//2.��֤�ڲ��һ��������Ƿ��ҵ�ƥ��
		if (matchHead){
			//˳��ƥ�������ƥ��
			//��ʼ�ҵ�λ�ã���Σ���ƥ��ĳ��ȣ����Σ���ƥ��ľ��루���Σ�
			LongMatch(matchHead, curMatchLength, curMatchDist);
		}

		//3.��֤�Ƿ��ҵ�ƥ��
		if (curMatchLength < MIN_MATCH){
			//�ڲ��һ�����δ�ҵ��ظ����ַ�����δ�ҵ�����MIN_MATCH���ַ���

			//��starλ�õ��ַ�д�뵽ѹ���ļ��У�1����
			fputc(_pWin[start], fOUT);
			//д��ǰԴ�ַ���Ӧ�ı��

			++start;
			lookAhead--;
		}
		else{
			//�ҵ�ƥ��

			//�����Ⱦ����д�뵽�����ļ�
			fputc(curMatchDist, fOUT);
			fwrite(&curMatchDist, sizeof(curMatchDist), 1, fOUT);
			//�������л�����ʣ���ֽ���
			lookAhead -= curMatchLength;

			//���Ѿ�ƥ����ַ�����������һ��鵽��ϣ����
			--curMatchLength;  //��ǰ�ַ��Ѿ�������
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