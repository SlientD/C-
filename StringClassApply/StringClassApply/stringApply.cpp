#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

//Q1:
void Reverse(string &s)
{
	size_t start = 0;
	size_t end = s.size()-1;
	char tmp;
	while (start < end){
		tmp = s[start];
		s[start] = s[end];
		s[end] = tmp;
		start++;
		end--;
	}
}

//Q2:
char FindFirstChar(const string &str)
{
	int count[256] = { 0 };
	int pos = 0;
	for (pos; pos < str.size();pos++)
	{
		count[str[pos]]++;
	}
	for (pos=0; pos < str.size(); pos++)
	{
		if (count[str[pos]] == 1){
			return str[pos];
		}
		
	}
	return NULL;

}

//Q3:
string LastWord(const string &str)         //���ɷ������ã���Ϊs����ʱ���������������Ժ�s��ռ�ռ����Ч��
{
	string s = str.substr(str.rfind(' ') + 1);
	return s;
}

//Q5:��һ��
string Add(const string &str1, const string &str2)
{
	int size1 = str1.size()-1;
	int size2 = str2.size()-1;
	int size = (size1 > size2 ? size1 : size2)+1;
	int flag = 0;
	int d;
	string str(size+1, '0');
	while (size1 >= 0 && size2 >= 0)
	{
		d = str1[size1] + str2[size2] + flag-2*'0';
		flag = 0;
		if (d >= 10)
		{
			flag = 1;
			d = d % 10;
		}
		str[size] += d;
		size1--;
		size2--;
		size--;
	}
	while (size1 >= 0)
	{
		d = str1[size1] + flag-'0';
		flag = 0;
		if (d >= 10)
		{
			flag = 1;
			d = d % 10;
		}
		str[size] += d;
		size1--;
		size--;
	}
	while (size2 >= 0)
	{
		d = str2[size2] + flag -  '0';
		flag = 0;
		if (d >= 10)
		{
			flag = 1;
			d = d % 10;
		}
		str[size] += d;
		size2--;
		size--;
	}
	if (flag == 1)
	{
		str[0] +=1;
	}
	else if (flag==0)
	{
		str.erase(0, 1);
	}
	return str;
}
//������
string Add1(string &str1, string &str2)
{
	int size1 = str1.size() - 1;
	int size2 = str2.size() - 1;
	int size = (size1 > size2 ? size1 : size2) + 1;
	int flag = 0;
	char c;
	string str(size + 1, '0');
	if (size1 < size2){
		swap(size1, size2);
		swap(str1, str2);
	}
	for (; size1 >= 0; size1--,size2--)
	{
		c = str1[size1]+ flag ;
		if (size2>=0)
		{
			c += str2[size2] - '0';
		}
		flag = 0;
		if (c >= 10+'0')
		{
			flag = 1;
			c-=10;
		}
		str[size] = c;
		size--;
	}
	
	if (flag == 1)
	{
		str[0] += 1;
	}
	else if (flag == 0)
	{
		str.erase(0, 1);
	}
	return str;
}

int main()
{
	//Q1:�ַ�����ת
	cout << "Q1:�ַ�����ת" << endl;
	string s1("hello!");
	Reverse(s1);
	cout << s1 << endl;
	//string�⺯�����з�ת�ַ����ĺ�������ֱ�ӵ���
	reverse(s1.begin(), s1.end());
	cout << s1 << endl;
	cout << endl;


	//Q2:���ַ����е�һ��ֻ����һ�ε��ַ�
	cout << "Q2:���ַ����е�һ��ֻ����һ�ε��ַ�" << endl;
	string s2("abbccsahh");
	char c = FindFirstChar(s2);
	cout << c << endl;
	cout << endl;

	//Q3:�ַ����������һ�����ʵĳ���
	cout << "Q3:�ַ����������һ�����ʵĳ���" << endl;
	string s3;

	while (getline(cin,s3))      //ѭ�����룬  ��Ҫ��cin ��Ϊcin�����ո��ֹͣ�ˡ���getline��ȡ����һ��
		                         //^Z����ֹͣ  ��Ӱ������һ��cin��ʹ�ã�������ô���
	{
		cout << LastWord(s3) << endl;
	}
	
	
	//Q4:��֤һ���ַ����ǲ��ǻ���


	//Q5:�ַ������
	cout << "Q5:�ַ������" << endl;
	string s5,s6;
	cin >> s5;
	cin >> s6;
	cout << Add1(s5, s6) << endl;


	system("pause");
	return 0;
}