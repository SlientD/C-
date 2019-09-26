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
string LastWord(const string &str)         //不可返回引用，因为s是临时变量，函数完了以后s所占空间就无效了
{
	string s = str.substr(str.rfind(' ') + 1);
	return s;
}

//Q5:法一：
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
//法二：
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
	//Q1:字符串反转
	cout << "Q1:字符串反转" << endl;
	string s1("hello!");
	Reverse(s1);
	cout << s1 << endl;
	//string库函数中有反转字符串的函数，可直接调用
	reverse(s1.begin(), s1.end());
	cout << s1 << endl;
	cout << endl;


	//Q2:找字符串中第一个只出现一次的字符
	cout << "Q2:找字符串中第一个只出现一次的字符" << endl;
	string s2("abbccsahh");
	char c = FindFirstChar(s2);
	cout << c << endl;
	cout << endl;

	//Q3:字符串里面最后一个单词的长度
	cout << "Q3:字符串里面最后一个单词的长度" << endl;
	string s3;

	while (getline(cin,s3))      //循环输入，  不要用cin 因为cin遇见空格就停止了。但getline读取的是一行
		                         //^Z可以停止  但影响了下一个cin的使用？？？怎么解决
	{
		cout << LastWord(s3) << endl;
	}
	
	
	//Q4:验证一个字符串是不是回文


	//Q5:字符串相加
	cout << "Q5:字符串相加" << endl;
	string s5,s6;
	cin >> s5;
	cin >> s6;
	cout << Add1(s5, s6) << endl;


	system("pause");
	return 0;
}