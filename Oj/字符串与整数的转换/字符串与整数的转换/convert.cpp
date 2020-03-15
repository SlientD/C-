#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
using namespace std;


int main(){
	//c
	//1.atoi/stoi
	char str[] = "100";
	int num1 = atoi(str);
	cout << "atoi:"<<num1 << endl;
	//2.sprintf/sscanf
	//int sprintf(char *str, const char *format, ...) 发送格式化输出到 str 所指向的字符串
	//用法：sprintf(str, "Pi 的值 = %f", M_PI);
	//      puts(str);
	int num2=20;
	sprintf(str, "%d", num2);       //把num2的值转换成字符串给str
	cout << "sprintf:" << str << endl;

	//int sscanf(const char *str, const char *format, ...) 从字符串读取格式化输入
	//用法
	//int day, year;
	//char weekday[20], month[20], dtm[100];
	//strcpy(dtm, "Saturday March 25 1989");
	//sscanf(dtm, "%s %s %d  %d", weekday, month, &day, &year);
	
	char str2[] = "44";
	sscanf(str2, "%d", &num2);     //把str2的值赋给num2
	cout << "sscanf:" << num2 << endl;

	//c++
	//stringstram
	stringstream s;
	string str = "100";
	int num4;
	s << str;
	s >> num4;
	cout << "stream:" << num4<<endl;

	



	system("pause");
	return 0;
}