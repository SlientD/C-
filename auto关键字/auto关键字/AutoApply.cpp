#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

int TestAuto()
{
	return 3;
}
////Q5:auto������Ϊ�����Ĳ���
//void TestAuto1(auto a)     //auto�����ڴ˴��ã��������βΣ���Ϊ�������޷���a��ʵ�����ͽ����Ƶ�����������auto��ô��û����ʲô�����ˣ���ʲôֵauto��ʲô���ͣ�
//{
//
//}
int main()
{
	//Q1:c++11�涨��auto����Ϊһ���µ�����ָʾ����ָʾ��������auto�����ı��������ɱ������ڱ���ʱ���Ƶ����á�
	auto a = 1.3;
	int b = 2;
	auto c = b;
	auto d = 'd';
	auto e = TestAuto();
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;
	cout << typeid(e).name() << endl;     //typeid(����).name()������������͵�
	

	//Q2:ʹ��auto�������ʱ���������г�ʼ�����ڱ���׶α�������Ҫ���ݳ�ʼ�����ʽ���Ƶ�auto��ʵ�����͡�
	//auto e;      //��ͨ�������룬��Ϊauto��֪��e��ʲô���ͣ�����޷�����


	//Q3:auto��ָ�����ý�ϣ���auto����ָ������ʱ����auto��auto*û���κ����𣬵���auto������������ʱ������&������&������ͨ���ͱ���
	int x = 1;
	auto px = &x;
	auto *ppx = &x;
	auto& rx = x;
	auto rrx = x;
	

	cout << typeid(px).name() << endl;
	cout << typeid(ppx).name() << endl;
	cout << typeid(rx).name() << endl;
	cout << typeid(rrx).name() << endl;
	rx = 3;
	cout << x << endl;        //x�����˱仯˵��������
	rrx = 2;
	cout << x << endl;        //xδ�����仯��˵����������

	//Q4:auto��ͬһ�ж���������
	//����ͬһ�������������ʱ����Щ������������ͬ�����ͣ�������������ᱨ����Ϊ������ʵ��ֻ�Ե�һ�����ͽ����Ƶ���Ȼ�����Ƶ����������Ͷ�������������
	auto f = 1, g = 2;
	//auto h = 1, i = 2.3; //����ᱨ��h��i���Ͳ�ͬ

	//Q6:auto����ֱ��������������
	int h[] = { 1, 2, 3 };
	//auto t[] = { 4��5��6 };//����ʱ�ᷢ������

	
	
	system("pause");
	return 0;
}