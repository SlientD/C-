#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

#if 0
//��Ԫ���������Ƕ��������ⲿ����ͨ��������Ԫ��������ֱ�ӷ������˽�г�Ա���������κ��࣬
//          ����Ҫ������ڲ�����������ʱ��Ҫ��friend�ؼ��֡�

//��Ԫ������Ӧ�ã�
//�������ǳ���ȥ����operator<<��Ȼ��������û�취��operator<<���سɳ�Ա��������Ϊcout��
//����������������thisָ������ռ��һ��������λ�á�thisָ��Ĭ���ǵ�һ������Ҳ������������ˡ�����
//ʵ��ʹ����cout��Ҫ�ǵ�һ���βζ��󣬲�������ʹ�á���������Ҫ��operator << ���س�ȫ�ֺ�����������
//���Ļ����ֻᵼ������û�취���ʳ�Ա����ô�������Ҫ��Ԫ�������operator >> ͬ��
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
		
	}

	Date(const Date& d)
		: _year(d._year)
		, _month(d._month)
		, _day(d._day)
	{}
	friend ostream& operator<<(ostream& _cout, const Date& d);
	friend istream& operator>>(istream& _cin, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day ;
	return _cout;
}
istream& operator>>(istream& _cin, Date& d)
{
	_cin >> d._year; _cin >> d._month;_cin >> d._day;
	return _cin;
}

int main()
{
	Date d(1999, 10, 20);

	cout << d << endl<<d<<endl;
	cin >> d;
	cout << d << endl;
	system("pause");
	return 0;
}
#endif
//��Ԫ�����ɷ������˽�г�Ա����������ĳ�Ա����.��thisָ�봫����ǳ�Ա����
//��Ԫ����������const���Ρ���Ϊconst���ε���this
//��Ԫ�����������ඨ����κεط�����������������޶������ơ�����endl
//һ�����������Ƕ�������Ԫ����
//��Ԫ�����ĵ�������ͨ�����ĵ��ú�ԭ����ͬ�����磺�ж��ٸ�ʵ�Σ����ж��ٸ��β��ڽ�



//��Ԫ�ࣺ��Ԫ������г�Ա��������������һ�������Ԫ�����������Է�����һ�����еķǹ��г�Ա��
//ע�⣺
//1.��Ԫ��ϵ�ǵ���ģ������н����ԡ�
//��������Time���Date�࣬��Time��������Date��Ϊ����Ԫ�࣬��ô������Date����ֱ�ӷ���Time
//���˽�г�Ա������������Time���з���Date����˽�еĳ�Ա�������С�
//2.��Ԫ��ϵ���ܴ���
//���B��A����Ԫ��C��B����Ԫ������˵��CʱA����Ԫ��


class Date; // ǰ������
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	void SetTimeOfDate(int hour, int minute, int second)
	{
		// ֱ�ӷ���ʱ����˽�еĳ�Ա����
		_t._hour = hour;
		_t._minute = minute;
		_t._second = second;
	}

private:
	int _year;
	int _month;
	int _day;
	Time _t;
};
class Time
{
	friend class Date; // ����������Ϊʱ�������Ԫ�࣬�����������о�ֱ�ӷ���Time���е�˽�г�Ա����.������Time�в�����Date�е�˽�г�Ա����
public:
	Time()
	{}
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{}

private:
	int _hour;
	int _minute;
	int _second;
};

