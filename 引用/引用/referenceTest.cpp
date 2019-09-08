#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<time.h>
using namespace std;
//引用是什么？引用不是新定义一个变量，而是给已存在变量取了一个别名，编译器不会为引用变量开辟内存空间，它和它引用的变量共用同一块内存空间。



//Q3：引用做参数时，可实现实参的改变
//如果在函数体内不想改变实参，可开始就将引用设为const如此就不怕无心将原实参值改变
void swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

//Q4：引用作为返回值，返回的变量赢不受函数控制，即函数结束，变量依旧还在，比如全局变量，用户为释放的堆变量，引用变量参数
int& Add(int x, int y)       //返回的是c的引用，然而c只是函数中的变量，会随函数调用完而没有意义
{
	int c = x + y;
	return c;
}
//Q5.函数传值、传址、传引用对比
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
	//传值：
	size_t begin1 = clock();
	for (size_t i = 0; i < 10000; i++)
	{
		Fun1(a);
	}
	size_t end1 = clock();
	//传引用：
	size_t begin2 = clock();
	for (size_t i = 0; i < 10000; i++)
	{
		Fun2(a);
	}
	size_t end2 = clock();
	//传址：
	size_t begin3 = clock();
	for (size_t i = 0; i < 10000; i++)
	{
		Fun3(&a);
	}
	size_t end3 = clock();
	cout << "Fun1 time:" << end1 - begin1 << endl;
	cout << "Fun2 time:" << end2 - begin2 << endl;
	cout << "Fun3 time:" << end3 - begin3 << endl;   //结果传指针和传引用用的时间差不多，原因可以转会汇编观察，传指针和传引用的汇编代码一模一样，编译器对两者的处理方式是一样的
}

int main()
{

	//Q1.引用特性：引用在定义时必须初始化，一个变量可有多个引用，一个引用一旦引用一个实体，就再也不能改变,可通过修改引用，来修改实体的值
	int a = 0;
	//int& ra;     //会出错
	int& ra = a;
	int& rra = a;
	int b = 2;
	cout << a << ra << rra << endl;      //000
	ra = 1;
	cout << a << ra << rra << endl;      //111
	ra = b;
	cout << a << ra << rra << endl;      //222     说明上一句并不是引用的b而是将b的值赋值给ra
	

	//Q2.常引用
	const int c = 1;
	//int& rc = c;     //会报错，因为c是const型，若能给一个int引用，就能通过引用来修改他的值了，便不符合const的特性了，因而不能给常变量一个普通引用
	const int&rc = c;  //这样引用才可以，c就不能通过引用修改了
	//int& con = 9;      //理由同上，9是不能被修改的
	double d = 12.34;
	//int& rd = d;      //会报错，类型不匹配
	const int&rd = d;   //输出12，但此处的rd并不是d的别名，这个过程是先通过取出d的整数，形成一个临时变量放进去，然后rd再引用这个临时变量。由于这个临时变量不知道名字，不知道地址，因此无法修改，所以rd引用前要加const
	

	//Q3.引用做参数
	swap(a, b);
	cout << a << b;

	//Q4引用作为返回值
	int& ret = Add(1, 2);      
	Add(3, 4);              //返回的是函数栈中存放c的空间的引用，而这次改变了了原栈上上一次存放函数中存放c的空间，因而ret改变了
	cout << ret << endl;   //会输出7;

	//Q5.传引用，地址，值的对比：
	Compare();

	system("pause");
	return 0;

}