#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;





int main()
{
	//Q1.构造方法
	cout << "构造方法" << endl;
	vector<int> v1;        //vector()
	cout << v1.size() << endl;
	v1.push_back(3);
	cout << v1.size() << endl;
	system("pause");



	vector<int> v2(4);  //vector (n,m);  构造并初始化n个m,m默认为0
	vector<int> v3(v2);     //vector (const vector &x);  拷贝构造
	vector<int> v4(v3.begin(), v3.begin() + 2); //迭代器构造，从开始到结尾
	vector<int> v5{ 1, 2, 3, 4, 5 };
	v1 = v5;
	vector<vector<int>> v6(2);   //定义一个二维数组


	
	//Q2.迭代器
	for (int i = 0; i < sizeof(v2) / sizeof(v2[0]); i++)   //for循环遍历
	{
		cout << v2[i] << ' ';
	}
	cout << endl;

	for (auto e:v2)          //当要对空间里的内容修改，或空间里的内容是自定义类型（若不加引用直接给值会进行一次拷贝构造，效率低）时，e要用引用
	{
		cout << e << " ";
	}
	cout << endl;

	//vector<int>::iterator it = v2.begin();
	auto it = v5.begin();
	while (it != v5.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	
	 it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;


	//Q3.容量
	cout << "容量" << endl;
	//1.size
	cout << v1.size() << endl;
	//2.capacity
	cout << v1.capacity() << endl;
	//3.empty
	cout << v1.empty() << endl;
	//4.resize-->同string类中的用法
	v1.resize(7, 1);
	v1.resize(2, 1);
	v1.resize(5);
	cout << v1.size() << endl;
	cout << v1.capacity() << endl;
	//5.reserve
	cout << "reserve" << endl;
	v5.reserve(20);     //给v5预留20个空间，注意，每次扩容几乎变量表示的空间都要换地方，地址也会发生改变
	cout << v5.size() << endl;   //v5的有效元素只有5个
	//v5[6]=3;            //会抛出越界异常错误  注意：虽然reserve了20个空间，但是有效个数改的看size（）有几个，而不是有空间就可以用了
	
	
	size_t sz;
	std::vector<int> foo;
	foo.reserve(100);       //在大概知道要用多少空间的情况下，直接扩容，避免每次扩容降低代码效率
	sz = foo.capacity();
	
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);//SeqList 扩容方式：开辟新空间  拷贝元素 释放旧空间  效率低
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	//vs下capacity是1.5倍增长的，在linux下 g++是2倍增长的





	//访问：[] at

	//内容修改查找
	v5.push_back(1); //尾插
	v5.pop_back();   //尾删

	//int pos = v5.find(3);   //在vector中，find不是成员函数了，而是作为算法模块实现的，此处会出现语法错误v5中没有成员函数find
	vector<int>::iterator pos = find(v5.begin(), v5.end(), 3);    //注意返回值     传参传入范围加要查找的值

	v5.insert(pos, 10);   //在pos的位置差诶元素10   注意传参pos的类型

	v5.erase(pos);           //删除pos位置的数据    注意传参pos的类型

	v5.swap(v2);          //交换两个vector的数据空间   
	swap(v5, v2);         //当然可也以这么写，不调用成员函数，但是推荐上面的写法，因为这种写法必定要创建临时变量，效率不如上面的高
	


	//迭代器失效问题：
	vector<int> v{ 1, 2, 3, 4, 5, 6 ,7};
	/*it = v.begin();
	cout << v.capacity() << endl;
	v.push_back(10);                            //会扩容，v的空间整体迁移，因而it指向的空间便变得无效了
	cout << v.capacity() << endl;
	while (it != v.end())                          //此处会报错   迭代器失效了
	{
		cout << *it << " ";
		cout << endl;
	}*/
	

	//通过这个例子举一反三：要是涉及扩容的操作如：resize，reserve，insert都会导致迭代器失效
	//解决方法：重新给it赋值即可
	it = v.begin();
	cout << v.capacity() << endl;
	v.push_back(10);   //会扩容，v的空间整体迁移，因而it指向的空间便变得无效了
	it = v.begin();
	cout << v.capacity() << endl;
	while (it != v.end())                          //此处会报错   迭代器失效了
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	

	//erase也会使其失效
	auto pos1 = find(v.begin(), v.end(), 3);
	cout << v.capacity() << endl;
	v.erase(pos1);
	cout << v.capacity() << endl;
	cout << *pos1 << endl;                      //会报错

	/*//解决方法：
	pos1 = v.erase(pos1);                   //因为erase会返回下一个空间的地址，所以可通过这种方法来使迭代器继续使用
	//或者：
	v.erase(pos1++);                         //传入前先将pos1往后移，再将之前的值传入也可实现
   */
	



	



	system("pause");
	return 0;
}