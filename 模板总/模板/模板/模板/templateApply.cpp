#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;


//Q1:
//������ģ�����
//�����βΣ�������ģ������б��У�����class��typename֮��Ĳ�����������
//�������βΣ���һ��������Ϊ�ຯ��ģ���һ����������ģ���пɽ��������ɳ�����ʹ��

namespace Eg
{

	template <class T,size_t N=10>     //N���������У���Ϊ����ʹ��
	class array{
	public:
		size_t size()const
		{
			//N = 20;      //�ᱨ������	1	error C2106: ��=��: �����������Ϊ��ֵ,��֤��N�ǳ���
			return _size;
		}
	private:
		T _array[N];
		size_t _size;
	};
}

void Test1(){
	Eg::array<int> x;
	x.size();
}
 

void Test2(){

	Eg::array<int,2> x1;
	//ע 1��������ģ�����Ҫ�ڱ����ھ���ȷ�Ͻ��,1+2�����ڱ���ʱȷ�ϣ���a+b������
	Eg::array<int, 2+1> x2;
	//int a = 1, b = 2;
	//Eg::array<int, a+b> x3;
	
	//2.��������������Լ��ַ����ǲ�������Ϊ������ģ�����
	//Eg::array<int, 2.0> x3;
}


//Q2:ģ����ػ�����ԭģ����Ļ����ϣ���������������������⻯��ʵ�ַ�ʽ

//2.1����ģ���ػ�:
//ʹ��ģ�����ʵ���������޹صĴ��룬�������������ͻ�ﲻ�������ڴ��Ľ��������Ƚ�ָ������
template <class T>
T& MAX_T(T& left, T& right)
{
	return left>right?left:right;
}
//����ģ����ػ���ʽ��
//1.Ҫ����һ����������ģ��
//2.�ؼ���template�����һ�ѿյļ�����<>
//3.���������һ�Լ������������Ҫ�ػ�������
//4.�����βα����Ҫ��ģ�庯���Ļ�������������ȫ��ͬ����ͬ�Ļ����������ܻᱨһЩ����
//�������char*�����ػ���
template <>
char*& MAX_T<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) == 1)
	{
		return left;
	}
	else{
		return right;
	}
}
//����һ�㶼�ǽ��ú���ֱ�Ӹ�����һ��ʵ�ּ򵥣�������Ϊ����ģ����ܻ��������ܴ�����ߴ������޵�����
template <class T>
const T& MIN_T(const T& left,const T& right)
{
	return left<right ? left : right;
}
template <>
const char*& MIN_T<const char*&>(const char*& left,const char*& right)
{
	if (strcmp(left, right) == -1)
	{
		return left;
	}
	else{
		return right;
	}
}

template<class T>
void TestTemplate(T const & p) //��Ӧ�ǣ�T const &p Ӧ����*p���ܸı� �������p��ָ��  const int*& p<---���� int*& const p
{
	*p = 100;

	int b = 20;
//	p = &b;          //�ᱨ������ 	error C3892: ��p��: ���ܸ�������ֵ	

}


void Test3(){
	int x = 2,y=2;
	cout << MAX_T(x, y) << endl;
	char *p1 = "wello";
	char *p2 = "hello";
	cout << MAX_T(p1, p2) << endl;   //���hello  ��Ӧ�����wello �������߼����������ҪΪchar*���ػ�һ��ģ���ṩ����������

	const char *p3 = "Hello";
	const char *p4 = "hello";
	cout << MIN_T(p1, p2) << endl;   //��������ػ�����ģ��

	int *ip1 = &x;
	TestTemplate(ip1);
}


//2.2��ģ���ػ�����Ϊȫ�ػ���ƫ�ػ�

//ȫ�ػ�������ģ������б������еĲ�����ȷ����

template<class T1, class T2>
class Data1
{
public:
	Data1() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

template<>
class Data1<int, int>
{
public:
	Data1()
	{
		cout << "Data1<int, int>" << endl;
	}
private:
	int _d1;
	int _d2;
};

void Test4(){
	Data1<int, int> d1;      //���ػ�ģ�������
	Data1<int, double> d2;
}

//ƫ�ػ��������ֱ��֣������ػ��Ͳ�������һ��������
template<class T1, class T2>
class Data2
{
public:
	Data2() { cout << "Data2<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

// �����ػ�����ģ������б��в��ֲ������ͻ�
template<class T1>
class Data2<T1, int>
{
public:
	Data2()
	{
		cout << "Data2<T1, int>" << endl;
	}

private:
	T1 _d1;
	int _d2;
};


// ƫ�ػ�����ģ������б��е��������Ƹ����ϸ�
template<class T1, class T2>
class Data2<T1*, T2*>
{
public:
	Data2()
	{
		cout << "Data2<T1*, T2*>" << endl;
	}
private:
	T1* _d1;
	T2* _d2;
};

void Test5(){					 
	Data2<int, int> d1;      //�ò����ػ�ģ�������
	Data2<double, int> d2;   //�ò����ػ�ģ�������     ��Ϊ����Ķ���int����������������ػ�ģ��
	Data2<int, double> d3;
	Data2<double, double> d4;



	Data2<int*, int> d5;
	Data2<int, int*> d6;
	Data2<int*, int*> d7;
	Data2<int*, double*> d8;
}

// дһ��ͨ�õĿ���������Ҫ��Ч�ʾ����ܸ�
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* str = new char[strlen(s._str) + 1];
			strcpy(str, s._str);
			delete[] _str;
			_str = str;
		}
	}

	~String()
	{
		delete[] _str;
	}

private:
	char* _str;
};
template<class T>
void Copy(T* dst, T* src, size_t size)
{
	memcpy(dst, src, sizeof(T)*size);
}
void TestCopy()
{
	int array1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int array2[10];
	Copy(array2, array1, 10);

	String s1[3] = { "1111", "2222", "3333" };
	String s2[3];            //�������ǵ�ַ���������ͬһ��ռ��ͷ����Σ��ᱨ��
	Copy(s2, s1, 3);
}


int main(){
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	TestCopy();
	system("pause");

}