#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//在c语言中，在堆上申请动态内存是通过malloc，calloc，realloc。释放通过free来释放内存
//在C++中，内存管理的方式也可以用c的4个函数来实现。但是有些地方有点麻烦。c++又引入了new和delete操作符进行动态内存管理

#if 0
//Q1:用法：
int main(){
	int *ptr1 = new int;        //动态申请一个int类型的空间
	int *ptr2 = new int(10);    //动态申请一个int类型的空间并初始化为10
	int *ptr3 = new int[10];    //动态申请10个int类型的空间
	int *ptr4 = new int[5]{1, 2, 3, 4, 5};   //动态申请5个int类型的空间并初始化为1 2 3 4 5

	//ptr1、ptr2、ptr3、ptr4都是指向一块内存空间的指针，但他们本身是一个整形指针
	//new申请的空间不需要指针判空
	//而且new开辟的空间是不用强转的，因为调用的时候给类型，知道返回什么类型的指针因此不用强转

	//释放：申请和释放单个元素的空间，使用new和delete操作符，申请和释放连续的空间，使用new[]和delete[]
	delete ptr1;
	delete ptr2;
	delete[] ptr3;
	delete[] ptr4;


	system("pause");
	return 0;
}
#endif

#if 1
//Q2：注：new与delete要配对使用，new创建free释放，malloc创建和delete释放，有些时候会出错


//如果申请的是内置类型的空间，new和malloc，delete和free基本类似，不同的地方是：new/delete申请和
//释放的是单个元素的空间，new[]和delete[]申请的是连续空间，而且new在申请空间失败时会抛异常，
//malloc会返回NULL。
//若申请的是内置类型的空间，不配对产生错误.
void Test1()
{
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = (int*)malloc(sizeof(int));
	delete p1;
	delete[] p2;

	int* p3 = new int;
	int* p4 = new int;
	free(p3);
	//delete[] p4;

	int* p5 = new int[10];
	int* p6 = new int[10];
	free(p5);
	delete[] p6;
}

//若申请的是自定义的空间，会有问题出现
// new会先申请空间然后在申请的空间调用构造函数创建对象，free不会调用析构函数--对象中的资源不会被销毁，会产生内存泄漏
//malloc不会调用构造函数，delete会调用析构函数再释放new申请的对象的空间--会释放无效空间，程序会崩掉
class A
{
public:
	A()
	{
		_data = 10;
		_p = new int;
		cout << "Test():" << this << endl;
	}

