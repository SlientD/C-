#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
//Q1:�̳з�ʽ��
class Base{
public:
	void GetB(){
		cout << "����Base�Ĵ���" << endl;
	}
protected:
	int _b;
};
class Derived : public Base{      //Base��Derived�Ļ��࣬Derived�̳���Base����Base�������࣬�̳з�ʽ��class [������] ��������Ȩ�ޡ� ������
	void GetD(){
		_b = 10;                    //�̳к����Person�ĳ�Ա����Ա����+��Ա�����������������һ����
		cout << "����Derived�Ĵ���" << endl;
	}
protected:
	int _d;
};

//Q2:����Ȩ��:�޶��ó�Ա�����Ƿ����ֱ����������е���
class B1{
public:
	void GetB1(){
		cout << "����B�Ĵ���" << endl;
	}
public:
	int _bpub;
protected:
	int _bpro;
private:
	int _bpri;
};
//public�̳�
// ������public/protected�ĳ�Ա��������Ȩ�޲���
// ������private�ĳ�Ա�������в��ɼ�(������---�ó�Ա����ȷʵ�Ѿ��̳е�������)
class D1 : public B1{     
public:
	void GetD(){
		_bpub = 0;
		_bpro = 0;
		//_bpri = 0;     //�˴��޷�����bpri  
		
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
		_bpub = 0;      //���ɿ��Է���
		_bpro = 0;      //���ɿ��Է���
		//_bpri = 0;     //�˴��޷�����bpri  

	}
};
void Test1(){
	D1 d1;
	d1.GetD();
	d1._bpub = 1;
	//d1._bpro = 1;  //�޷�����
}




//protected�̳�
// ������public�ĳ�Ա�������з���Ȩ���Ѿ����protected
// ������protected�ĳ�Ա�������з���Ȩ�޲���
// ������private�ĳ�Ա�������в��ɼ�(������---�ó�Ա����ȷʵ�Ѿ��̳е�������)
class D2 : protected B1{
public:
	void GetD(){
		_bpub = 0;
		_bpro = 0;
		//_bpri = 0;     //�˴��޷�����bpri  

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
		_bpro = 0;       //�˴����ɿ��Է���_bpro
		//_bpri = 0;     //�˴��޷�����bpri  

	}

};

void Test2(){
	D2 d2;
	//d2._bpub = 1;    //�˴���Ϊprotected�̳б���޷�����
	//d1._bpro = 1;  //�޷�����
}
//private�̳�
// ������public�ĳ�Ա�������з���Ȩ���Ѿ����private   (�������ﻹ�ǿ���ʹ�õģ����ǵ����౻�̳�ʱ������������Ѿ��޷����ʸó�Ա��)
// ������protected�ĳ�Ա�������з���Ȩ���Ѿ����private
// ������private�ĳ�Ա�������в��ɼ�(������---�ó�Ա����ȷʵ�Ѿ��̳е�������)
class D3 : private B1{
public:
	void GetD(){
		_bpub = 0;
		_bpro = 0;
		//_bpri = 0;     //�˴��޷�����bpri  

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
		//_bpub = 0;        //�˴��޷�����_bpub����D3�У�_bpub��Ȩ�ޱ�Ϊ��private����������Ҳ�޷�����_bpub��
		//_bpro = 0;       //�˴��޷�����_bpro����D3�У�_bpro��Ȩ�ޱ�Ϊ��private����������Ҳ�޷�����_bpro��
		//_bpri = 0;     //�˴��޷�����bpri  

	}

};
void Test3(){
	D3 d3;
	//d3._bpub = 1;    //�˴���Ϊprivate�̳б���޷�����
	//d1._bpro = 1;  //�޷�����
}

//Q3:classĬ�ϼ̳�Ȩ��priavet structĬ�ϼ̳�Ȩ��public
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
		//_bpub = 0;   //��ΪDSS��private�̳��������޷�����
	}
};

//Q4:��������������ֵת��
// ��ֵ���ݹ���ǰ����Ҫ��public�̳з�ʽ
// �����public�̳з�ʽ����������������֮����--is-a�Ĺ�ϵ
// is-a: ��һ�������Խ�һ��������󿴳���һ���������
// �����õ���������λ�ö�����ʹ�����������д���
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
	//Q4.1��������Ը����ำֵ �����޷��������ำֵ
	Person p1;
	Student s1;
	//p1 = s1;
	//s1 = p1;    //�ᱨ��

	//Q4.2 һ������ָ�����ָ���������һ�������ָ�벻��ֱ��ָ��һ������Ķ���
	Person *pp1=&p1;
	Student *ps1=&s1;
	
	pp1 = &s1;
	//ps1 = &p1;   //�ᱨ��
	//����ָͬ�룬һ������ָ���������������ã���֮�����ԣ�����ʵ����Ҳ��ָ��ʵ�ֵ�

	//Q4.3 Ҳ����ͨ��ǿת�ķ�ʽ��ʹ����ָ��ָ��һ��������󣬵��ǲ���ȫ,�ڷ����������ж���ӵĳ�Աʱ��������

	Student *ps2 = (Student *)&p1;
	ps2->_stuid=0;     //????????????
	
}

