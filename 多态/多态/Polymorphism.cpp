#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
using namespace std;
//˵�������´�������vs 2013��x86���������еģ��漰��ָ����ռ�ռ��С����4Byte
//Q1:��̬���ã��ڼ̳������£���ͨ����ͬ������ȥ���û����е�ͬһ�����������������ͬ���
// ��̬�����֣��������ʱ������ȷ�����׵����Ǹ�����麯��
//           �ڴ�������ʱ������ָ����ָ���ʵ�ʶ���ѡ����ö�Ӧ����麯��

//�������¼̳й�ϵ
class Person1{
public:
	Person1(const string& name)
	:_name(name)
	{

	}
	void BuyTicket(){
		cout << "��ȫ��Ʊ" << endl;
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
		cout << "����Ʊ" << endl;
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
		cout << "���" << endl;
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
	

	p1.BuyTicket();   //ȫ��Ʊ
	s1.BuyTicket();  //ѧ��Ʊ
	s2.BuyTicket();   //���
	//��ͨ��������������֮���ͬ��������ͨ����ͬ������������ͬ�������Լ����е�BuyTicket��������ʵ�ֲ�ͬ�����
	TestButTicket1(p1);   //ȫ��Ʊ
	TestButTicket1(s1);   //ȫ��Ʊ
	TestButTicket1(s2);   //ȫ��Ʊ
	//ͨ��TestButTicket�������ڴ���ʱ�����ഫ��ȥ��������˻�����󣬵��õĶ��ǻ�����BuyTicket��������

	//��̬��Ŀ�ľ���ʵ�֣�����TestButTicket�����ܺ�����ڵ��β����Ͷ���Person����������Ȼ����ͨ��ָ��ָ�򣨻����ã��Ŀռ������������еĸ�д����

}



//   ���ɶ�̬�̳�������1.����ͨ�������ָ������õ����麯��(-->��virtual���εĺ�����Ϊ�麯��)����ʱ����ݻ���ָ�벻ͬ��ָ��ָ�������õ��ò�ͬ���еĸ�д����
//					   2.�����õĺ��������ǻ����е��麯���������������Ի�����麯��������д������д�ĺ����ɲ���virtual�ؼ��֣�
//                                                                    --��д������������һ���ͻ�����ȫ��ͬ���麯����������ֵ���͡��������֡��β��б���ȫ��ͬ
class Person2{
public:
	Person2(const string& name)
		:_name(name)
	{

	}
	virtual void BuyTicket(){         //����Ҫ��virtual����
		cout << "��ȫ��Ʊ" << endl;
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
	virtual void BuyTicket(){                   //�ɲ���virtual�ؼ���
		cout << "����Ʊ" << endl;
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
	virtual void BuyTicket(){                        //�ɲ���virtual�ؼ��֣�����ü���
		cout << "���" << endl;
	}
protected:
	string _solid;
};

void TestButTicket2(Person2 &P)    //ͨ�����û���ָ�붨���β�
{
	P.BuyTicket();
}

void Test2(){
	Person2 p1("ren");
	Student2 s1("stu", "123");
	Soldier2 s2("soldier", "6666");

	TestButTicket2(p1);   //ȫ��Ʊ
	TestButTicket2(s1);   //ѧ��Ʊ
	TestButTicket2(s2);   //���


	//���ʵ�ַ�ʽû���������������ԭ��1.��дʧ�ܣ������ʾ�麯������������������дʱԭ�Ͳ�һ��
	//                                    2.û��ͨ������ָ�������������


}


//Q3������д����������ʵ��
//Q3.1  Э�䣨��д�������ຯ��������е��麯������ֵ��ͬ��
//     �������麯�����ػ�������ָ������ã��������麯����������������ָ�������
class Person31{
public:
	Person31(const string& name)
		:_name(name)
	{

	}
	virtual Person31& BuyTicket(){         //����Ҫ��virtual����
		cout << "��ȫ��Ʊ" << endl;
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

		cout << "����Ʊ" << endl;
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
		cout << "���" << endl;
		return *this;
	}
protected:
	string _solid;
};

void TestButTicket31(Person31 &P)    //ͨ�����û���ָ�붨���β�
{
	P.BuyTicket();
}

// ע������ֻҪ����������๹�ɼ̳У����صĻ������ͷ��ص������๹�ɼ̳м�ΪЭ��
class A{};
class B :public A{};
class Person32{
public:
	Person32(const string& name)
		:_name(name)
	{

	}
	virtual A& BuyTicket(){         //����Ҫ��virtual����
		cout << "��ȫ��Ʊ" << endl;
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

		cout << "����Ʊ" << endl;
		return *(new B);
	}
protected:
	string _stuid;
};
void TestButTicket32(Person32 &P)    //ͨ�����û���ָ�붨���β�
{
	P.BuyTicket();
}

void Test3(){
	Person31 p1("ren");
	Student31 s1("stu", "123");
	Soldier31 s2("soldier", "6666");

	TestButTicket31(p1);   //ȫ��Ʊ
	TestButTicket31(s1);   //ѧ��Ʊ
	TestButTicket31(s2);   //���

	Person32 p2("ren");
	Student32 s22("stu", "123");
	TestButTicket32(p2);   //ȫ��Ʊ
	TestButTicket32(s22);   //ѧ��Ʊ
	
}
//Q3.2 ����������д
//����������������Ϊ�麯������ʱ��������������ֻҪ���壬�����Ƿ��virtual�ؼ��֣�����������������������д��
//��Ȼ����������������������������ͬ��������Υ������д�Ĺ�����ʵ���ᣬ����������Ϊ�����������������������������⴦���������������������ͳһ�����destructor��
class B3{
public:
	virtual ~B3(){
		cout << "B����" << endl;
	}
};
class D3:public B3{
public:
	~D3(){
		cout << "D����" << endl;
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
//Q4 override��final
//Q4.1 override������������д�����麯�����override���ɼ������������Ƿ񹹳�����д�����ĳ���麯��Ҫ�������������д�ᱨ��
class B4{
	virtual void func(){

	}
};
class D4:public B4{
	//void func1()override{      //��Ϊ�������޶�Ӧ��func1�麯��������޷��̳лᱨ��override���������������������ں�����д���µĴ���
	                     

	//}
	void func()override{    

	}
};
//Q4.2 final:������override����ʾ���麯�����ܼ̳С�
//ע�����finalһ�㲻�������ζ������࣬������д���麯��������final����һ���඼��д����д���������

class D41 :public B4{
	void func()override final{

	}
};
class D42 :public D41{
	//void func()override {    //�����޷���д

	//}
};



//Q5:�����ࣨ�ӿ��ࣩ���������麯�����ࡣ�����಻��ʵ����������������̳���û����д��ǰ����Ҳû�취ʵ�������󡣣���Ĵ�С��ȷ����
//                  ���麯�������麯���������=0��������ͨ��ָ���������ָ��һ���������麯�����ָࣨ���Сȷ����







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
	//���ԣ������ó���������������,��Ϊ��֪��������Ĵ�С
	//Person p;      //����
	



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

//Q6.��̬ԭ���ڰ����麯�������У���Ĵ�С����ĸ��ֽ�������麯�����ָ��,�麯�����Ǵ���麯����ڵ�ַ��һ�οռ�
//              ���������麯����ͨ�������д�ŵ��麯�����ָ�����ҵ��麯�����麯������ͨ��ƫ�����ҵ��麯����ڵ�ַ�������麯��

//Q6.1
//�������û��дĬ�Ϲ��캯�������������Զ�����һ��Ĭ�Ϲ��캯���������Ǵ�ǰ�ĸ��ֽڵ�ֵ
//�������д�ˣ����������д���캯������������Ӵ�ǰ�ĸ��ֽڵ�ֵ�Ĳ���

//��ϼ��Ӻ��ڴ�����
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

//Q6.2�麯���������̣�
//���ڻ��ࣺ���麯�����������е���������һ�ν�����ڵ�ַ���������
//���������������ǰ�ĸ��ֽڴ��ָ���ָ����麯��������ָ�����飩�е�����
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
//���������ࣺ�ȼ̳и����еĳ�Ա����ȻҲ����ǰ�ĸ��ֽ�-->������ַ���������ﲻ�ǽ������е�������ַ������������(���������)
//            �����������Լ�Ҳ����һ��ռ����Լ��������Ȼ�󽫸��������������ݣ��麯����ڵ�ַ���ŵ��Լ���������У��麯�����ܹ��ã�
//            ����������д�����е��麯��ʱ��������д��������ڵ�ַ�滻ƫ������ͬ�ĴӸ����п����ĺ�����ڵ�ַ������д���麯����
//            ����Լ�д���麯����ڵ�ַ������˳������麯������

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
		(*p)();       //������pָ��ĺ���
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
	D63 d1;                //�ᷢ���������Test3��ڵ�ַ�븸�����ͬ��Test1��Test2����д����ڵ�ַ�ͱ���
	D64 d2;
	
	cout << *(int *)&b3 << endl;   //��Ϊָ���ַռ�ĸ��ֽڣ���ͨ��intǿת�ڽ����ã��Ϳ��Եó�������ǰ�ĸ��ֽ��е�����
	cout << *(int*)&d2 << endl;
	cout << *(int*)&d1 << endl;   
	    //���϶���ǰ�ĸ��ֽڶ���ͬ��˵��ÿ������ָ����麯����ͬ

	PrintTable(b3, "B63");
	PrintTable(d1, "D63");//��ڵ�ַ��ͬ��B63�е�Test2��,û�и�дTest3��������麯������Test3������ڵ�ַû�б�������
	PrintTable(d2, "D64");//D64��û�и�дB63�е��麯��������麯�����еĺ�����һ����

	


	////Q6.3  �ڵײ㣬��һ���ഴ���Ķ�����һ�������
	B61 b12;
	cout << *(int *)&b1 << endl;   
	cout << *(int*)&b12 << endl;    //�ó������һ���ģ�˵�����������õ���һ���麯����

}

//Q7.�麯���ĵ��ã���̬�����֣���ͨ�������ָ��������õ����麯��������ô���õĵ������е���д�ĺ����أ�

void TestVirtual(B63 * p)
{
	p->Test1();
	p->Test2(); 
	p->Test3(); //�麯������ͨ��ָ��ָ��ռ�� ǰ�ĸ��ֽڣ������麯����ĵ�ַ�� �ټ���ƫ�������ҵ��ú��������
	           //��˾���p��������B63 * ������ָ��Ŀռ��������࣬�õ����麯��������������麯�������д�ŵ�����������д����麯��������ɵ�����д��ĺ���
	p->Test4();// call  B63::Test4 (0DA1663h)    -->��ͨ�������÷�ʽ
	
}


void Test7(){
	B63 b1;
	D63 d1;
	TestVirtual(&b1);
	TestVirtual(&d1);
}



//Q8:�����麯���Ķ�̳�������Ķ���ģ��
//��̳���Ĺ�����ʽ���������е����ݣ��麯�����е����ݷŵ���������麯������,��Ա��������ͨ��Ա�����������Լ�������
//                                  �м����������麯�����������Ҫ������Ӧ����麯����ָ����ָ���麯����
//                   ��д�Ǹ�������麯�������ҵ����ж�Ӧ���麯����ָ���ٽ��ƫ�����滻�麯�����е���ڵ�ַ
//                   �������е��ټӵ��麯����������˳�򽫺�����ڵ�ַ�ŵ���һ�����֮��
class B81{            //ռ8���ֽ�
public:
	virtual void Test1(){

	}
	void CommenFun(){

	}
	int b1;
};
class B82{                  //ռ8���ֽ�
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
	virtual void Test4(){            //���ڵ�һ�����֮��                     

	}
	int b3;             //-->4
};

//�ڴ沼��
//�̳�B81����´���������ָ��   ��--���������½�һ���麯������B81����е�����, �������ӵ��麯�����Ҳ�����ű��У�
//B81��Ա����                     B81��Ա����
//�̳�B81����´���������ָ��    ��--���������½�һ���麯������B82����е����ݣ�
//B82��Ա����
//������ĳ�Ա����


void Test8(){
	D81 d1;
	cout<<sizeof(d1)<<endl;     //8 8 4   -->20
}

//Q9.inline�������������麯��--����Ϊinlineû�к�����ַ�����麯�����麯�������ľ��Ǻ�����ַ��������ܽ����Ƿŵ�һ��ʹ��
//   static��Ա����Ҳ���������麯��-->��Ϊstatic��Ա������û��thisָ�룬����������麯������Ҫthisָ����������ʹ������::��Ա�����ĵ��÷�ʽ�޷������麯����Ҳ�Ͳ���ͨ������취�ҵ�������ڵ�ַ



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