	~A()
	{
		delete _p;                    //注意：在析构函数中不要放 delete 一个本类类对象， 否则会进入死循环，因为delete一下，进入这个析构，一进又delete再进，，，
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
	int* _p;
};


void Test2()
{

	// 用malloc申请空间时不会调用构造函数--申请的是与对象大小相同的一块内存空间，只是一块大小相同的空间，还不能讲该块内存空间看成是一个对象
	          
	//A* p1 = (A*)malloc(sizeof(A));
	//A* p2 = (A*)malloc(sizeof(A));
	//delete p1;                         //会崩掉
	//delete[] p2;


	A* p3 = new A;
	A* p4 = new A;
	A* p7 = new A;
	free(p3);
	delete p4;
	//delete[] p7;        //会崩掉

	A* p5 = new A[10];
	A* p6 = new A[10];
	delete p5;           //会崩掉
	delete[] p6;
}

int main()
{
	Test1();
	
	system("pause");
	return 0;
}

#endif

#if 0
//Q3:new和delete操作符函数     operator new和operator delete
//new和delete是用户进行动态内存申请和释放的操作符，operator new 和operator delete是系统提供的
//全局函数，new在底层调用operator new全局函数来申请空间，delete在底层通过operator delete全局
//函数来释放空间。

//我们来看operator new底层实现
/*
operator new：该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间失败，尝试
执行空 间不足应对措施，如果改应对措施用户设置了，则继续申请，否则抛异常。

void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
{
	// try to allocate size bytes
	void *p;
	while ((p = malloc(size)) == 0)      //通过malloc来申请空间//申请空间失败，进入抛出异常，直到申请成功为止
	                                    //成功就跳出循环    此处就是为什么new不用判空的原因
	if (_callnewh(size) == 0)           
	{
		// report no memory
		// 如果申请内存失败了，这里会抛出bad_alloc 类型异常
		static const std::bad_alloc nomem;
		_RAISE(nomem);
	}
	return (p);
}
*/


/*
operator delete: 该函数最终是通过free来释放空间的

void operator delete(void *pUserData)
{
	_CrtMemBlockHeader * pHead;
	RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
	if (pUserData == NULL)
		return;
	_mlock(_HEAP_LOCK); //block other threads 
__TRY
// get a pointer to memory block header 
pHead = pHdr(pUserData);
// verify block type 
_ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
_free_dbg(pUserData, pHead->nBlockUse);
__FINALLY
_munlock(_HEAP_LOCK); // release other threads 
__END_TRY_FINALLY
return;
}
*/
#endif


//Q3.new.delete重载应用

#if 0

//Q3.1自己写个重载实现
//1. new--->能够将申请空间的信息打印
//2. delete--->能够将释放空间信息打印
void* operator new(size_t size, const char* filename, const char* funName, size_t lineNo)
{
	cout << filename << "-" << funName << "-" << lineNo << "-" << size << endl;
	return malloc(size);
}

void operator delete(void* p, const char* filename, const char* funName, size_t lineNo)
{
	cout << filename << "-" << funName << "-" << lineNo << endl;
	free(p);
}

#define new new(__FILE__, __FUNCDNAME__, __LINE__)     //三个定义好的变量，文件名你，函数名，行号

int main()
{
	//int* p = new(__FILE__, __FUNCDNAME__, __LINE__) int;

	int* p1 = new int;

	delete p1;
	return 0;
}
#endif

#if 0
//Q3.2:new，delete关于链表的专属重载:实现链表节点使用内存池申请和释放内存
struct ListNode{
	int _date;
	ListNode* _pre;
	ListNode* _next;
	 
	 void* operator new(size_t n)
	 {
		 void* p = nullptr;
		 p = allocator<ListNode>().allocate(1);    //指向内存池的一块内存
		 cout << "memory pool allocate" << endl;
		 return p;
	 }
	 void operator delete(void* p)
	 {
		 allocator<ListNode>().deallocate((ListNode*)p, 1);
		 cout << "memory pool deallocate" << endl;
	 }

};
class List{
public:
	List()
	{
		_head = new ListNode;
		_head->_next = _head;
		_head->_pre = _head;
	}
	~List()
	{
		ListNode *cur;
		while (_head){
			cur = _head;
			_head = _head->_next;
			delete cur;
		}
		_head = nullptr;
	}
private:
	ListNode* _head;
};
void TestList()
{
	List l;
}

int main()
{
	TestList();
	return 0;
}
#endif

#if 0

//设计一个类，只能在堆上创建对象
//方法：将构造函数和拷贝构造函数定义为私有的(禁止通过默认构造函数来创建对象)，防止其他函数在栈上生成对象。然后在类中提供一个静态成员函数，在该静态成员函数上完成堆对象的创建

class A{

public:
	static A* CreatObject(){
		return new A;
	}

private:
	A(){

	}
	A(const A &x)
	{

	}
	/*也可以定义这样避免默认构造函数的干扰
	// C++98
	// 1.只声明,不实现。因为实现可能会很麻烦，而你本身不需要
	// 2.声明成私有
	A(const A&);

		// or

 
 // C++11 
 A(const A&) = delete;//删除默认的拷贝构造函数
 */
};
int main(){
	A::CreatObject();//只能通过这样定义来创建对象

	system("pause");
	return 0;
}
#endif