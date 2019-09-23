#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <malloc.h>
#include <crtdbg.h>


using namespace std;


#if 1
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


//1.4构造函数初始化：在以上构造函数的介绍中，构造函数的作用只是赋初值，赋值可以赋很多次，但是初始化只能在对象创建时初始化一次
// 初始化列表作用：初始化类中的成员变量，并且每个成员变量只能在初始化列表中出现一次
class Time4{

public:
	Time4(int hour=0,int minute=0,int second=0)
		:_hour(hour)
		, _minute(minute)
		, _second(second)
	{
	}



private:
	int _hour;
	int _minute;
	int _second;




};

class Date4
{
public:
	Date4(int year, int month, int day)
		: _year(year)             //在此处给出初始化列表，给每个变量初始化，每个成员变量在初始化列表中只能出现一次因为初始化只能初始化一次
		, _month(month)
		, _day(day)
		, a(10)           //此处a虽然是const值，但是初始化还是可以给值的
		, b(_year)
		, _t(19, 24, 30)
		//在 构造函数体中：赋初值
	{
		
		/*_year = year;
		_month = month;
		_day = day;
		//a = 10;                //不可以赋值的
		*/
	}

private:
	int _year;
	int _month;
	int _day;

	const int a;
	int& b;
	Time4 _t;
};
//const成员变量-a，引用成员变量-b，类类型成员-t（该类没有默认构造函数）类中如果包含以下成员，必须放在初始化列表位置进行初始化

//Q1.5.1成员变量在类中声明次序就是其在初始化列表中的初始化顺序，预期在初始化列表中的先后次序无关

class Date5
{
public:
	Date5(int year,int day)
		: _year(year)
		, _day(day)
		, _month(_day)       //此处_month是随机值，因为是按声明赋值的，此处_day还没有赋值
	{
		cout << this <<_year<<_month<<_day<< endl;

	}


private:
	int _year;
	int _month;
	int _day;
};
// 所以建议：尽量不要使用成员初始化成员
//      初始化列表中成员的出现次序最好与其在类中的声明次序保持一致

//Q1.6 此处引入一个explicit关键字
//说明：因为构造函数不仅可以构造与初始化对象，对于单个参数的构造函数，还具有类型转换的作用。比如
class Date6
{
public:
	Date6(int year)
		: _year(year)
		
	{
		cout << this << _year  << endl;
	}


private:
	int _year;
};
class Date7
{
public:
	explicit Date7(int year)
		: _year(year)

	{
		cout << this << _year << endl;
	}


private:
	int _year;
};


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
	Date4 d41(2011,10,21);
	Date5 d51(2019,9);

	//Q6:用一个整形变量给日期类型对象赋值,实际编译器背后会用2019构造一个无名对象，最后用无名对象给d6对象进行赋值
	Date6 d6(2018);
	d6 = 2019;
	//但是如果这样写，会给人一种d6是变量的感觉，降低了代码的可读性，所以我们要防止单参构造函数的隐式转换。因而引入explicit
	//用法：在函数前加explicit修饰构造函数，将会禁止单参构造函数的隐式转换。注：该关键字修饰单参构造函数才有意义
	Date7 d7(2018);
	//d7 = 2019;   //此处会报错
	
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

#if 0
//4.运算符重载：若想实现两个对象进行加减，肯定不能直接操作，所以可用函数来对对象中的成员变量进行操作。但是每次调函数代码的可读性会很差
//C++为了增强代码的可读性引入了运算符重载，运算符重载是具有特殊函数名的函数，也具有其返回值类型，函数名字以及参数列表，其返回值类型与参数列表与普通的函数类似。
//函数名字为：关键字operator后面接需要重载的运算符符号。 函数原型：返回值类型 operator操作符(参数列表)
//特性：1.不能通过连接其他符号来创建新的操作符：比如operator@
//      2.重载操作符必须有一个类类型或者枚举类型的操作数
//      3.用于内置类型的操作符，其含义不能改变，例如：内置的整型 + ，不 能改变其含义:比如=，可以实现连等，因而加上返回值才能将等号的全部含义
//      4.作为类成员的重载函数时，其形参看起来比操作数数目少1成员函数的
//      5.操作符有一个默认的形参this，限定为第一个形参
//      6.  .*、::、sizeof 、 ? : 、.注意以上5个运算符不能重载。这个经常在笔试选择题中出现

int GetMonthDay(int year,int month)
{
	int Day[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		Day[2] += 1;

	}
	return Day[month];
}

