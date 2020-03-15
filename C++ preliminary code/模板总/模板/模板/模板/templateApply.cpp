#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;


//Q1:
//非类型模板参数
//类型形参：出现在模板参数列表中，跟在class或typename之后的参数类型名称
//非类型形参：用一个常量作为类函数模板的一个参数，在模板中可将参数当成常量来使用

namespace Eg
{

	template <class T,size_t N=10>     //N在下面类中，作为常数使用
	class array{
	public:
		size_t size()const
		{
			//N = 20;      //会报错：错误	1	error C2106: “=”: 左操作数必须为左值,可证明N是常数
			return _size;
		}
	private:
		T _array[N];
		size_t _size;
	};
}

void Test1(){
	Eg::array<int> x;
	x.size();
}
 

void Test2(){

	Eg::array<int,2> x1;
	//注 1、非类型模板参数要在编译期就能确认结果,1+2可以在编译时确认，而a+b不可以
	Eg::array<int, 2+1> x2;
	//int a = 1, b = 2;
	//Eg::array<int, a+b> x3;
	
	//2.浮点数、类对象以及字符串是不允许作为非类型模板参数
	//Eg::array<int, 2.0> x3;
}


//Q2:模板的特化：在原模板类的基础上，针对特殊类型所进行特殊化的实现方式

//2.1函数模板特化:
//使用模板可以实现与类型无关的代码，但对于特殊类型会达不到我们期待的结果，比如比较指针类型
template <class T>
T& MAX_T(T& left, T& right)
{
	return left>right?left:right;
}
//函数模板的特化方式：
//1.要先有一个基础函数模板
//2.关键字template后面接一堆空的尖括号<>
//3.函数名后跟一对尖括号里面放需要特化的类型
//4.函数形参表必须要和模板函数的基础参数类型完全相同，不同的话编译器可能会报一些错误
//比如针对char*类型特化：
template <>
char*& MAX_T<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) == 1)
	{
		return left;
	}
	else{
		return right;
	}
}
//但是一般都是将该函数直接给出，一是实现简单，二是因为函数模板可能会遇到不能处理或者处理有误的类型
template <class T>
const T& MIN_T(const T& left,const T& right)
{
	return left<right ? left : right;
}
template <>
const char*& MIN_T<const char*&>(const char*& left,const char*& right)
{
	if (strcmp(left, right) == -1)
	{
		return left;
	}
	else{
		return right;
	}
}

template<class T>
void TestTemplate(T const & p) //本应是：T const &p 应该是*p不能改变 但最后是p的指向  const int*& p<---错误 int*& const p
{
	*p = 100;

	int b = 20;
//	p = &b;          //会报错：错误 	error C3892: “p”: 不能给常量赋值	

}


void Test3(){
	int x = 2,y=2;
	cout << MAX_T(x, y) << endl;
	char *p1 = "wello";
	char *p2 = "hello";
	cout << MAX_T(p1, p2) << endl;   //输出hello  但应该输出wello 不符合逻辑，因此我们要为char*来特化一个模板提供给这种类型

	const char *p3 = "Hello";
	const char *p4 = "hello";
	cout << MIN_T(p1, p2) << endl;   //不会进入特化函数模板

	int *ip1 = &x;
	TestTemplate(ip1);
}


//2.2类模板特化：分为全特化和偏特化

//全特化：即将模板参数列表中所有的参数都确定了

template<class T1, class T2>
class Data1
{
public:
	Data1() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

template<>
class Data1<int, int>
{
public:
	Data1()
	{
		cout << "Data1<int, int>" << endl;
	}
private:
	int _d1;
	int _d2;
};

void Test4(){
	Data1<int, int> d1;      //用特化模板参数类
	Data1<int, double> d2;
}

//偏特化：有两种表现：部分特化和参数更进一步的限制
template<class T1, class T2>
class Data2
{
public:
	Data2() { cout << "Data2<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

// 部分特化：将模板参数列表中部分参数类型化
template<class T1>
class Data2<T1, int>
{
public:
	Data2()
	{
		cout << "Data2<T1, int>" << endl;
	}

private:
	T1 _d1;
	int _d2;
};


// 偏特化：让模板参数列表中的类型限制更加严格
template<class T1, class T2>
class Data2<T1*, T2*>
{
public:
	Data2()
	{
		cout << "Data2<T1*, T2*>" << endl;
	}
private:
	T1* _d1;
	T2* _d2;
};

void Test5(){					 
	Data2<int, int> d1;      //用部分特化模板参数类
	Data2<double, int> d2;   //用部分特化模板参数类     因为后面的都是int，都符合这个部分特化模板
	Data2<int, double> d3;
	Data2<double, double> d4;



	Data2<int*, int> d5;
	Data2<int, int*> d6;
	Data2<int*, int*> d7;
	Data2<int*, double*> d8;
}

// 写一个通用的拷贝函数，要求：效率尽可能高
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* str = new char[strlen(s._str) + 1];
			strcpy(str, s._str);
			delete[] _str;
			_str = str;
		}
		return *this;
	}

	~String()
	{
		delete[] _str;
	}

private:
	char* _str;
};


/*Way1：
//String：用该函数会报错拷贝的是地址，析构会对同一块空间释放两次，会报错
template<class T>
void Copy(T* dst, T* src, size_t size)
{
memcpy(dst, src, sizeof(T)*size);
}
*/

//因而要区分自定义和内置类型，来调用使用不同的方法进行拷贝
/*
//Way2：增加函数判定 区分自定义和内置类型
bool IsPodType(const char* strType){
	const char* arrType[] = { "char", "short", "int", "long", "long long", "float","double", "long double" };
	for (size_t i = 0; i < sizeof(arrType) / sizeof(arrType[0]); ++i)      //每次都要遍历，效率太低！
	{
		if (0 == strcmp(strType, arrType[i]))
			return true;
	}
	return false;
}

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if (IsPodType(typeid(T).name()))
	{
		memcpy(dst, src, sizeof(T)*size);
	}
	else{
		for (int i = 0; i < size; i++)
		{
			dst[i] = src[i];
		}
	}
}
*/


//Way3:萃取类型
struct TrueType{
	static bool Get(){     //只有静态才能用 ::  访问
		return true;
	}
};
struct FlaseType{
	static bool Get(){
		return false;
	}
};
template<class T>
struct TypeTraits{
	typedef FlaseType IsPodeType;
};
//对上述模板进行实例化，将内置类型都特化
template<>
struct TypeTraits<int>{
	typedef TrueType IsPodeType;
};
template<>
struct TypeTraits<double>{
	typedef TrueType IsPodeType;
};


template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if (TypeTraits<T>::IsPodeType::Get())
	{
		memcpy(dst, src, sizeof(T)*size);
	}
	else{
		for (int i = 0; i < size; i++)
		{
			dst[i] = src[i];
		}
	}
}



void TestCopy()
{
	int array1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int array2[10];
	Copy(array2, array1, 10);

	String s1[3] = { "1111", "2222", "3333" };
	String s2[3];            
	Copy(s2, s1, 3);
}

#include "CompilingTest.h"
void TestCompiling()
{
	Add(1, 1);   //会发生报错
}


int main(){
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//TestCopy();
	TestCompiling();

	system("pause");

}