//Q5:ͬ�����أ�������������о�����ͬ���Ƶĳ�Ա(��Ա���� || ��Ա����)
// ���ͨ�����������ֱ�ӷ���ͬ����Ա�����ȷ��ʵ������������Լ��ģ������
// �������ʻ���ģ�Ҫͨ��  ������::��Ա������
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
	s1.Print();          //����Print����
	s1.Person::Print();  //���û����Print����
}

//Q6:Ĭ�Ϲ��캯��
//Q6.1���캯��
//�ڴ������������ʱ�����������ִ�л��๹�캯�������崴�����������ִ�������ຯ�������幹��������
//�ȵ��������๹�캯�����ٵ��û��๹�캯�������๹������������๹�챻����֮��ִ�л��๹�캯����֮ǰ���ã�
// �������Ĺ��캯�����в����Ĺ��캯�����û������������๹�캯����ʼ���б��λ����ʽ���ã�����ɻ��ಿ�ֳ�Ա�ĳ�ʼ��

class B61{
public:
	B61(){
		cout << "�޲ι���B61" << endl;
	}
};
class D61:public B61{
public:
	D61(){                         //���Զ����û��๹�캯��
		cout << "����D61" << endl;
	}

};

class B62{
public:
	B62(int x){
		_x = x;
		cout << "�вι���B62" << endl;
	}

	int _x;
};
class D62 :public B62{
public:
	//D62(){                         //���˴������ú��ʵĸ��๹�캯���ͻᱨ��
	//	cout << "����D62" << endl;
	//}
	D62(int tmp)
	:B62(tmp)             //ʹ�ú��ʵĸ��๹��
	{                         
		cout << "����D62" << endl;
	}
};
//�������죬�������캯��������Ҳ�ǿ���Ĭ�����ɵģ������漰��Դ������ǳ�������������Ҫ�Լ�ʵ����
//��ֵ���������
class B63{
public:

	B63(int x){
		_x = x;
		cout << "�вι���B63" << endl;
	}
	B63(const B63 &tmp){
		_x = tmp._x;
		cout << "�������캯��B63" << endl;
	}
	B63& operator=(const B63 &tmp)
	{
		_x = tmp._x;
		cout << "��ֵ���������B63" << endl;
		return *this;
	}
	int _x;
};
class D63 :public B63{
public:
	D63(int tmp)
		:B63(tmp)             //ʹ�ú��ʵĸ��๹��
	{
		cout << "����D63" << endl;
	}
	D63(const D63 &tmp)
		:B63(tmp)             //������������ำֵ
	{
		cout << "����D63" << endl;
	}
	D63& operator=(const D63 &tmp)
	{
		B63::operator=(tmp);
		cout << "��ֵ���������D63" << endl;
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
//Q7:��������
//��ʹ�������������ٶ���ʱ���ȵ������������������ĺ����壬�ں��������ʱ���û�������������������Ա
class B71{
public:

	B71(int x){
		_x = x;
		cout << "�вι���B71" << endl;
	}
	~B71(){
		cout << "��������~B71" << endl;
	}
	int _x;
};
class D71 :public B71{
public:
	D71(int tmp)
		:B71(tmp)             
	{
		cout << "����D71" << endl;
	}
	~D71(){
		cout << "��������~D71" << endl;
	}
};
void Test7(){
	D71 d1(1);
	D71 d2(d1);     //�������캯�����Զ����ɣ����Ѵ��ڹ��캯����ǰ�����ǲ���Ӱ��Ĭ�Ͽ�����������ɵģ�������������Ĭ���޲ι��캯��
}


//Q8.ʵ��һ�����ܱ��̳е���

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
//����������̳к���Ϊ���캯����˽�еģ��ڼ̳к�������Ĺ��캯���ض�Ҫͨ�����û��๹������ɶ���Ĵ��������Ǹ���Ĺ��캯��
//��˽�е��޷����ã����ʵ�ֲ��˼̳�
class Instance1 :public NonIherit1{
public:
	/*Instance1()
	                    //�˴��޷����û����޲ι��캯��
	{

	}*/
	//Instance1(const Instance1 &tmp)        //�˴����Ե��û���Ŀ������캯�����������������޷�����һ�������࣬����ô��ͨ������������������һ������������أ�
	//	:NonIherit1(tmp)
	//{
	//	
	//}	
};

//Q8.2ͨ������Ľӿ����Ƿ���ʵ�ֲ��˼̳�����Ҳû�а취����NonIherit1��������ˡ�����������Ҫ��һ������
//��GetInstance1���� ���������Ϊstatic���Ϳ���ͨ�� ������::������������
class NonIherit2{
public:
	static NonIherit2 GetInstance2()        //����ֵΪNonIherit2��Ҳͨ�����ÿ�������������������
	{
		return NonIherit2();
	}
private:
	NonIherit2(){

	}
	/*NonIherit2(const NonIherit2 & tmp){

	}*/
};

//Q8.3 C++11�и������µĹؼ���final�������࣬��ʾ�����޷��̳�
class NonIherit3 final
{

};
/*
class Instance3 :public NonIherit3{    //����ʾ������Ϣ��NonIherit3�޷��̳�

}
*/

void Test8(){
	NonIherit2 x=NonIherit2::GetInstance2();
}

//Q9.�̳�����Ԫ
//��Ԫ�������ܼ̳У����������Ԫ���ܷ��������˽�кͱ�����Ա
//�ܺ���⣬֮ǰ˵��Ԫ��������������һ���ֻ࣬Ҫ�Ǹ��������˸ú������ú���������������Ԫ,�����ڸ���Ķ���������ȻҲ�޷��̳�
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
	//cout << dtmp._d << endl;    //������ʾ_d���ɷ���
}
#if 0     //ģ�����Ԫ˼��
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
	//cout << dtmp._d << endl;    //������ʾ_d���ɷ���
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


//Q10:�̳��뾲̬��Ա��
//���ඨ��һ��static��̬��Ա�����ܱ���������̳У���ֻ��һ��static��Ա��������������๲���������
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
	cout << &d3.t << endl;      //�����ַһ��
}
//Q11:�̳з�ʽ���ͣ��ڴ˽��ܵ��̳С���̳С����μ̳�
//Q11.1���̳У�һ������̳�һ������
//�����������õļ̳з�ʽ���ǵ��̳�ģʽ
//Q11.2��̳У�һ������̳ж�����ࣨ����������
//ע���ڼ̳е�ʱ��ÿ������ǰ��Ҫ�Ӽ̳�Ȩ�޷����Ĭ�������ļ̳з�ʽΪprivate
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


//Q11.3���μ̳У�һ�����౻��������̳У������������ֱ�����һ�������̳�,���ֳ����ε���״

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
//�����ĸ��๹�������μ̳�

//Q11.3.1���μ̳еĶ���������
//��Ϊ���μ̳У�C���̳���B113�����е�_a,�ּ̳���B114�����е�_a����������μ̳�ʱc���л��������_a��Ա�����������������
//��η���c���е�_aʱ����Ϊ��֪�������Ǹ�_a����ֶ��������⣬���� C c1._a;  ��ΪC::_a ����ȷ����֪����D113 ����D114�е�_a������

//���������1.�ڷ���ʱ��ǰ���������ʹ������ȷ�����������ĸ����еĳ�Ա�����ڸ���������û�н������������
//          2.����˻���ֵA���һ�ݣ�ʵ�ַ�ʽ�����ε�����̳�     ----������̳�һ��ֻ���������μ̳е�������
//�÷��������Ϸ������и�д
class A1{
public:
	int _a;
};
class B1131 :virtual public A1{    //B1131����̳���A1
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

//ʵ��ԭ��ͨ������̳�ʵ����C1��ֻ���һ��A1��ĴӸ����Ͻ������������
//����̳н��ܣ�
//����̳���Ĵ洢���ݣ���˳��Ϊ��1>�����ָ�루4B������ָ��һ��������ÿռ��ŵ��ǣ��͵�ǰλ�õ�ƫ����-0�������д�ȡ�����Ա��ƫ������
//                        2>�м�����������Ա����  3>��ײ�����������Ա����  4>���������Ա����-->��ͨ��ƫ�����ҵ�
//�ò������ݿɴ��ڴ���ӹ۲�

                                

void Test11(){
	D111 d1;
	D112 d2;
	//d1._b112;     //����Ȩ����private���޷�������
	d2._b112;

	C c1;
	//c1._a;   //�˴��ᱨ����ΪC::_a ����ȷ����֪����D113 ����D114�е�_a
	c1.B113::_a;    //�������1
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