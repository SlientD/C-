#define _CRT_SECURE_NO_WARNINGS 1
#include "common.hpp"
#include "LZHashTable.hpp"

//Q1:ʵ�֣�<���ȣ�����>�ԣ�ռ����1���ֽھ���2     ����û�б�Ҫ�ٳ����ٳ�����Ч�ʲ�����
//Q1.1:����ж��ǳ��Ⱦ���Ի���Դ�ַ���    �������ش���0��ʾԴ�ַ�������1��ʱ���ʾ�����˳��Ⱦ���ԣ�����������ֽڶ��ǳ��Ⱦ����
//Q1.2:��Сƥ���ַ�MIN_MATCH :Ҫ�ﵽ�滻Ҫ���滻����ַ������滻ǰ�̣��������������4���ֽ�
//Q1.3:���ȷ�Χ [0,255]  ��Ϊ��MIN_MATACH�����Գ��ȿɱ�ʾ��MIN_MATCH��255+MIN_MATCH��

//Q2:���л������е�����ʲôʱ��ֹͣƥ�䣿
//�����������������ֻʣ�¼����ַ�������ƥ�䣬����һ�μ��ص��������е���������������ŵ�Ҳ�ǿ���ƥ�䲢�п���ƥ�䴮�ﵽ258
//������ĩβ��ʣ���ַ��Ƚ��٣���ô����ƥ�����ʱ�����У���MIN_LOOKAHEAD����ʾ���л������еĴ�ѹ������ʣ�ൽһ������ƥ����ַ���
//��ô���MIN_LOOKAHEADΪ���ٺ��ʣ�
//MIN_LOOKAHEAD=MAX_MATCH+MIN_MATCH+1  ǰ�߱�֤����ƥ��ﵽ��󣬺��߱�֤��һ�λ�����ƥ��
//��μ����¸����ݻ��ܱ�֤ƥ�䵽��һ�ε����ˣ���WSIZE2�е����ݵ���WSIZE1�У��Ӵ�ѹ���ļ������¶�ȡһ��WSIZE�����ݵ�WSIZE2�У����¹�ϣ��
//����������ƥ����벢����WSIZE,����MAX_DIST=WSIZE-MIN_LOOKAHEAD???????

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
	UCH *_pWin;   //�����ѹ�����ݵĻ�����
	LZHashTable _ht;

};