#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;


//C++允许在同一作用域中声明几个功能类似的同名函数，这些同名函数的形参列表(参数个数 或 类型 或 顺序)必须不同，常用来处理实现功能类似数据类型不同的问题


#if 0

//c语言中不行是因为编译器换的名字不包含返回值，形参列表等信息，只在函数名前多加一个下划线，因此c语言中不可以出现函数重载
//在编译时，编译器会分别给两个函数换名字,名字中包含了形参列表的信息，由此可以区分
int Add(int x, int y);
double Add(double x, double y);
#endif 

#if 0
//函数不可通过返回值来重载
int Add(int x, int y){
	return x + y;
}
short  Add(int x, int y){
	return x + y;
}
#endif

#if 0
//无参函数，与缺省函数无法形成重载，因为调用时如果不传参，编译器不知道应该调用哪一个
void Fun(){
	
}
void Fun(int x = 0){

}
#endif


#if 0
//缺省函数无法与同名的函数重载，同理，编译器不知道要调用哪个
void Fun1(int x){

}
void Fun1(int x = 0){        //会报已有主体

}
#endif

#if 0
//函数前加 extern "C"表示本函数用c的规则
extern "C" int add(int x, int y);      //编译替换的函数名为_add 是c语言的规则
#endif

int main()
{
	//Fun();        //此处会报错
	//Fun1(2);         //不加形参汇报传递参数太少
	//add(1, 2);

}
