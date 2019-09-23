#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
//static关键字在类中的用法可通过一道题来引入：
//求Date总共创建了多少个有效对象？    --- 有效即存在的，已通过构造（宝库欧拷贝构造）函数构造出来的又没通过析构函数消除的
// 最终需要结果：对象的个数---计数--int



//所以问题来了，计数器做成全局变量？还是成员变量？

#if 0
//W1:做成成员变量

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
	int count;        //到此处，会发现无论怎么写，一个对象都无法和另外一个对象里的count有关系，count也不能实现在上一个对象的count上执行++操作
};                    //所以，count肯定是不能作为普通成员来给值的
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
//Way2:做全局变量
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
//可发现这个方法是可以的，但是有个问题，count是全局变量，在哪都可以修改，那随便在哪个地方给count赋个值，结果就不对了。
#endif


//然后我们再来发现static的用处：
//Q1:修饰变量：static的类成员称为类的静态成员，用static修饰的成员变量，称之为静态成员变量
//有以下特性：
//1.静态成员为所有类对象所共享，不属于某个具体的实例.意思是这个变量对于每个对象来说都是一个变量。是共同可以拥有的。
//2.静态成员变量必须在类外定义/初始化，定义时不添加static关键字。如果在类内定义，那么每创建一个对象，就将count的值给重新赋值修改了。那么他共享的意义就没有了
//3.类静态成员可用类名::静态成员(共享的是类的属性，不随对象)||对象.静态成员来访问
//4.静态成员和类的普通成员一样，也有public、protected、private3种访问级别，也可以具有返回值

#if 0
//Way3：通过static可以轻松完美的解决这个问题
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
int A1::count = 0;    //静态成员变量是类的属性

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
	// 静态成员变量是所有类对象共享的成员变量，不属于某个具体的对象，以下输出结果一样
	cout << x4.count << endl;
	cout << x5.count << endl;
	return 0;
}
#endif

//Q2:修饰成员函数：用static修饰的成员函数，称之为静态成员函数。当要在其他函数里读取私有的静态成员，可用一个静态函数来读取
//特性：静态成员函数没有隐藏的this指针，不能访问任何非静态成员
//        成员函数也不属于任何一个对象，访问也可以使用上面所述的两种方法来访问

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
	//cout << A1::count << endl;//这个两个方法是无法访问的

	cout << x5.Getcount() << endl;
	cout << A1::Getcount() << endl;//这两个方法是可以访问的
	return 0;
}
#endif


#if 0
//Q3:静态变量不在对象中，因而对象的大小不包含成员变量

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

//Q4;1. 静态成员函数不可以调用非静态成员函数     原因很简单，上面说静态成员函数中不会传this指针，而非静态成员函数是需要this指针传入的，因而在静态成员函数中调用非静态成员函数是无法给非静态成员函数传入this指针的
//   2.非静态成员函数可以调用类的静态成员函数    静态函数不需要this指针，非静态成员函数不影响静态的






//Q5:static应用：求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C)


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
	//在线OJ做法
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


	//Q6:看博客，在c语言中static和在c++中static的对比