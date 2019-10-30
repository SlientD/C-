#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
//Q1:继承方式：
class Base{
public:
	void GetB(){
		cout << "基类Base的创建" << endl;
	}
protected:
	int _b;
};
class Derived : public Base{      //Base是Derived的基类，Derived继承了Base，是Base的派生类，继承方式：class [子类名] ：【访问权限】 父类名
	void GetD(){
		_b = 10;                    //继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分
		cout << "基类Derived的创建" << endl;
	}
protected:
	int _d;
};

//Q2:访问权限:限定该成员变量是否可以直接在类外进行调用
class B1{
public:
	void GetB1(){
		cout << "基类B的创建" << endl;
	}
public:
	int _bpub;
protected:
	int _bpro;
private:
	int _bpri;
};
//public继承
// 基类中public/protected的成员在子类中权限不变
// 基类中private的成员在子类中不可见(不能用---该成员变量确实已经继承到子类中)
class D1 : public B1{     
public:
	void GetD(){
		_bpub = 0;
		_bpro = 0;
		//_bpri = 0;     //此处无法访问bpri  
		
	}
public:
	int _dpub;
protected:
	int _dpro;
private:
	int _dpri;
};
class D11 :public D1{
	void GetD1(){
		_bpub = 0;      //依旧可以访问
		_bpro = 0;      //依旧可以访问
		//_bpri = 0;     //此处无法访问bpri  

	}
};
void Test1(){
	D1 d1;
	d1.GetD();
	d1._bpub = 1;
	//d1._bpro = 1;  //无法访问
}




//protected继承
// 基类中public的成员在子类中访问权限已经变成protected
// 基类中protected的成员在子类中访问权限不变
// 基类中private的成员在子类中不可见(不能用---该成员变量确实已经继承到子类中)
class D2 : protected B1{
public:
	void GetD(){
		_bpub = 0;
		_bpro = 0;
		//_bpri = 0;     //此处无法访问bpri  

	}
public:
	int _dpub;
protected:
	int _dpro;
private:
	int _dpri;
};
class D22 : protected D2{
public:
	void GetDD(){
		_bpub = 0;
		_bpro = 0;       //此处依旧可以访问_bpro
		//_bpri = 0;     //此处无法访问bpri  

	}

};

void Test2(){
	D2 d2;
	//d2._bpub = 1;    //此处因为protected继承变得无法访问
	//d1._bpro = 1;  //无法访问
}
//private继承
// 基类中public的成员在子类中访问权限已经变成private
// 基类中protected的成员在子类中访问权限已经变成private
// 基类中private的成员在子类中不可见(不能用---该成员变量确实已经继承到子类中)
class D3 : private B1{
public:
	void GetD(){
		_bpub = 0;
		_bpro = 0;
		//_bpri = 0;     //此处无法访问bpri  

	}
public:
	int _dpub;
protected:
	int _dpro;
private:
	int _dpri;
};
class D33 : public D3{
public:
	void GetDD(){
		//_bpub = 0;        //此处无法访问_bpub，在D3中，_bpub的权限变为了private，他的子类也无法访问_bpub了
		//_bpro = 0;       //此处无法访问_bpro，在D3中，_bpro的权限变为了private，他的子类也无法访问_bpro了
		//_bpri = 0;     //此处无法访问bpri  

	}

};
void Test3(){
	D3 d3;
	//d3._bpub = 1;    //此处因为private继承变得无法访问
	//d1._bpro = 1;  //无法访问
}

//Q3:class默认继承权限priavet struct默认继承权限public
struct DS : B1{
	void Get(){
		_bpro = 0;
		_bpub = 0;
    }
};
class DSS :DS{
	void GetS(){
		_bpro = 0;
		_bpub = 0;
	}
};
class DSSS :DSS{
	void GetS(){
		//_bpro = 0;
		//_bpub = 0;   //因为DSS是private继承因而变得无法访问
	}
};

