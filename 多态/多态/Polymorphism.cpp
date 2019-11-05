#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
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