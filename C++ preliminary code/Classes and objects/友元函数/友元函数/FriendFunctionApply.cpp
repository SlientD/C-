#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

#if 0
//友元函数：它是定义在类外部的普通函数，友元函数可以直接访问类的私有成员，不属于任何类，
//          但需要在类的内部声明，声明时需要加friend关键字。

//友元函数的应用：
//现在我们尝试去重载operator<<，然后发现我们没办法将operator<<重载成成员函数。因为cout的
//输出流对象和隐含的this指针在抢占第一个参数的位置。this指针默认是第一个参数也就是左操作数了。但是
//实际使用中cout需要是第一个形参对象，才能正常使用。所以我们要将operator << 重载成全局函数。但是这
//样的话，又会导致类外没办法访问成员，那么这里就需要友元来解决。operator >> 同理。
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
		
	}

	Date(const Date& d)
		: _year(d._year)
		, _month(d._month)
		, _day(d._day)
	{}
	friend ostream& operator<<(ostream& _cout, const Date& d);
	friend istream& operator>>(istream& _cin, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day ;
	return _cout;
}
istream& operator>>(istream& _cin, Date& d)
{
	_cin >> d._year; _cin >> d._month;_cin >> d._day;
	return _cin;
}

int main()
{
	Date d(1999, 10, 20);

	cout << d << endl<<d<<endl;
	cin >> d;
	cout << d << endl;
	system("pause");
	return 0;
}
#endif
//友元函数可访问类的私有成员，但不是类的成员函数.有this指针传入才是成员函数
//友元函数不能用const修饰。因为const修饰的是this
//友元函数可以在类定义的任何地方声明，不受类访问限定符限制。比如endl
//一个函数可以是多个类的友元函数
//友元函数的调用与普通函数的调用和原理相同。比如：有多少个实参，就有多少个形参在接



//友元类：友元类的所有成员函数都可以是另一个类的友元函数，都可以访问另一个类中的非公有成员。
//注意：
//1.友元关系是单向的，不具有交换性。
//比如上述Time类和Date类，在Time类中声明Date类为其友元类，那么可以在Date类中直接访问Time
//类的私有成员变量，但想在Time类中访问Date类中私有的成员变量则不行。
//2.友元关系不能传递
//如果B是A的友元，C是B的友元，则不能说明C时A的友元。


class Date; // 前置声明
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	void SetTimeOfDate(int hour, int minute, int second)
	{
		// 直接访问时间类私有的成员变量
		_t._hour = hour;
		_t._minute = minute;
		_t._second = second;
	}

private:
	int _year;
	int _month;
	int _day;
	Time _t;
};
class Time
{
	friend class Date; // 声明日期类为时间类的友元类，则在日期类中就直接访问Time类中的私有成员变量.但是在Time中不能用Date中的私有成员变量
public:
	Time()
	{}
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{}

private:
	int _hour;
	int _minute;
	int _second;
};

