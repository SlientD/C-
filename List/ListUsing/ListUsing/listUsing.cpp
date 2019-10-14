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
	//����
	list<int> L1;
	list<int> L2(3, 5);
	list<int> L3(L2);
	list<int> L4{ 1, 2, 3, 5,4, 5 };
	list<int> L5(L4.begin(), L4.end());
	cout << L1.size() << endl;
	L1 = L4;
	
	
	//������
	Print(L2);
	Print(L3);
	Print(L4);
	Print(L5);
	Print(L1);
	//�����޸�
	cout << "-----------------------������-----------------" << endl;
	cout<<L1.size()<<endl;
	L1.resize(10,2);
	Print(L1);

	cout<<L1.empty()<<endl;
	L1.clear();
	Print(L1);


	


	//Ԫ�ط���
	cout << "-----------------------Ԫ�ط��ʣ�-----------------" << endl;
	cout << L4.front() << endl;
	cout << L4.back() << endl;
	//cout << L4[5] << endl;    //�����±���ʣ���Ϊ����������˳������Ҫ���Ǹ�����Ҫ��++����

	//Ԫ���޸�
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
	L4.remove(5);    //ɾ�����������е�5
	Print(L4);
	L4.sort();
	Print(L4);
	L4.push_back(10);
	Print(L4);
	cout << "unique:";
	L4.unique();          //ȥ�أ���������Ԫ�أ�����ʹ��ǰҪ������
	Print(L4);
	cout << "merge:";

	L4.merge(L3);         //�ϲ�����ı���������õ�  ˳������  �Լ����Լ��޷��ϲ�
	Print(L4);
	L5 = L4;
	L4.merge(L5);
	Print(L4);
	// remove_if��ɾ���������������Ľڵ�
	// ���������Ǹú����Ĳ�������������Ǹ�����ָ��
	// �ú�����ʵ��ԭ����ÿ���ڵ��е�ֵ���ò�������������֤�����������ɾ�������������ʲô������
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
