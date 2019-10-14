#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <list>
using namespace std;

template <class T>
void Print(const list<T> &L)
{
	
	auto it = L.begin();
	cout << "------------------------------" << endl;
	/*cout << *L.end() << endl;
	printf("%p\n", L.begin());
	printf("%p\n", L.end());
	if (L.begin() == L.end())
	{
		cout << "same" << endl;
	}
	else{
		cout << "diffirent" << endl;
	}*/
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
