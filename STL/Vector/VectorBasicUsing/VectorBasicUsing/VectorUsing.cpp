#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;





int main()
{
	//Q1.���췽��
	cout << "���췽��" << endl;
	vector<int> v1;        //vector()
	cout << v1.size() << endl;
	v1.push_back(3);
	cout << v1.size() << endl;
	system("pause");



	vector<int> v2(4);  //vector (n,m);  ���첢��ʼ��n��m,mĬ��Ϊ0
	vector<int> v3(v2);     //vector (const vector &x);  ��������
	vector<int> v4(v3.begin(), v3.begin() + 2); //���������죬�ӿ�ʼ����β
	vector<int> v5{ 1, 2, 3, 4, 5 };
	v1 = v5;
	vector<vector<int>> v6(2);   //����һ����ά����


	
	//Q2.������
	for (int i = 0; i < sizeof(v2) / sizeof(v2[0]); i++)   //forѭ������
	{
		cout << v2[i] << ' ';
	}
	cout << endl;

	for (auto e:v2)          //��Ҫ�Կռ���������޸ģ���ռ�����������Զ������ͣ�����������ֱ�Ӹ�ֵ�����һ�ο������죬Ч�ʵͣ�ʱ��eҪ������
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


	//Q3.����
	cout << "����" << endl;
	//1.size
	cout << v1.size() << endl;
	//2.capacity
	cout << v1.capacity() << endl;
	//3.empty
	cout << v1.empty() << endl;
	//4.resize-->ͬstring���е��÷�
	v1.resize(7, 1);
	v1.resize(2, 1);
	v1.resize(5);
	cout << v1.size() << endl;
	cout << v1.capacity() << endl;
	//5.reserve
	cout << "reserve" << endl;
	v5.reserve(20);     //��v5Ԥ��20���ռ䣬ע�⣬ÿ�����ݼ���������ʾ�Ŀռ䶼Ҫ���ط�����ַҲ�ᷢ���ı�
	cout << v5.size() << endl;   //v5����ЧԪ��ֻ��5��
	//v5[6]=3;            //���׳�Խ���쳣����  ע�⣺��Ȼreserve��20���ռ䣬������Ч�����ĵĿ�size�����м������������пռ�Ϳ�������
	
	
	size_t sz;
	std::vector<int> foo;
	foo.reserve(100);       //�ڴ��֪��Ҫ�ö��ٿռ������£�ֱ�����ݣ�����ÿ�����ݽ��ʹ���Ч��
	sz = foo.capacity();
	
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);//SeqList ���ݷ�ʽ�������¿ռ�  ����Ԫ�� �ͷžɿռ�  Ч�ʵ�
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	//vs��capacity��1.5�������ģ���linux�� g++��2��������





	//���ʣ�[] at

	//�����޸Ĳ���
	v5.push_back(1); //β��
	v5.pop_back();   //βɾ

	//int pos = v5.find(3);   //��vector�У�find���ǳ�Ա�����ˣ�������Ϊ�㷨ģ��ʵ�ֵģ��˴�������﷨����v5��û�г�Ա����find
	vector<int>::iterator pos = find(v5.begin(), v5.end(), 3);    //ע�ⷵ��ֵ     ���δ��뷶Χ��Ҫ���ҵ�ֵ

	v5.insert(pos, 10);   //��pos��λ�ò���Ԫ��10   ע�⴫��pos������

	v5.erase(pos);           //ɾ��posλ�õ�����    ע�⴫��pos������

	v5.swap(v2);          //��������vector�����ݿռ�   
	swap(v5, v2);         //��Ȼ��Ҳ����ôд�������ó�Ա�����������Ƽ������д������Ϊ����д���ض�Ҫ������ʱ������Ч�ʲ�������ĸ�
	


	//������ʧЧ���⣺
	vector<int> v{ 1, 2, 3, 4, 5, 6 ,7};
	/*it = v.begin();
	cout << v.capacity() << endl;
	v.push_back(10);                            //�����ݣ�v�Ŀռ�����Ǩ�ƣ����itָ��Ŀռ������Ч��
	cout << v.capacity() << endl;
	while (it != v.end())                          //�˴��ᱨ��   ������ʧЧ��
	{
		cout << *it << " ";
		cout << endl;
	}*/
	

	//ͨ��������Ӿ�һ������Ҫ���漰���ݵĲ����磺resize��reserve��insert���ᵼ�µ�����ʧЧ
	//������������¸�it��ֵ����
	it = v.begin();
	cout << v.capacity() << endl;
	v.push_back(10);   //�����ݣ�v�Ŀռ�����Ǩ�ƣ����itָ��Ŀռ������Ч��
	it = v.begin();
	cout << v.capacity() << endl;
	while (it != v.end())                          //�˴��ᱨ��   ������ʧЧ��
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	

	//eraseҲ��ʹ��ʧЧ
	auto pos1 = find(v.begin(), v.end(), 3);
	cout << v.capacity() << endl;
	v.erase(pos1);
	cout << v.capacity() << endl;
	cout << *pos1 << endl;                      //�ᱨ��

	/*//���������
	pos1 = v.erase(pos1);                   //��Ϊerase�᷵����һ���ռ�ĵ�ַ�����Կ�ͨ�����ַ�����ʹ����������ʹ��
	//���ߣ�
	v.erase(pos1++);                         //����ǰ�Ƚ�pos1�����ƣ��ٽ�֮ǰ��ֵ����Ҳ��ʵ��
   */
	



	



	system("pause");
	return 0;
}