#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
//static�ؼ��������е��÷���ͨ��һ���������룺
//��Date�ܹ������˶��ٸ���Ч����    --- ��Ч�����ڵģ���ͨ�����죨����ŷ�������죩���������������ûͨ����������������
// ������Ҫ���������ĸ���---����--int



//�����������ˣ�����������ȫ�ֱ��������ǳ�Ա������

#if 0
//W1:���ɳ�Ա����

class A1{
public:
	A1()
	{
		count++;

	}
	A1(const A1 &x)
	{
		count++;
	}
	~A1(){
		count--;
	}
public:
	int x;
	int count;        //���˴����ᷢ��������ôд��һ�������޷�������һ���������count�й�ϵ��countҲ����ʵ������һ�������count��ִ��++����
};                    //���ԣ�count�϶��ǲ�����Ϊ��ͨ��Ա����ֵ��
int  Test()
{
	A1 x1;
	A1 x2;
	A1 x3(x1);
	return x3.count;

}
int main()
{
	A1 x4;
	int total=Test();
	cout << total << endl;
	
	return 0;

}
#endif

#if 0
//Way2:��ȫ�ֱ���
int count = 0;
class A1{
public:
	A1()
	{
		::count++;

	}
	A1(const A1 &x)
	{
		::count++;
	}
	~A1(){
		::count--;
	}
public:
	int x;
};
void  Test()
{
	A1 x1;
	A1 x2;
	A1 x3(x1);
	

}
int main()
{
	Test();
	A1 x4;
	
	cout << ::count << endl;

	return 0;

}
//�ɷ�����������ǿ��Եģ������и����⣬count��ȫ�ֱ��������Ķ������޸ģ���������ĸ��ط���count����ֵ������Ͳ����ˡ�
#endif


//Ȼ��������������static���ô���
//Q1:���α�����static�����Ա��Ϊ��ľ�̬��Ա����static���εĳ�Ա��������֮Ϊ��̬��Ա����
//���������ԣ�
//1.��̬��ԱΪ���������������������ĳ�������ʵ��.��˼�������������ÿ��������˵����һ���������ǹ�ͬ����ӵ�еġ�
//2.��̬��Ա�������������ⶨ��/��ʼ��������ʱ�����static�ؼ��֡���������ڶ��壬��ôÿ����һ�����󣬾ͽ�count��ֵ�����¸�ֵ�޸��ˡ���ô������������û����
//3.�ྲ̬��Ա��������::��̬��Ա(�������������ԣ��������)||����.��̬��Ա������
//4.��̬��Ա�������ͨ��Աһ����Ҳ��public��protected��private3�ַ��ʼ���Ҳ���Ծ��з���ֵ

#if 0
//Way3��ͨ��static�������������Ľ���������
class A1{
public:
	A1()
	{
		count++;

	}
	A1(const A1 &x)
	{
		count++;
	}
	~A1(){
		count--;
	}
private:
	int x;
public:
	static int count;
};
int A1::count = 0;    //��̬��Ա�������������

void  Test()
{
	A1 x1;
	A1 x2;
	A1 x3(x1);


}



int main()
{
	Test();
	A1 x4;
	A1 x5;
	// ��̬��Ա�����������������ĳ�Ա������������ĳ������Ķ�������������һ��
	cout << x4.count << endl;
	cout << x5.count << endl;
	return 0;
}
#endif

//Q2:���γ�Ա��������static���εĳ�Ա��������֮Ϊ��̬��Ա��������Ҫ�������������ȡ˽�еľ�̬��Ա������һ����̬��������ȡ
//���ԣ���̬��Ա����û�����ص�thisָ�룬���ܷ����κηǾ�̬��Ա
//        ��Ա����Ҳ�������κ�һ�����󣬷���Ҳ����ʹ���������������ַ���������

#if 0
//Way4:
class A1{
public:
	A1()
	{
		count++;

	}
	A1(const A1 &x)
	{
		count++;
	}
	~A1(){
		count--;
	}
	static int Getcount()
	{
		return count;
	}
private:
	int x;
	static int count;
};
int A1::count = 0;    

void  Test()
{
	A1 x1;
	A1 x2;
	A1 x3(x1);


}


int main()
{
	Test();
	A1 x4;
	A1 x5;
	
	//cout << x4.count << endl;  
	//cout << A1::count << endl;//��������������޷����ʵ�

	cout << x5.Getcount() << endl;
	cout << A1::Getcount() << endl;//�����������ǿ��Է��ʵ�
	return 0;
}
#endif


#if 0
//Q3:��̬�������ڶ����У��������Ĵ�С��������Ա����

class A1{
public:
	A1()
	{
		

	}
	A1(const A1 &x)
	{
		
	}
	~A1(){
		
	}
	static int Getcount()
	{
		return count;
	}
private:
	int x;
	static int count;
};



int main()
{
	A1 x1;
	cout << sizeof(x1) << endl;    //-->4
	system("pause");
	return 0;
}
#endif

//Q4;1. ��̬��Ա���������Ե��÷Ǿ�̬��Ա����     ԭ��ܼ򵥣�����˵��̬��Ա�����в��ᴫthisָ�룬���Ǿ�̬��Ա��������Ҫthisָ�봫��ģ�����ھ�̬��Ա�����е��÷Ǿ�̬��Ա�������޷����Ǿ�̬��Ա��������thisָ���
//   2.�Ǿ�̬��Ա�������Ե�����ľ�̬��Ա����    ��̬��������Ҫthisָ�룬�Ǿ�̬��Ա������Ӱ�쾲̬��






//Q5:staticӦ�ã���1+2+3+...+n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case�ȹؼ��ּ������ж���䣨A?B:C)


	class Sum{
	public:
		Sum(){
			count++;
			sum += count;
		}
		
		static int GetSum()
		{
			return sum;
		}
	private:
		static int sum;
		static int count;
	};

	int Sum::count = 0;
	int Sum::sum = 0;

	int main() {
		
		Sum A[2];
		cout << Sum::GetSum();
		system("pause");
		return 0;
	}
	/*
	//����OJ����
	class Solution {
	public:
		class Sum{
		public:
			Sum(){
				count++;
				sum += count;
			}
			static void Set()
			{
				sum = 0;
				count = 0;
			}
			static int GetSum()
			{
				return sum;
			}
		private:
			static int sum;
			static int count;
		};


		int Sum_Solution(int n) {
			Sum::Set();
			Sum A[n];

			return Sum::GetSum();
		}
	};

	int Solution::Sum::count = 0;
	int Solution::Sum::sum = 0;
	*/


	//Q6:�����ͣ���c������static����c++��static�ĶԱ