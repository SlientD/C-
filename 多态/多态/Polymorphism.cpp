#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
//说明：以下代码是在vs 2013下x86环境下运行的，涉及的指针所占空间大小都是4Byte
//Q1:多态作用：在继承条件下，可通过不同的子类去调用基类中的同一个函数，但会产生不同结果
// 多态的体现：代码编译时，不能确定到底调用那个类的虚函数
//           在代码运行时，根据指针所指向的实际对象选择调用对应类的虚函数

//例如以下继承关系
class Person1{
public:
	Person1(const string& name)
	:_name(name)
	{

	}
	void BuyTicket(){
		cout << "买全价票" << endl;
	}
protected:
	string _name;
};
class Student1:public Person1{
public:
	Student1(const string &name, const string &stuid)
		:Person1(name)
		, _stuid(stuid)
	{

	}
	void BuyTicket(){
		cout << "买半价票" << endl;
	}
protected:
	string _stuid;
};
class Soldier1 :public Person1{
public:
	Soldier1(const string &name, const string &solid)
		:Person1(name)
		, _solid(solid)
	{

	}
	void BuyTicket(){
		cout << "免费" << endl;
	}
protected:
	string _solid;
};

void TestButTicket1(Person1 &P)
{
	P.BuyTicket();
}



void Test1(){
	Person1 p1("ren");
	Student1 s1("stu", "123");
	Soldier1 s2("soldier", "6666");
	

	p1.BuyTicket();   //全价票
	s1.BuyTicket();  //学生票
	s2.BuyTicket();   //免费
	//可通过派生类与子类之间的同名隐藏来通过不同的子类对象调用同名后在自己类中的BuyTicket函数，以实现不同的输出
	TestButTicket1(p1);   //全价票
	TestButTicket1(s1);   //全价票
	TestButTicket1(s2);   //全价票
	//通过TestButTicket函数，在传参时，子类传过去，都变成了基类对象，调用的都是基类中BuyTicket函数、、

	//多态的目的就是实现，对于TestButTicket，尽管函数入口的形参类型都是Person，但我们仍然可以通过指针指向（或引用）的空间来调用子类中的复写函数

}



//   构成多态继承条件：1.必须通过基类的指针或引用调用虚函数(-->被virtual修饰的函数称为虚函数)运行时会根据基类指针不同的指针指向与引用调用不同类中的复写函数
//					   2.被调用的函数必须是基类中的虚函数，且派生类必须对基类的虚函数进行重写。（重写的函数可不加virtual关键字）
//                                                                    --重写即派生类中有一个和基类完全相同的虚函数，即返回值类型、函数名字、形参列表完全相同
class Person2{
public:
	Person2(const string& name)
		:_name(name)
	{

	}
	virtual void BuyTicket(){         //必须要有virtual修饰
		cout << "买全价票" << endl;
	}
protected:
	string _name;
};
class Student2 :public Person2{
public:
	Student2(const string &name, const string &stuid)
		:Person2(name)
		, _stuid(stuid)
	{

	}
	virtual void BuyTicket(){                   //可不加virtual关键字
		cout << "买半价票" << endl;
	}
protected:
	string _stuid;
};
class Soldier2 :public Person2{
public:
	Soldier2(const string &name, const string &solid)
		:Person2(name)
		, _solid(solid)
	{

	}
	virtual void BuyTicket(){                        //可不加virtual关键字，但最好加上
		cout << "免费" << endl;
	}
protected:
	string _solid;
};

void TestButTicket2(Person2 &P)    //通过引用或者指针定义形参
{
	P.BuyTicket();
}

void Test2(){
	Person2 p1("ren");
	Student2 s1("stu", "123");
	Soldier2 s2("soldier", "6666");

	TestButTicket2(p1);   //全价票
	TestButTicket2(s1);   //学生票
	TestButTicket2(s2);   //免费


	//如果实现方式没有满足可能有两个原因：1.重写失败：基类表示虚函数，或者派生类中重写时原型不一样
	//                                    2.没有通过基类指针或引用来调用


}


//Q3函数重写的两个特殊实现
//Q3.1  协变（重写的派生类函数与基类中的虚函数返回值不同）
//     即基类虚函数返回基类对象的指针或引用，派生类虚函数返回派生类对象的指针或引用
class Person31{
public:
	Person31(const string& name)
		:_name(name)
	{

	}
	virtual Person31& BuyTicket(){         //必须要有virtual修饰
		cout << "买全价票" << endl;
		return *this;
	}
protected:
	string _name;
};
class Student31 :public Person31{
public:
	Student31(const string &name, const string &stuid)
		:Person31(name)
		, _stuid(stuid)
	{

	}
	virtual Student31& BuyTicket(){

		cout << "买半价票" << endl;
		return *this;
	}
protected:
	string _stuid;
};
class Soldier31 :public Person31{
public:
	Soldier31(const string &name, const string &solid)
		:Person31(name)
		, _solid(solid)
	{

	}
	virtual Soldier31& BuyTicket(){
		cout << "免费" << endl;
		return *this;
	}
protected:
	string _solid;
};

void TestButTicket31(Person31 &P)    //通过引用或者指针定义形参
{
	P.BuyTicket();
}

// 注：这里只要基类和派生类构成继承，返回的基类对象和返回的派生类构成继承即为协变
class A{};
class B :public A{};
class Person32{
public:
	Person32(const string& name)
		:_name(name)
	{

	}
	virtual A& BuyTicket(){         //必须要有virtual修饰
		cout << "买全价票" << endl;
		return *( new A);
	}
protected:
	string _name;
};
class Student32 :public Person32{
public:
	Student32(const string &name, const string &stuid)
		:Person32(name)
		, _stuid(stuid)
	{

	}
	virtual B& BuyTicket(){

		cout << "买半价票" << endl;
		return *(new B);
	}
protected:
	string _stuid;
};
void TestButTicket32(Person32 &P)    //通过引用或者指针定义形参
{
	P.BuyTicket();
}

void Test3(){
	Person31 p1("ren");
	Student31 s1("stu", "123");
	Soldier31 s2("soldier", "6666");

	TestButTicket31(p1);   //全价票
	TestButTicket31(s1);   //学生票
	TestButTicket31(s2);   //免费

	Person32 p2("ren");
	Student32 s22("stu", "123");
	TestButTicket32(p2);   //全价票
	TestButTicket32(s22);   //学生票
	
}
//Q3.2 析构函数重写
//如果基类的析构函数为虚函数，此时派生类析构函数只要定义，无论是否加virtual关键字，都与基类的析构函数构成重写，
//虽然基类与派生类析构函数函数名不同，看起来违背了重写的规则，其实不会，这里可以理解为编译器对析构函数的名称做了特殊处理，编译后析构函数的名称统一处理成destructor。
class B3{
public:
	virtual ~B3(){
		cout << "B析构" << endl;
	}
};
class D3:public B3{
public:
	~D3(){
		cout << "D析构" << endl;
	}
};
void TestD3(B3 & T){
	cout << "TestD3" << endl;
	T.~B3();
}
void Test4(){
	B3* b1=new B3;
	D3* d1 = new D3;
	D3 d2;

	delete b1;
	delete d1;
	TestD3(d2);

}
void Test5(){

}
void Test6(){

}
void Test7(){

}

int main(){

	//Test1();
	//Test2(); 
	//Test3();
	Test4();
	//Test6();
	//Test7();

	system("pause");
	return 0;
}