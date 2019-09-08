#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<time.h>
using namespace std;
//������ʲô�����ò����¶���һ�����������Ǹ��Ѵ��ڱ���ȡ��һ������������������Ϊ���ñ��������ڴ�ռ䣬���������õı�������ͬһ���ڴ�ռ䡣



//Q3������������ʱ����ʵ��ʵ�εĸı�
//����ں������ڲ���ı�ʵ�Σ��ɿ�ʼ�ͽ�������Ϊconst��˾Ͳ������Ľ�ԭʵ��ֵ�ı�
void swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

//Q4��������Ϊ����ֵ�����صı���Ӯ���ܺ������ƣ��������������������ɻ��ڣ�����ȫ�ֱ������û�Ϊ�ͷŵĶѱ��������ñ�������
int& Add(int x, int y)       //���ص���c�����ã�Ȼ��cֻ�Ǻ����еı��������溯���������û������
{
	int c = x + y;
	return c;
}
//Q5.������ֵ����ַ�������öԱ�
struct A
{
	int a[1000];
};
void Fun1(A a)
{}
void Fun2(A& a)
{}
void Fun3(A* a)
{}
void Compare()
{
	A a = { 1, 23, 10 };
	//��ֵ��
	size_t begin1 = clock();
	for (size_t i = 0; i < 10000; i++)
	{
		Fun1(a);
	}
	size_t end1 = clock();
	//�����ã�
	size_t begin2 = clock();
	for (size_t i = 0; i < 10000; i++)
	{
		Fun2(a);
	}
	size_t end2 = clock();
	//��ַ��
	size_t begin3 = clock();
	for (size_t i = 0; i < 10000; i++)
	{
		Fun3(&a);
	}
	size_t end3 = clock();
	cout << "Fun1 time:" << end1 - begin1 << endl;
	cout << "Fun2 time:" << end2 - begin2 << endl;
	cout << "Fun3 time:" << end3 - begin3 << endl;   //�����ָ��ʹ������õ�ʱ���࣬ԭ�����ת����۲죬��ָ��ʹ����õĻ�����һģһ���������������ߵĴ���ʽ��һ����
}

int main()
{

	//Q1.�������ԣ������ڶ���ʱ�����ʼ����һ���������ж�����ã�һ������һ������һ��ʵ�壬����Ҳ���ܸı�,��ͨ���޸����ã����޸�ʵ���ֵ
	int a = 0;
	//int& ra;     //�����
	int& ra = a;
	int& rra = a;
	int b = 2;
	cout << a << ra << rra << endl;      //000
	ra = 1;
	cout << a << ra << rra << endl;      //111
	ra = b;
	cout << a << ra << rra << endl;      //222     ˵����һ�䲢�������õ�b���ǽ�b��ֵ��ֵ��ra
	

	//Q2.������
	const int c = 1;
	//int& rc = c;     //�ᱨ����Ϊc��const�ͣ����ܸ�һ��int���ã�����ͨ���������޸�����ֵ�ˣ��㲻����const�������ˣ�������ܸ�������һ����ͨ����
	const int&rc = c;  //�������òſ��ԣ�c�Ͳ���ͨ�������޸���
	//int& con = 9;      //����ͬ�ϣ�9�ǲ��ܱ��޸ĵ�
	double d = 12.34;
	//int& rd = d;      //�ᱨ�����Ͳ�ƥ��
	const int&rd = d;   //���12�����˴���rd������d�ı����������������ͨ��ȡ��d���������γ�һ����ʱ�����Ž�ȥ��Ȼ��rd�����������ʱ���������������ʱ������֪�����֣���֪����ַ������޷��޸ģ�����rd����ǰҪ��const
	

	//Q3.����������
	swap(a, b);
	cout << a << b;

	//Q4������Ϊ����ֵ
	int& ret = Add(1, 2);      
	Add(3, 4);              //���ص��Ǻ���ջ�д��c�Ŀռ�����ã�����θı�����ԭջ����һ�δ�ź����д��c�Ŀռ䣬���ret�ı���
	cout << ret << endl;   //�����7;

	//Q5.�����ã���ַ��ֵ�ĶԱȣ�
	Compare();

	system("pause");
	return 0;

}