#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <list>
using namespace std;

template <class T>
void Print(const list<T> &L)
{
	
	auto it = L.begin();
	cout << "------------------------------" << endl;
	//cout << *L.end() << endl;
	printf("%p\n", L.begin());
	printf("%p\n", L.end());    
	printf("%p\n", *(&L.begin()));
	printf("%p\n", *(&L.end()));//打印结果还是一样的  ？？？？？？？？？？？？？？？？？？？？？
	                            //四个结果是一样的
	                            //begin迭代器返回的是第一个节点的地址，end()返回的是头结点的地址，不管是返回结点所在空间的首字节地址或者_date所在空间地址，都不应该相同
	// L.end() list_iterator<T>类型，类型里有ListNode<T>* 这样一个指针
	//打印的是L.end() 这个对象的地址
	//监视结果陈旧？？？？？？？？？？？？？？？
	if (L.begin() == L.end())
	{
		cout << "same" << endl;
	}
	else{
		cout << "diffirent" << endl;
	}
	cout << "size():" << L.size() << endl;

	while (it != L.end())
	{
		cout << *it << ' ';
		it++;
	}
	cout << endl;
	//cout << "end:" << it << endl;
	printf("%p\n", it);
	
}

template <class T>
void Print1(const list<T> &L)
{

	auto it = L.end();
	cout << "------------------------------" << endl;
	//cout << *L.end() << endl;
	printf("%p\n", L.begin());
	printf("%p\n", L.end());           
	printf("%p\n", *(&L.begin()));
	printf("%p\n", *(&L.end()));

	if (L.begin() == L.end())
	{
		cout << "same" << endl;
	}
	else{
		cout << "diffirent" << endl;
	}
	cout << "size():" << L.size() << endl;

  	while (it != L.begin())         
	{
		it--;             //要放前用的是正向迭代器        L.end（）不能++，因为++后就访问到头节点了，头结点无值访问
		cout << *it << ' ';
		//it--;
		
		
	}
	cout << endl;
	//cout << "end:" << it << endl;
	printf("%p\n", it);

}
template <class T>
void Print2(const list<T> &L)
{

	auto it = L.rend();            //若返回的是begin   那应该和print一样的，但是此处若是
	cout << "------------------------------" << endl;


	while (it != L.rbegin())       
	{
		it--;                              //rend返回的是begin，--内部实现其实是++，因而只能--
		                                   
		cout << *it << ' ';
		/*T& operator*()
		{
			Iterator temp = _it;
			--temp;
			return *temp;
		}*/              //*内部实现，指针又转换为正向的啦
		
		//it--;           //也是要放前边的，因为内部要--，你要先把指针向后移动，他才能去到这个元素地址去*取得是下一个元素

	}
	cout << endl;
	//cout << "end:" << it << endl;
	printf("%p\n", it);

}
template <class T>
void Print3(const list<T> &L)
{

	auto it = L.rbegin();          //返回的是end()  
	while (it != L.rend())
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;
	//cout << "end:" << it << endl;
	printf("%p\n", it);

}

bool IsOdd(int data)
{
	if (0 == data % 2)
		return true;

	return false;
}
void Test1()
{
	//构造
	list<int> L1;
	list<int> L2(3, 5);
	list<int> L3(L2);
	list<int> L4{ 1, 2, 3, 5,4, 5 };
	list<int> L5(L4.begin(), L4.end());
	cout << L1.size() << endl;
	L1 = L4;
	
	
	//迭代器
	Print(L2);
	Print(L3);
	Print(L4);
	Print(L5);
	Print(L1);
	//容量修改
	cout << "-----------------------容量：-----------------" << endl;
	cout<<L1.size()<<endl;
	L1.resize(10,2);
	Print(L1);

	cout<<L1.empty()<<endl;
	L1.clear();
	Print(L1);


	


	//元素访问
	cout << "-----------------------元素访问：-----------------" << endl;
	cout << L4.front() << endl;
	cout << L4.back() << endl;
	//cout << L4[5] << endl;    //不可下标访问，因为是链表，不是顺序表，因而要找那个数，要用++操作

	//元素修改
	L4.push_front(10);
	Print(L4);
	L4.pop_front();
	Print(L4);
	L4.push_back(10);
	Print(L4);
	L4.pop_back();
	Print(L4);
	L4.insert(find(L4.begin(), L4.end(), 2), 10);
	Print(L4);
	L4.erase(find(L4.begin(), L4.end(), 2));
	Print(L4);
	cout << "remove:" ;
	L4.remove(5);    //删除链表中所有的5
	Print(L4);
	L4.sort();
	Print(L4);
	L4.push_back(10);
	Print(L4);
	cout << "unique:";
	L4.unique();          //去重（相邻两个元素）所以使用前要先排序
	Print(L4);
	cout << "merge:";

	L4.merge(L3);         //合并传入的必须是排序好的  顺便排序  自己与自己无法合并
	Print(L4);
	L5 = L4;
	L4.merge(L5);
	Print(L4);
	// remove_if：删除所有满足条件的节点
	// 条件：就是该函数的参数，传入参数是个函数指针
	// 该函数的实现原理：对每个节点中的值域用参数条件进行验证，如果满足则删除，如果不满足什么都不做
	L4.remove_if(IsOdd);  

	Print(L4);

	

	L4.swap(L1);
	Print(L4);
	

}

int main(){

	Test1();

	system("pause");
	return 0;
}