class Date
{
public:
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	//Q1.1;==
	bool operator==(const Date& x)const{
		return _year == x._year&&_month == x._month&&_day == x._day;
	}
	bool operator!=(const Date& x)const{
		return !(_year == x._year&&_month == x._month&&_day == x._day);
	}
	//Q1.2
	bool operator>(const Date& x)const{
		return (_year > x._year||_month > x._month||_day > x._day);
	}
	bool operator<(const Date& x)const{
		return (_year < x._year&&_month < x._month&&_day < x._day);
	}
	bool operator>=(const Date& x)const{
		return !(_year >= x._year&&_month >= x._month&&_day >= x._day);
	}
	bool operator<=(const Date& x)const{
		return !(_year <= x._year&&_month <= x._month&&_day <= x._day);
	}
	//Q2:=,赋值运算符：注意：1.参数类型，返回值返回*this，检查是否自己给自己赋值，
	Date& operator=(const Date& x)
	{
		if (this != &x){
			_year = x._year;
			_month = x._month;
			_day = x._day;
		}
			return *this;             //实现赋值符的连等
	}
	//注！一个类如果没有显示定义赋值运算符重载，编译器也会生成一个，完成对象按字节序的值拷贝（浅拷贝），因而像之前拷贝函数一样，涉及到资源管理，要自己写一个赋值重载


    //Q3:++
	Date& operator++()              //前置++，由于前后++返回值不同，因而可写成两个函数，两个函数通过参数有无实现重载。
	{
		
		_day++;
		if (_day > GetMonthDay(_year, _month))
		{
			_month++;
			_day = 1;
		}
		if (_month>12)
		{
			_year++;
			_month = 1;
		}

		return *this;

	}

	Date operator++(int)            //后置++
	{
		Date tmp(_year,_month,_day);
		_day++;
		if (_day > GetMonthDay(_year, _month))
		{
			_month++;
			_day = 1;
		}
		if (_month>12)
		{
			_year++;
			_month = 1;
		}
		return tmp;

	}
	//Q4:--
	Date& operator--()              //前置++，由于前后++返回值不同，因而可写成两个函数，两个函数通过参数有无实现重载。
	{

		_day--;
		if (_day <=0)
		{
			_month--;
			_day = GetMonthDay(_year,_month);
		}
		if (_month<=0)
		{
			_year--;
			_month = 12;
		}

		return *this;

	}

	Date operator++(int)            //后置++
	{
		Date tmp(_year, _month, _day);
		_day--;
		if (_day <= 0)
		{
			_month--;
			_day = GetMonthDay(_year, _month);
		}
		if (_month <= 0)
		{
			_year--;
			_month = 12;
		}
		return tmp;

	}

	//Q5.1:+,运用到Date类可算一个日期加几天是几号
	Date operator+(int x)
	{
		
		Date tmp = *this;
		if (x<0)
		{
			return (tmp - (0 - x));

		}
		tmp._day += x;
		
		while (tmp._day > GetMonthDay(tmp._year,tmp. _month))
		{
			tmp._day -= GetMonthDay(tmp._year,tmp. _month);
			if (12 == tmp._month)
			{
				tmp._month = 1;
				tmp._year++;
			}
			else{
				tmp._month++;
			}
		}
		
		return tmp;
	}
	//Q5.2-,运用到Date类可算一个日期加减天是几号
	Date operator-(int x)
	{
		Date tmp = *this;
		if (x < 0)
		{
			return (tmp + (0 - x));
		}
		tmp._day -= x;
		while (tmp._day <= 0)
		{
			if (tmp._month <= 1)
			{
				tmp._year--;
				tmp._month = 12;
			}
			else{
				tmp._month--;
			}
			tmp._day += GetMonthDay(tmp._year, tmp._month);

		}
		return tmp;

	}
	//Q6：-，两个日期做差，运用到Date类可算两个日期差几天
	int operator-(const Date &x)const
	{
		Date max = x;
		Date min = *this;
		int t=0;
		if (x._year < _year || x._month < _month || x._day < _day)
		{
			max = *this;
			min = x;
		}
		while (max != min)
		{
			min++;
			t++;
		}
		return t;
	}

//private:

	int _year;
	int _month;
	int _day;

};
    


//Q4.1
//该函数的效果和isEqual相同，这个函数在使用时可以直接使两个date对象x==y来实现判等
//bool operator== (const Date& x, const Date& y)   
//{
//	return (x._day == y._day&&x._month == y._month&&x._year == y._year);
//
//}
//// 这里会发现运算符重载成全局的就需要成员变量是共有的，那么问题来了，封装性如何保证？,因而将其做成成员函数

bool isEqual(const Date& x, const Date& y)
{
	return (x._day == y._day&&x._month == y._month&&x._year == y._year);

}


void TestDate4()
{
	Date d1(2019, 9, 17);
	Date d2(d1++);
	Date d3(++d1);
	Date d4(d1);
	Date d5(2030, 9, 17);
	//cout << (d1 == d4) << endl;     //调用外部 operator== (const Date& x, const Date& y)来赋值
	//以下两种操作都是调用同一个函数
	cout << (d1.operator==(d4)) << endl;
	cout << (d1 == d4) << endl;
	d2 = d4+(-30);
	cout << d2._year<<"-" << d2._month <<"-"<< d2._day << endl;
	int t = d5 - d1;
	cout << t << endl;
}
#endif

int main()
{
	
	
	TestDate1();


	//TestDate2();
	//_CrtDumpMemoryLeaks();  查看内存泄露问题

	//TestDate3();
	//TestDate4();
	system("pause");
	return 0;
}