#define _CRT_SECURE_NO_WARNINGS 1
#include "classApply.h"

//Q1:先引入结构体定义，在c语言中，结构体只能定义变量，而在C++中，结构体不仅可以定义变量，也可以定义函数
struct Student
{
	// 成员函数 || 行为
	void SetStudentInfo(const char * name, const char * gender, int age)        //结构体里的函数，定义出来一个结构体对象后，这个函数成员就可以被对象调用了
	{
		strcpy(_name, name);
		strcpy(_gender, gender);
		_age = age;
	}
	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;

	}
	//成员变量 || 属性
	char _name[20];           //成员变量名要和成员函数的形参名区分开来，一般成员名前要加下划线，第一为了避免冲突，第二为了整齐，让人一看这就是成员变量名       
	char _gender[3];
	int _age;
};//分号记得

//Q2:在C++中，这种类型的结构体更喜欢用class类来代替，下面引入class的定义
//Q2.1第一种定义方式，成员函数的声明和定义都放在类体中，注意：成员函数如果在类中定义，编译器可能将其当做内联函数处理
class Person1{
public:
	void SetPersonInfo(const char * name, const char * gender, int age)        //结构体里的函数，定义出来一个结构体对象后，这个函数成员就可以被对象调用了
	{
		strcpy(_name, name);
		strcpy(_gender, gender);
		_age = age;
	}
	void PrintPersonInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}
private:
	char *_name;
	char *_gender;
	int _age;
};
//Q2.2第二种定义方式，成员函数声明放到.h中，类的定义放到.cpp文件中:看classApply.h和classApply.cpp


//Q3：C++是面向对象语言，面相对象程序：封装  继承  多态

// 封装概念：将一个事物的内部实现细节隐藏起来，提供一个公有接口让对象之间进行交互
// C++实现封装：类(通过类将对象的属性和行为包装在一起)+访问权限：private  protected  public
// public: 被public修饰的成员，可以直接在类外被访问
// protected/private: 不能直接在类外进行访问
//访问限定符作用域从该访问限定符出现位置到下一个访问出现符出现为止

//struct和class的区别就是，struct默认访问方式是public，class的默认访问方式是private


//Q4:类的作用域：类定义了一个新的作用域，类的所有成员都在类的作用域中。类体外定义的成员，需要使用::作用域解析符指明成员属于哪个类
//用法见类的定义方式Q2.2



//Q5.类的实例化：类只是一个模型一样的东西，定义出一个类并没有分配实际的内存空间来存储他。
//一个类可以实例化出多个对象，实例化的对象占用实际的物理空间，存储类成员和变量
//类（描述对象的特征和行为）-》实例化-》对象（实实在在存在的实体，会占物理空间），打个比方，类就是一个图纸，对象是实实在在的房子，通过一个图纸，可以盖很多和图纸一样的房子
Student s1, s2, s3;   //实例化了3个成员

//Q6.为什么在类中可以先在成员函数中使用变量后定义？
//这就要看编译器如何处理类了：编译器会先识别类名，在识别类中的成员变量，最后识别类中的函数然后进行改写。因而变量后定义也没关系



//Q7.3
class A1
{
public:
	void f1();
private:
	int _a;
};
class A2   //只有成员函数
{
public:
	void f2();
};
class A3     //空类
{

};

//Q8.this指针，Q7.2所说，调用成员函数的时候，编译器会传一个隐藏的指向对象指针给成员函数，这个指针就是this
//Q8.1.拿Date类来说
class Date
{
public:
	void Show()
	{
		cout << _year << " " << _month << " " << _day << endl;
	}
	void SetDate(int year, int month, int day)
	{
		_year = year;      //此处经编译器处理后实际上是this->_year=year,this的指向是调用此函数的对象，由此对对象里的内容进行了修改
		_month = month;  
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;
};
//Q8.2.this指针可以为空吗？
class A
{
public:
	void Print()
	{
		cout << _a << endl;     //在此处崩溃，因为在此处编译器会改写为this->_a  this又等于p，p为空又无法解引用，因而崩掉了
	}
	void Show()
	{
		cout << "Show()" << endl;
	}
private:
	int _a;
};

//由上述例子，this指针可以为空，但是不可以访问、使用其成员，因为空无指向


//Q8.3总结this有以下特性：
//1.this指针的类型：类的类型*const，是一个指向对象自己的常量指针，不能给this赋值
//2.只能在成员内部使用
//3.this本质是一个函数的形参，对象的地址作为实参传递给this，由编译器通过ecx寄存器传递，不需要用户自己传递
//4.静态函数中没有this指针

//Q8.4this指针存在哪里？
//this指针会因编译器不同，而放置的位置不同。可能是栈，也可能是寄存器，甚至全局变量。

//Q8.5并不是所有this都由ecx寄存器传递，比如不定参数中的this是通过压栈传递的，具体怎么调用要看函数约定，
//可通过写函数声明，不写函数定义时的报错看函数用的是那一条函数约定。









int main()
{

	Student s;                 //在C++中，此处Student就可以表示定义的结构体了，不用像c中一样，还要带上struct，或者还要用typedef再重新给个名字。。
	s.SetStudentInfo("Peter", "nan", 18);
	s.PrintStudentInfo();

	Person2 people;
	people.SetPersonInfo("liming", "nan", 19);
	people.PrintPersonInfo();


	//Q7:类对象大小的计算
	//Q7.1 一个类中有成员变量和成员函数，一个类的对象中是否包含什么？
	cout << sizeof(s) << endl;//->28
	//三个成员变量通过内存对齐在内存中所占大小的确实是28个字节
	//所以得出结论：对象在内存中只保留成员变量，成员函数放在公共的代码段,一个类的大小实际上就是该类中成员变量之和，当然也要进行内存对齐
	//Q7.2那么问题又来了，若每个对象调用的都是一个成员函数，那么函数怎么知道是修改的是哪个对象？
    //其实，这类似于我们通过函数修改结构体变量，我们会将结构体的指针传过去，告诉函数我们要修改哪个结构体变量，只不过此处是编译器隐藏传址
	
	//Q7.3空类型大小
	cout << sizeof(A1) << endl;    //4
	cout << sizeof(A2) << endl;    //1
	cout << sizeof(A3) << endl;    //1  
	//在主流编译器中空类所占大小为1B，因为要区分空类定义的对象，空类同样可以被实例化，每个实例在内存中都有一个独一无二的地址，为了达到这个目的，
	//编译器往往会给一个空类隐含的加一个字节，这样空类在实例化后在内存得到了独一无二的地址，所以空类所占的内存大小是1个字节。

	//8.2测试
	A *p = NULL;
	p->Show();    
	p->Print();     //程序会在打印出崩溃，p作为参数传进去给了this

	



	system("pause");
	return 0;
}






