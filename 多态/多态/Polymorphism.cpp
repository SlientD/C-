#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
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
//Q4 override和final
//Q4.1 override：在派生类重写基类虚函数后加override，可检验派生类中是否构成了重写基类的某个虚函数要求，如果不构成重写会报错
class B4{
	virtual void func(){

	}
};
class D4:public B4{
	//void func1()override{      //因为基类中无对应的func1虚函数，因而无法继承会报错，override函数可用来避免我们由于函数名写错导致的错误
	                     

	//}
	void func()override{    

	}
};
//Q4.2 final:在类后加override，表示该虚函数不能继承。
//注：因此final一般不用来修饰顶级基类，基类中写的虚函数，再用final修饰一个类都重写不了写这个虚类干嘛？

class D41 :public B4{
	void func()override final{

	}
};
class D42 :public D41{
	//void func()override {    //报错无法重写

	//}
};



//Q5:抽象类（接口类）：包含纯虚函数的类。抽象类不能实例化出对象，派生类继承在没有重写的前提下也没办法实例化对象。（类的大小不确定）
//                  纯虚函数：在虚函数声明后加=0。但可以通过指针和引用来指向一个包含纯虚函数的类（指针大小确定）







class WC{
public:
	void GetMen(){
		cout << "turn left" << endl;
	}
	void GetWomen(){
		cout << "turn right" << endl;
	}
};
class Person{
public:
	virtual void GoTo_wc(WC& w) = 0;
};
class Women:public Person{
public:
	virtual void GoTo_wc(WC& w) override{
		
		w.GetWomen();
	}
};
class Men :public Person{
public:
	virtual void GoTo_wc(WC& w) override{
		
		w.GetMen();
	}
};
void Test5(){
	//测试：不能用抽象类来创建对象,因为不知道抽象类的大小
	//Person p;      //报错
	



	WC wc;
	
	for (int i = 0; i < 10; i++){
		srand(time(nullptr));
		Person* admin;
		cout << "rand= " << rand() << endl;
		if (rand() % 2 == 0){
			admin = new Women;
		}
		else
			admin = new Men;
		admin->GoTo_wc(wc);
		delete admin;
		Sleep(1000);
	}	
}

//Q6.多态原理：在包含虚函数的类中，类的大小会多四个字节来存放虚函数表的指针,虚函数表是存放虚函数入口地址的一段空间
//              类对象访问虚函数是通过对象中存放的虚函数表的指针来找到虚函数表，虚函数表再通过偏移量找到虚函数入口地址来调用虚函数

//Q6.1
//如果我们没有写默认构造函数，编译器会自动生成一个默认构造函数来帮我们存前四个字节的值
//如果我们写了，编译器会改写构造函数，在里面添加存前四个字节的值的操作

//结合监视和内存来看
class B61{
public:
	B61(){

	}
	virtual void Test(){

	}
	int x;
};



class B62{
public:
	
	virtual void Test(){

	}
	int x;
};

//Q6.2虚函数表构建过程：
//对于基类：将虚函数按照在类中的声明次序一次将其入口地址放入虚表中
//看监视中类对象中前四个字节存放指针的指向的虚函数表（函数指针数组）中的内容
class B63{
public:
	B63(){

	}
	virtual void Test1(){
		cout << "B63::Test1()" << endl;
	}
	virtual void Test2(){
		cout << "B63::Test2()" << endl;
	}
	virtual void Test3(){
		cout << "B63::Test3()" << endl;
	}
	void Test4(){

	}
	int x;
};
//对于派生类：先继承父类中的成员，当然也包括前四个字节-->虚基表地址，但是这里不是将父类中的虚基表地址放入派生类中(虚基表不共用)
//            而是派生类自己也开辟一块空间存放自己的虚基表，然后将父类中虚基表的内容（虚函数入口地址）放到自己的虚基表中（虚函数可能共用）
//            当派生类重写父类中的虚函数时，会用重写函数的入口地址替换偏移量相同的从父类中拷贝的函数入口地址（被重写的虚函数）
//            最后将自己写的虚函数入口地址按声明顺序放入虚函数表中

class D63:public B63{
public:
	D63(){

	}
	virtual void Test1(){
		cout << "D63::Test1()" << endl;
	}
	virtual void Test2(){
		cout << "D63::Test2()" << endl;
	}
	
	int x;
};
class D64 :public B63{

};