//Q4:基类和派生类对象赋值转换
// 赋值兼容规则：前提是要用public继承方式
// 如果是public继承方式：派生类与基类对象之间是--is-a的关系
// is-a: 是一个，可以将一个子类对象看成是一个基类对象
// 所有用到基类对象的位置都可以使用子类对象进行代替
class Person{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
public:
	string _name = "peter"; 
	int _age = 18; 
};
class Student : public Person
{
public:
	int _stuid; 
};

  
void Test4()
{
	//Q4.1派生类可以给基类赋值 基类无法给派生类赋值
	Person p1;
	Student s1;
	//p1 = s1;
	//s1 = p1;    //会报错

	//Q4.2 一个基类指针可以指向子类对象，一个子类的指针不能直接指向一个基类的对象
	Person *pp1=&p1;
	Student *ps1=&s1;
	
	pp1 = &s1;
	//ps1 = &p1;   //会报错
	//引用同指针，一个基类指针做子类对象的引用，反之不可以，引用实质上也是指针实现的

	//Q4.3 也可以通过强转的方式来使子类指针指向一个基类对象，但是不安全,在访问派生类中额外加的成员时代码会崩溃

	Student *ps2 = (Student *)&p1;
	ps2->_stuid=0;     //????????????
	
}

//Q5:同名隐藏：基类和派生类中具有相同名称的成员(成员变量 || 成员函数)
// 如果通过派生类对象直接访问同名成员，优先访问到的是派生类自己的，基类的
// 如果想访问基类的，要通过  基类名::成员名访问
class Student1 : public Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "Person::name:" << Person::_name << endl;
		cout << "age:" << _age << endl;
		cout << "_stuid:" << _stuid << endl;
	}
public:
	int _stuid=0;
	string _name = "redom";
};
void Test5()
{
	Student1 s1;
	s1.Print();          //子类Print函数
	s1.Person::Print();  //调用基类的Print函数
}

//Q6:默认构造函数
//Q6.1构造函数
// 如果基类的构造函数带有参数的构造函数，用户必须在
// 派生类构造函数初始化列表的位置显式调用，以完成基类
// 部分成员的初始化

class B61{
public:
	B61(){
		cout << "无参构造B61" << endl;
	}
};
class D61:public B61{
public:
	D61(){                         //会自动调用基类构造函数
		cout << "构造D61" << endl;
	}

};

class B62{
public:
	B62(int x){
		_x = x;
		cout << "有参构造B62" << endl;
	}

	int _x;
};
class D62 :public B62{
public:
	//D62(){                         //若此处不调用合适的父类构造函数就会报错
	//	cout << "构造D62" << endl;
	//}
	D62(int tmp)
	:B62(tmp)             //使用合适的父类构造
	{                         
		cout << "构造D62" << endl;
	}
};
//拷贝构造，拷贝构造函数编译器也是可以默认生成的，但是涉及资源管理（深浅拷贝）的类就需要自己实现了
//赋值运算符重载
class B63{
public:

	B63(int x){
		_x = x;
		cout << "有参构造B63" << endl;
	}
	B63(const B63 &tmp){
		_x = tmp._x;
		cout << "拷贝构造函数B63" << endl;
	}
	B63& operator=(const B63 &tmp)
	{
		_x = tmp._x;
		cout << "赋值运算符重载B63" << endl;
		return *this;
	}
	int _x;
};
class D63 :public B63{
public:
	D63(int tmp)
		:B63(tmp)             //使用合适的父类构造
	{
		cout << "构造D63" << endl;
	}
	D63(const D63 &tmp)
		:B63(tmp)             //用派生类给基类赋值
	{
		cout << "构造D63" << endl;
	}
	D63& operator=(const D63 &tmp)
	{
		B63::operator=(tmp);
		cout << "赋值运算符重载D63" << endl;
		return *this;
	}
};
void Test6(){
	D61 d1; 
	D62 d2(2);
	D63 d3(3);
	D63 d4(d3);
	D63 d5(4);
	d3 = d5;
}



int main()
{
	
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	Test6();
}