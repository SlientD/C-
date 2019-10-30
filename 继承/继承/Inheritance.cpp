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
// ������public�ĳ�Ա�������з���Ȩ���Ѿ����private
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
// �������Ĺ��캯�����в����Ĺ��캯�����û�������
// �����๹�캯����ʼ���б��λ����ʽ���ã�����ɻ���
// ���ֳ�Ա�ĳ�ʼ��

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



int main()
{
	
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	Test6();
}