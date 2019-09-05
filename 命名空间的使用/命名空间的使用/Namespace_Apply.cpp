#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

int a = 10;

//命名空间：一个命名空间就定义了一个新的作用域，命名空间中的所有内容都局限于该命名空间中
//命名空间定义一：直接用namespace+命名空间名定义一个命名空间
namespace N1{

	int a = 1;
	int fun(int x)
	{
		return x+1;
	}
}                                  //定义结构体是需要分号的，此处不用
//命名空间定义二：嵌套使用
namespace N2{
	int a = 2;
	int fun(int x)
	{
		return x + 2;
	}
	namespace N3{
		int a = 3;
		int fun(int x)
		{
			return x + 3;
		}
	}
}
//命名空间定义三：并列定义，可存在多个相同名称的命名空间，编译器会自动合并为一个命名空间，因而两个里面的变量不可重复
namespace N4{
	int a = 4;
}
namespace N4{
	int b = 4;
}


////用法二：直接用using+命名空间变量名或函数名，将其引入使用：
//using N1::a;         //在此要把之前定义的a删掉，不然会重复

//用法三：直接using+命名空间名，将命名空间所有变量和函数都引入
using namespace N2;                               //上面也引入了a，会冲突，下面使用时会不明确


int main()
{
	//int a = 0;
	
	//namespace 的用法一：
	//printf("%d ", a);   //在未指定是哪的变量时，会用函数里的局部变量，就近使用。
	printf("%d ", ::a); // ::为作用域限定符  在前面未加命名空间时，是指全局变量的作用域
	printf("%d ", N1::a);   //命名空间名+作用域限定符  +所要引用的变量或函数
	//printf("%d ", N1::fun(a));
	printf("%d ", N2::N3::a);  //嵌套调用时，一层一层进入找到变量

	printf("%d", a);
	



	system("pause");
	return 0;
}