#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>

#include <algorithm>        //reverse����ͷ�ļ�  ,oj��Ҳ��ʹ�ø�ͷ�ļ���ֱ�Ӷ� �ַ���/vector���� ���з�ת(ֻҪ��һ������)�������û��Լ�ʵ��

using namespace std;
int main(){
	string str="abc";
	char s[] = "abc";
	reverse(str.begin(), str.end());   //reverse�����Ƿ�ת�����е����ݣ����ַ�������Ч��
	cout << str << endl;
	reverse(&s[1],&s[2]);        //ֵ�ǲ�����ĵ�
	cout << s << endl;

	//_strrev:ʹ�������������ʵ�ֶ��ַ��������ת,ע�����ַ����飬�������鲻���ԣ�
	_strrev(s);
	cout << s << endl;
	
	vector<int> v{ 1, 2, 3 };
	reverse(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << endl;
	}

	


	system("pause");

}