typedef void(*PVF)();
void PrintTable(B63 & b, const string& str)
{
	cout << str << endl;
	
	PVF* p = (PVF*)(*(int*)&b);

	while (*p)
	{
		cout<<*p<<endl;
		(*p)();       //调用所p指向的函数
		++p;

	}
	cout << endl;
	
}
void Test6(){
	//Q6.1
	B61 b1;
	cout << sizeof(b1) << endl;    //-->8
	B62 b2;
	cout << sizeof(b2) << endl;    //-->8
	//Q6.2
	B63 b3;
	D63 d1;                //会发现虚基表存的Test3入口地址与父类的相同，Test1与Test2被重写后入口地址就变了
	D64 d2;
	
	cout << *(int *)&b3 << endl;   //因为指针地址占四个字节，可通过int强转在解引用，就可以得出对象中前四个字节中的内容
	cout << *(int*)&d2 << endl;
	cout << *(int*)&d1 << endl;   
	    //以上对象前四个字节都不同，说明每个对象指向的虚函数表不同

	PrintTable(b3, "B63");
	PrintTable(d1, "D63");//入口地址不同与B63中的Test2类,没有改写Test3，因而在虚函数表中Test3函数入口地址没有被换掉。
	PrintTable(d2, "D64");//D64中没有改写B63中的虚函数，因而虚函数表中的函数是一样的

	


	////Q6.3  在底层，由一个类创建的对象共用一个虚基表
	B61 b12;
	cout << *(int *)&b1 << endl;   
	cout << *(int*)&b12 << endl;    //得出结果是一样的，说明两个对象用的是一个虚函数表

}

//Q7.虚函数的调用（多态的体现）：通过基类的指针或者引用调用虚函数又是怎么调用的到子类中的重写的函数呢？

void TestVirtual(B63 * p)
{
	p->Test1();
	p->Test2(); 
	p->Test3(); //虚函数都是通过指针指向空间的 前四个字节（对象虚函数表的地址） 再加上偏移量来找调用函数的入口
	           //因此尽管p的类型是B63 * 但是它指向的空间是派生类，得到的虚函数表是派生类的虚函数表，其中存放的是派生类重写后的虚函数，因而可调用重写后的函数
	p->Test4();// call  B63::Test4 (0DA1663h)    -->普通函数调用方式
	
}


void Test7(){
	B63 b1;
	D63 d1;
	TestVirtual(&b1);
	TestVirtual(&d1);
}



//Q8:带有虚函数的多继承派生类的对象模型
//多继承类的构建方式：将基类中的内容（虚函数表中的内容放到派生类的虚函数表中,成员变量，普通成员函数）放入自己的类中
//                                  有几个基类有虚函数，派生类就要生成相应多的虚函数表指针来指向虚函数表
//                   重写那个基类的虚函数，就找到类中对应的虚函数表指针再结合偏移量替换虚函数表中的入口地址
//                   派生类中的再加的虚函数，按声明顺序将函数入口地址放到第一个虚表之后
class B81{            //占8个字节
public:
	virtual void Test1(){

	}
	void CommenFun(){

	}
	int b1;
};
class B82{                  //占8个字节
public:
	virtual void Test2(){

	}
	virtual void Test3(){

	}
	int b2;
};
class D81 :public B81, public B82{    //8  8                                   
public:                                                                      
	virtual void Test3()override{         
																			  
	}																			
	virtual void Test4(){            //放在第一张虚表之后                     

	}
	int b3;             //-->4
};

//内存布局
//继承B81后的新创建表的虚表指针   （--》派生类新建一个虚函数表存放B81虚表中的内容, 派生类后加的虚函数最后也在这张表中）
//B81成员变量                     B81成员内容
//继承B81后的新创建表的虚表指针    （--》派生类新建一个虚函数表存放B82虚表中的内容）
//B82成员变量
//派生类的成员变量


void Test8(){
	D81 d1;
	cout<<sizeof(d1)<<endl;     //8 8 4   -->20
}

//Q9.inline函数不可以是虚函数--》因为inline没有函数地址，而虚函数在虚函数表里存的就是函数地址，因而不能讲他们放到一起使用
//   static成员函数也不可以是虚函数-->因为static成员函数中没有this指针，而对象访问虚函数表需要this指针来看他的使用类型::成员函数的调用方式无法访问虚函数表，也就不能通过这个办法找到函数入口地址



int main(){

	//Test1();
	//Test2(); 
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	Test8();

	system("pause");
	return 0;
}