#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
//内部类：如果一个类定义在另一个类的内部，这个内部类就叫做内部类。注意此时这个内部类是一个独立的
//类，它不属于外部类，更不能通过外部类的对象去调用内部类。外部类对内部类没有任何优越的访问权限。
//注意：内部类就是外部类的友元类。注意友元类的定义，内部类可以通过外部类的对象参数来访问外部类中
//的所有成员。但是外部类不是内部类的友元。
//特性：1. 内部类可以定义在外部类的public、protected、private都是可以的。
//      2. 注意内部类可以直接访问外部类中的static、枚举成员，不需要外部类的对象 / 类名。但是不能直接用外部类的私有变量
//      3. sizeof(外部类) = 外部类，和内部类没有任何关系。

class Date{

public:
	class Time{
	public:
		void printfD()
		{
			cout << total;
			//cout << _year;   会报错
		}


	private:
		int _hour;
		int _minute;
		int _second;

	};
private:
	int _year;
	int _month;
	int _day;
	static int total;
	
};
int Date::total = 1;
int main(){
	Date d;
	Date::Time x;
	x.printfD();
	cout << sizeof(d) << endl;    //--》12   没有包含内部类的成员变量
	system("pause");
	return 0;
}