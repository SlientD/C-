#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
//�ڲ��ࣺ���һ���ඨ������һ������ڲ�������ڲ���ͽ����ڲ��ࡣע���ʱ����ڲ�����һ��������
//�࣬���������ⲿ�࣬������ͨ���ⲿ��Ķ���ȥ�����ڲ��ࡣ�ⲿ����ڲ���û���κ���Խ�ķ���Ȩ�ޡ�
//ע�⣺�ڲ�������ⲿ�����Ԫ�ࡣע����Ԫ��Ķ��壬�ڲ������ͨ���ⲿ��Ķ�������������ⲿ����
//�����г�Ա�������ⲿ�಻���ڲ������Ԫ��
//���ԣ�1. �ڲ�����Զ������ⲿ���public��protected��private���ǿ��Եġ�
//      2. ע���ڲ������ֱ�ӷ����ⲿ���е�static��ö�ٳ�Ա������Ҫ�ⲿ��Ķ��� / ���������ǲ���ֱ�����ⲿ���˽�б���
//      3. sizeof(�ⲿ��) = �ⲿ�࣬���ڲ���û���κι�ϵ��

class Date{

public:
	class Time{
	public:
		void printfD()
		{
			cout << total;
			//cout << _year;   �ᱨ��
		}


	private:
		int _hour;
		int _minute;
		int _second;

	};
private:
	int _year;
	int _month;
	int _day;
	static int total;
	
};
int Date::total = 1;
int main(){
	Date d;
	Date::Time x;
	x.printfD();
	cout << sizeof(d) << endl;    //--��12   û�а����ڲ���ĳ�Ա����
	system("pause");
	return 0;
}