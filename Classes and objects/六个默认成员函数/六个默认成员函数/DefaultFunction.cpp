#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <malloc.h>
#include <crtdbg.h>


using namespace std;


#if 0
class Date
{
};
//一个空类，并不是什么都没有，任何一个类在我们不写的情况下，都自动会生成6个默认函数，下面为这6个函数一一介绍



//Q1.构造函数:主要完成初始化工作，并不是开空间创建对象
//Q1.1特征：1.名字与类名相同；
//      2.不可以有返回值；void也不可以
//      3.对象实例化时由编译器自动调用对应的构造函数，保证每个数据成员都有一个合适的初始值
//      4.并且在对象的生命周期内只调用一次
//      5.构造函数可以重载
//      6. 如果类中没有显式定义构造函数，则C++编译器会自动生成一个无参的默认构造函数，一旦用户显式定义编译器将不再生成


class Date1
	
{
	//如果我们没有写的编译器自动生成了一个无参的默认构造函数
public:
	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};


class Date2{
public:
	//如果用户显示定义了构造函数，编译器将不再生成
	// 无参构造函数
	Date2()
	{}                 //只要有以下的构造函数，就不会生成默认函数，因而不写无参的构造函数，Date2 d这种定义就是错的

	// 带参构造函数
	Date2(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// Q1.2.无参的构造函数和全缺省的构造函数都称为默认构造函数，并且默认构造函数只能有一个（两者只能存在一个）。
	// 注意：无参构造函数、全缺省构造函数、我们没写编译器默认生成的构造函数，都可以认为是默认成员函数。
	//Date2(int year = 2019, int month = 9, int day = 15)       //编译时会报错错误对重载函数的调用不明确	

	//{

	//}

private:
	int _year;
	int _month;
	int _day;
};


//Q1.3此处有个问题，在我们不实现构造函数的情况下，编译器会生成默认的构造函数。但是看起来默认构造函数又没什么用？
//对象调用了编译器生成的默认构造函数，但是对象中year/month/day，依旧是随机值。也就说在这里编译器生成的默认构造函数并没有什么用
//但是看如下代码
class Time
{
public:
	Time()
	{
		cout << "Time()" << endl;
		_hour = 0;
		_minute = 0;
		_second = 0;
	}
private:
	int _hour;
	int _minute;
	int _second;
};


class Date3
{
private:
	// 基本类型(内置类型)
	int _year;
	int _month;
	int _day;
	// 自定义类型
	Time _t;      //在调用Date3构造函数赋默认值时，碰到了_t的类型是自定义类型Time，因而又调用了Time的构造方法，在此构造方法中，给了_t默认值，所以默认的构造函数并不是没什么用
};
//因而对于自定义类型的成员变量，默认构造函数还是起作用的，而对于内置类型，默认构造函数就是赋了个随机值，需要自己写个构造函数，来给初始值


void TestDate1()
{
	Date1 d11;                   //没有定义构造函数，对象也能创建成功，说明此处调用了我们没有写的编译器自动生成的一个无参的默认构造函数
	Date1 d12;
	d12.SetDate(2019, 9, 15);   //每次创建对象都调用该方法设置信息,会很麻烦

	//而使用构造函数，每次在初始化时传参，就可以将原始数据保存进去了
	Date2 d21; // 调用无参构造函数
	Date2 d22(2015, 1, 1); // 调用带参的构造函数，在初始化时就直接存值

	Date2 d23();         //不可以怎么写表示要调用无参构造函数，这样写就变成了返回值为Date2，函数名为d23，无参数列表的函数声明了
	// 注意：如果通过无参构造函数创建对象时，对象后面不用跟括号，否则就成了函数声明

	Date3 d31;       
}
#endif

#if 0
//2.析构函数：对象销毁时会自动调用析构函数，完成类的一些资源的清理工作
//比如在某个函数里创建的对象，对象有在堆上申请空间，这个函数调用完后，对象释放的工作就靠析构函数来做
//特征：1.析构函数名是在类名前加~
//      2.无参数也无返回值，--所以析构函数没有办法实现重载
//      3.一个类有且仅有一个析构函数，若无显示定义，系统就会自动生成默认的析构函数
//      4.对象生命周期结束时，C++编译系统会自动调用析构函数

class Seqlist{
public:
	Seqlist(size_t capcity = 10)
	{
		cout << "SeqList(size_t)" << endl;
		_plist = (int *)malloc(capcity*sizeof(int));
		if (nullptr == _plist)
		{
			assert(0);
			return;
		}
		_size = 0;
		_capcity = capcity;
	}
	~Seqlist()
	{
		cout << "~SeqList()" << endl;        //输出了，说明编译器自动调了。自己写，编译器自动调用
		if (_plist)
		{
			free(_plist);
			_plist = nullptr;
			_capcity = 0;
			_size = 0;

		}

	}

private:
	int *_plist;
	size_t _size;
	size_t _capcity;
};


void TestDate2()
{
	Seqlist list1;
	
}
#endif


#if 0

//拷贝构造函数：用已存在的类类型对象创建新对象
//特性：1.拷贝构造函数是构造函数的一个重载形式
//      2.参数只有一个，且必须引用传参（一般要用const修饰）,用传值方式会引发无穷调用。因为值拷贝会形成临时变量，临时变量要从实参拷贝，所以要再调用拷贝函数，然后就进入了死循环
//      3.在用已存在的类类型创建新对象时由编译器自动调用
//      2.若无显示定义，系统会默认生成拷贝构造函数。默认的拷贝构造函数对象按内存存储按字节序完成拷贝，这种拷贝叫做浅拷贝
class Date{
public:
	
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}


	

public:
	int _year;
	int _month;
	int _day;
};

//特征4解释，着重强调：注意！！！！如果对象设计管理资源，就不能使用浅拷贝
class String
{
public:
	
	String(const char* str="hello")
	{
		_str = (char*)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}
	~String()
	{
		
		
		
			cout << "~String()" << endl;
			free(_str);
		
		
	}
private:
	char* _str;
};

void TestDate3()
{
	//Date d3;
	Date d1(2019,9,17);
	Date d2(d1);          //发生浅拷贝
	cout << d2._year << endl;

	String str1;
	String str2(str1);           //这里发生的也是浅拷贝，将str1的地址给了str2，即str1和str2共用一块内存空间
	          //在函数调用完后，对象要释放，先申请的后释放，后申请的先释放。因而调用完后先释放str2，此时str2指向的内存空间已经无效了，所以到str1释放时，一块内存空间被释放多次会使程序崩溃
	           //if (_str!=nullptr)在释放时加判断也不行，因为地址还存在，只是空间无效了，但是指向还有
}
#endif

//4.赋值运算符重载：

int main()
{

	//TestDate1();


	//TestDate2();
	//_CrtDumpMemoryLeaks();  查看内存泄露问题

	//TestDate3();

	system("pause");
	return 0;
}