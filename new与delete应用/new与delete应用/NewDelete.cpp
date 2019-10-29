#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//��c�����У��ڶ������붯̬�ڴ���ͨ��malloc��calloc��realloc���ͷ�ͨ��free���ͷ��ڴ�
//��C++�У��ڴ����ķ�ʽҲ������c��4��������ʵ�֡�������Щ�ط��е��鷳��c++��������new��delete���������ж�̬�ڴ����

#if 0
//Q1:�÷���
int main(){
	int *ptr1 = new int;        //��̬����һ��int���͵Ŀռ�
	int *ptr2 = new int(10);    //��̬����һ��int���͵Ŀռ䲢��ʼ��Ϊ10
	int *ptr3 = new int[10];    //��̬����10��int���͵Ŀռ�
	int *ptr4 = new int[5]{1, 2, 3, 4, 5};   //��̬����5��int���͵Ŀռ䲢��ʼ��Ϊ1 2 3 4 5

	//ptr1��ptr2��ptr3��ptr4����ָ��һ���ڴ�ռ��ָ�룬�����Ǳ�����һ������ָ��
	//new����Ŀռ䲻��Ҫָ���п�
	//����new���ٵĿռ��ǲ���ǿת�ģ���Ϊ���õ�ʱ������ͣ�֪������ʲô���͵�ָ����˲���ǿת

	//�ͷţ�������ͷŵ���Ԫ�صĿռ䣬ʹ��new��delete��������������ͷ������Ŀռ䣬ʹ��new[]��delete[]
	delete ptr1;
	delete ptr2;
	delete[] ptr3;
	delete[] ptr4;


	system("pause");
	return 0;
}
#endif

#if 1
//Q2��ע��new��deleteҪ���ʹ�ã�new����free�ͷţ�malloc������delete�ͷţ���Щʱ������


//�����������������͵Ŀռ䣬new��malloc��delete��free�������ƣ���ͬ�ĵط��ǣ�new/delete�����
//�ͷŵ��ǵ���Ԫ�صĿռ䣬new[]��delete[]������������ռ䣬����new������ռ�ʧ��ʱ�����쳣��
//malloc�᷵��NULL��
//����������������͵Ŀռ䣬����Բ�������.
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

//����������Զ���Ŀռ䣬�����������
// new��������ռ�Ȼ��������Ŀռ���ù��캯����������free���������������--�����е���Դ���ᱻ���٣�������ڴ�й©
//malloc������ù��캯����delete����������������ͷ�new����Ķ���Ŀռ�--���ͷ���Ч�ռ䣬��������
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
		delete _p;                    //ע�⣺�����������в�Ҫ�� delete һ����������� ����������ѭ������Ϊdeleteһ�£��������������һ����delete�ٽ�������
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
	int* _p;
};


void Test2()
{

	// ��malloc����ռ�ʱ������ù��캯��--�������������С��ͬ��һ���ڴ�ռ䣬ֻ��һ���С��ͬ�Ŀռ䣬�����ܽ��ÿ��ڴ�ռ俴����һ������
	          
	//A* p1 = (A*)malloc(sizeof(A));
	//A* p2 = (A*)malloc(sizeof(A));
	//delete p1;                         //�����
	//delete[] p2;


	A* p3 = new A;
	A* p4 = new A;
	A* p7 = new A;
	free(p3);
	delete p4;
	//delete[] p7;        //�����

	A* p5 = new A[10];
	A* p6 = new A[10];
	delete p5;           //�����
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
//Q3:new��delete����������     operator new��operator delete
//new��delete���û����ж�̬�ڴ�������ͷŵĲ�������operator new ��operator delete��ϵͳ�ṩ��
//ȫ�ֺ�����new�ڵײ����operator newȫ�ֺ���������ռ䣬delete�ڵײ�ͨ��operator deleteȫ��
//�������ͷſռ䡣

//��������operator new�ײ�ʵ��
/*
operator new���ú���ʵ��ͨ��malloc������ռ䣬��malloc����ռ�ɹ�ʱֱ�ӷ��أ�����ռ�ʧ�ܣ�����
ִ�п� �䲻��Ӧ�Դ�ʩ�������Ӧ�Դ�ʩ�û������ˣ���������룬�������쳣��

void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
{
	// try to allocate size bytes
	void *p;
	while ((p = malloc(size)) == 0)      //ͨ��malloc������ռ�//����ռ�ʧ�ܣ������׳��쳣��ֱ������ɹ�Ϊֹ
	                                    //�ɹ�������ѭ��    �˴�����Ϊʲônew�����пյ�ԭ��
	if (_callnewh(size) == 0)           
	{
		// report no memory
		// ��������ڴ�ʧ���ˣ�������׳�bad_alloc �����쳣
		static const std::bad_alloc nomem;
		_RAISE(nomem);
	}
	return (p);
}
*/


/*
operator delete: �ú���������ͨ��free���ͷſռ��

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


//Q3.new.delete����Ӧ��

#if 0

//Q3.1�Լ�д������ʵ��
//1. new--->�ܹ�������ռ����Ϣ��ӡ
//2. delete--->�ܹ����ͷſռ���Ϣ��ӡ
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

#define new new(__FILE__, __FUNCDNAME__, __LINE__)     //��������õı������ļ����㣬���������к�

int main()
{
	//int* p = new(__FILE__, __FUNCDNAME__, __LINE__) int;

	int* p1 = new int;

	delete p1;
	return 0;
}
#endif

#if 0
//Q3.2:new��delete���������ר������:ʵ������ڵ�ʹ���ڴ��������ͷ��ڴ�
struct ListNode{
	int _date;
	ListNode* _pre;
	ListNode* _next;
	 
	 void* operator new(size_t n)
	 {
		 void* p = nullptr;
		 p = allocator<ListNode>().allocate(1);    //ָ���ڴ�ص�һ���ڴ�
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

//���һ���ֻ࣬���ڶ��ϴ�������
//�����������캯���Ϳ������캯������Ϊ˽�е�(��ֹͨ��Ĭ�Ϲ��캯������������)����ֹ����������ջ�����ɶ���Ȼ���������ṩһ����̬��Ա�������ڸþ�̬��Ա��������ɶѶ���Ĵ���

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
	/*Ҳ���Զ�����������Ĭ�Ϲ��캯���ĸ���
	// C++98
	// 1.ֻ����,��ʵ�֡���Ϊʵ�ֿ��ܻ���鷳�����㱾����Ҫ
	// 2.������˽��
	A(const A&);

		// or

 
 // C++11 
 A(const A&) = delete;//ɾ��Ĭ�ϵĿ������캯��
 */
};
int main(){
	A::CreatObject();//ֻ��ͨ��������������������

	system("pause");
	return 0;
}
#endif