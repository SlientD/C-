#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//�ڶ���ָ�����ʱ��Ҫ��ָ��һ��ָ�򣬷���ָ����ܻ�û�кϷ���ָ�򣬱��һ��Ұָ�롣��c�����У�������NULL��û��ָ���ָ�븳��ֵ
//NULLʵ������һ���꣬NULL������Ϊ���泣��0�����߱�����Ϊ������ָ��(void*)�ĳ��������������һЩ������������
//�磺
void f(int)
{
	cout << "f(int)" << endl;
}
void f(int*)
{
	cout << "f(int*)" << endl;
}
int main()
{
	f(0);                    //���õ��ǵ�һ������
	f(NULL);                 //���õ������ǵ�һ��������Ȼ�����ǽ�NULL����ָ�룬�ڴ�NULLָ���ʱ����ʵ����������������ڶ���������
	f((int*)NULL);
	//���c++������nullptr��ר�Ŵ���һ��ָ���ֵ������
	int *ptr = nullptr;
	f(ptr);                //�ᷢ�����ǽ����˵ڶ�������
	//nullptr�������͵ģ�������Ϊnullptr_t���������Ա���ʽת��Ϊָ�����ͣ�nullptr_t��������ͷ�ļ��У�typedef decltype(nullptr) nullptr_t;
	    //��nullptr��ʾָ���ֵ���ð���ͷ�ļ�����Ϊnullptr��C++11��Ϊ�¹ؼ�������ġ�
		// ��C++11�У�sizeof(nullptr) �� sizeof((void*)0)��ռ���ֽ�����ͬ��ָ��ռ���ֽ�����Ϊ4
		//Ϊ����ߴ���Ľ�׳�ԣ��ں�����ʾָ���ֵʱ�������ʹ��nullptr��
	return 0;
}

