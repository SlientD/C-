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
	//int sprintf(char *str, const char *format, ...) ���͸�ʽ������� str ��ָ����ַ���
	//�÷���sprintf(str, "Pi ��ֵ = %f", M_PI);
	//      puts(str);
	int num2=20;
	sprintf(str, "%d", num2);       //��num2��ֵת�����ַ�����str
	cout << "sprintf:" << str << endl;

	//int sscanf(const char *str, const char *format, ...) ���ַ�����ȡ��ʽ������
	//�÷�
	//int day, year;
	//char weekday[20], month[20], dtm[100];
	//strcpy(dtm, "Saturday March 25 1989");
	//sscanf(dtm, "%s %s %d  %d", weekday, month, &day, &year);
	
	char str2[] = "44";
	sscanf(str2, "%d", &num2);     //��str2��ֵ����num2
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