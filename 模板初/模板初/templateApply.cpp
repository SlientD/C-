#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//Q1:用法
template<typename T>   
void Swap(T &x, T &y)     //之前不同的类型，对应不同的形参列表，所以要写很多个函数，但现在只写一个模板函数，
                          //原理：在编译阶段，编译器可根据传入的实参类型来推演生成对应类型的函数以供调用
{
	T tmp = x;
	x = y;
	y = tmp;
}
//在这个函数中，T只能被替换为一样的类型，若传入参数不同，则编译器其则生成不了匹配的函数，而编译器又不会进行类型转换，因而会报错
//若想要不同类型，可定义两个T
template<class T1, class T2>       //typename可用class代替
void Swap(T1 &x, T2 &y)     
{
	T1 tmp = x;
	x = y;
	y = tmp;
}


int Add(int x, int y)
{
	return x + y;
}


template<typename T>
T Add(const T &x, const T &y)
{
	return x + y;
}
//Q3.3
template<typename T1, typename T2>
T1 Add(const T1 &x, const T2 &y)
{
	return x + y;
}


/*
//Q4.类模板定义格式：
template<class T1,class T2...>
class A                             //A为类模板名，注意：A不是具体的类，是编译器根据被实例化的类型生成具体类的模具
{
	...
};
// 注意：类模板中函数放在类外进行定义时，需要加模板参数列表
template <class T>
A<T>::Function()

//初次使用会在vector容器中使用，详情请见vector实现代码
*/



int main()
{
	//Q1:用法
	int x1=0, y1=1;
	double x2 = 1.0, y2 = 2.0;
	Swap(x1, y1);
	Swap(x2, y2);
	Swap(x1, y2);

	//Q2:函数模板实例化
    //隐式实例化，让编译器根据实参推演模板参数的实际类型
	Add(x1, y1);     //隐式实例化

	//当无法确定T是什么，由该推演成什么的时候，会报错，因而要不然进行强转使传入参数类型相同，要不然进行显式实例化
	Add(x1, (int)y2); //强转
	Add<int>(x1, (int)y2);   //显式实例化，告诉编译器，由模板该推演成什么

	//Q3:非模板函数与同名函数
	//1.一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还可以被实例化为这个非模板函数
	Add(1, 2);    //调用非模板函数，无需模板实例化
	Add<int>(1, 2);//调用编译器特化的模板函数版本   --如果指定类型就必须用木板来生成相应类型

	//2.模板函数不允许自动类型转换，但普通函数可以进行自动类型转换 
	Add(1, 2.0);      //此处会调用非模板函数，发生隐式类型转换   （说明:此处还未加Add(const T1 &x, const T2 &y)函数模板）


	//3.对于非模板函数和同名函数模板，如果其他条件都相同，在调动时会优先调用非模板函数而不会从该模板产生出一个实例。
	//如果模板可以产生一个具有更好匹配的函数， 那么将选择模板
	Add(1, 2.0);        //选择函数模板若选择非模板函数，则会发生隐式类型转化，
	                    //不如调用Add(const T1 &x, const T2 &y)这个实例化的函数形参列表更匹配
	 

	//Q4.类模板
	//类模板实例化需要在类模板名字后跟<>，然后将实例化的类型放在<>中即可，类模板名字不是真正的类，而实例化的结果才是真正的类。
	//A<int> a;



	system("pause");
	return 0;
}