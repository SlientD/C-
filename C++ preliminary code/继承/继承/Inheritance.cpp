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
// 基类中public的成员在子类中访问权限已经变成private   (在子类里还是可以使用的，但是当子类被继承时，子类的子类已经无法访问该成员了)
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
//在创建派生类对象时，基类必须先执行基类构造函数函数体创建基类对象，再执行派生类函数函数体构造派生类
//先调用派生类构造函数，再调用基类构造函数（基类构造调用在派生类构造被调用之后执行基类构造函数体之前调用）
// 如果基类的构造函数带有参数的构造函数，用户必须在派生类构造函数初始化列表的位置显式调用，以完成基类部分成员的初始化

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
//Q7:析构函数
//在使用析构函数销毁对象时，先调用派生类析构函数的函数体，在函数体结束时调用基类析构函数清理基类成员
class B71{
public:

	B71(int x){
		_x = x;
		cout << "有参构造B71" << endl;
	}
	~B71(){
		cout << "析构函数~B71" << endl;
	}
	int _x;
};
class D71 :public B71{
public:
	D71(int tmp)
		:B71(tmp)             
	{
		cout << "构造D71" << endl;
	}
	~D71(){
		cout << "析构函数~D71" << endl;
	}
};
void Test7(){
	D71 d1(1);
	D71 d2(d1);     //拷贝构造函数会自动生成，在已存在构造函数的前提下是不会影响默认拷贝构造的生成的，但不会在生成默认无参构造函数
}


//Q8.实现一个不能被继承的类

//Q8.1
class NonIherit1{
public:
	NonIherit1 GetInstance1()
	{
		return NonIherit1();
	}
private:
	NonIherit1(){

	}
	NonIherit1(const NonIherit1 & tmp){

	}
};
//这个函数被继承后，因为构造函数是私有的，在继承后，派生类的构造函数必定要通过调用基类构造来完成对象的创建，但是父类的构造函数
//是私有的无法调用，因而实现不了继承
class Instance1 :public NonIherit1{
public:
	/*Instance1()
	                    //此处无法调用基类无参构造函数
	{

	}*/
	//Instance1(const Instance1 &tmp)        //此处可以调用基类的拷贝构造函数来创建，但是你无法创建一个派生类，又怎么能通过拷贝构造来创建另一个派生类对象呢？
	//	:NonIherit1(tmp)
	//{
	//	
	//}	
};

//Q8.2通过上面的接口我们发现实现不了继承我们也没有办法创建NonIherit1类类对象了。。所以我们要进一步完善
//将GetInstance1（） 这个函数变为static，就可以通过 类名加::来创建对象了
class NonIherit2{
public:
	static NonIherit2 GetInstance2()        //返回值为NonIherit2，也通过调用拷贝构造来创建对象了
	{
		return NonIherit2();
	}
private:
	NonIherit2(){

	}
	/*NonIherit2(const NonIherit2 & tmp){

	}*/
};

//Q8.3 C++11中给出了新的关键字final来修饰类，表示该类无法继承
class NonIherit3 final
{

};
/*
class Instance3 :public NonIherit3{    //会提示报错信息，NonIherit3无法继承

}
*/

void Test8(){
	NonIherit2 x=NonIherit2::GetInstance2();
}

//Q9.继承与友元
//友元函数不能继承，即基类的友元不能访问子类的私有和保护成员
//很好理解，之前说友元函数不属于任意一个类，只要那个类声明了该函数，该函数就是这个类的友元,不属于父类的东西子类自然也无法继承
class D91;
class B91{
public:
	B91(int val)
	:_b(val)
	{

    }
	friend void display(const B91 &btmp,const D91 &dtmp);
private:	
	int _b;
};

class D91:public B91{
public:
	D91(int val1,int val2)
	:B91(val1)
	,_d(val2)
	{

	}
private:
	int _d;
};
void display(const B91 &btmp, const D91 &dtmp){
	cout << btmp._b << endl;
	//cout << dtmp._d << endl;    //报错显示_d不可访问
}
#if 0     //模板加友元思考
class D92;
class B92{
public:
	B92(int val)
		:_b(val)
	{

	}
	template <class T>
	friend void display2(T &btmp);
private:
	int _b;
};

//class D92 :public B92{
//public:
//	D92(int val1, int val2)
//		:B92(val1)
//		, _d(val2)
//	{
//
//	}
//private:
//	int _d;
//};
template <class T>
void display2(T &btmp){
	cout << btmp._b << endl;
	//cout << dtmp._d << endl;    //报错显示_d不可访问
}

#endif
void Test9()
{
	B91 X(2);
	D91 Y(1,2);
	display(X, Y);
	//B92 x(2);
	//display2(x);
}


//Q10:继承与静态成员：
//基类定义一个static静态成员，不管被几个子类继承，都只有一个static成员，父类和所有子类共用这个变量
class B10{
public:
	static int t;
};
int B10::t = 1;
class D101 :public B10{
public:
	D101(){
		t++;
    }

};
class D102 :public B10{
public:
	D102(){
		t++;
	}

};
class D103 :public D101{
public:
	D103()
	{
		t++;
	}
};
void Test10()
{
	B10 b1;
	D101 d1;
	D102 d2;
	D103 d3;
	cout << B10::t << endl;
	cout << D101::t << endl;
	cout << &b1.t << endl;
	cout << &d1.t << endl;
	cout << &d2.t << endl;
	cout << &d3.t << endl;      //输出地址一样
}
//Q11:继承方式类型：在此介绍单继承、多继承、菱形继承
//Q11.1单继承：一个子类继承一个父类
//上面我们所用的继承方式都是单继承模式
//Q11.2多继承：一个子类继承多个父类（至少两个）
//注：在继承的时候每个基类前都要加继承权限否则就默认这个类的继承方式为private
class B111{
public:
	int _b111;
};
class B112{
public:
	int _b112;
};
class D111 :public B111, B112{
	void test(){
		_b111 = 1;
		_b112 = 2;
		cout << _b112 << endl;
	}
};
class D112 :public B111, public B112{
	void test(){
		_b111 = 1;
		_b112 = 2;
	}
};


//Q11.3菱形继承：一个父类被两个子类继承，这两个子类又被另外一个子类多继承,呈现出菱形的形状

class A{
public:
	int _a;
};
class B113:public A{
public:
	int _b1;
};
class B114:public A{
public:
	int _b2;

};
class C :public B113, public B114{
public:
	int _c;
};
//以上四个类构成了菱形继承

//Q11.3.1菱形继承的二义性问题
//因为菱形继承，C即继承了B113基类中的_a,又继承了B114基类中的_a，因而在菱形继承时c类中会出现两个_a成员存在数据冗余的现象
//其次访问c类中的_a时，因为不知道访问那个_a会出现二义性问题，比如 C c1._a;  因为C::_a 不明确，不知道是D113 还是D114中的_a而报错

//解决方法：1.在访问时，前面加上类名使访问明确化，表明是哪个类中的成员，但在根本问题上没有解决二义性问题
//          2.将最顶端基类值A存放一份，实现方式用菱形的虚拟继承     ----》虚拟继承一般只出现在菱形继承的问题中
//用法二对以上方法进行改写
class A1{
public:
	int _a;
};
class B1131 :virtual public A1{    //B1131虚拟继承了A1
public:
	int _b1;
};
class B1141 :virtual public A1{
public:
	int _b2;

};
class C1 :public B1131, public B1141{
public:
	int _c;
};

//实现原理：通过虚拟继承实现了C1中只存放一个A1类的从根本上解决二义性问题
//虚拟继承介绍：
//虚拟继承类的存储内容（按顺序）为：1>虚基表指针（4B），它指向一个虚基表，该空间存放的是（和当前位置的偏移量-0，与类中存取基类成员的偏移量）
//                        2>中间层派生类类成员变量  3>最底层层派生类类成员变量  4>最顶层基类类成员变量-->可通过偏移量找到
//该部分内容可打开内存监视观察

                                

void Test11(){
	D111 d1;
	D112 d2;
	//d1._b112;     //访问权限是private，无法访问了
	d2._b112;

	C c1;
	//c1._a;   //此处会报错，因为C::_a 不明确，不知道是D113 还是D114中的_a
	c1.B113::_a;    //解决方法1
	cout << sizeof(c1) << endl;   //20 =8+8+4

	C1 c2;
	c2._a;
	cout << sizeof(c2) << endl;     //24 =8(B1131)+8(B1132)+4(C)+4(A)

	

}

int main()
{
	
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	Test11();
}