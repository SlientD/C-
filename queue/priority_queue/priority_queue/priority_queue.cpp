#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <functional>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <deque>
using namespace std;
/*
template < class T, class Container = vector<T>,
class Compare = less<typename Container::value_type> > class priority_queue;
T: 代表优先级队列中存储元素类型
Container: 优先级队列中元素的底层存储结构，默认vector
Compare: 优先级中元素的比较规则：默认按照Less(小于)--->大堆
*/


class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
	/*bool operator<(const Date* d)const
	{
		return (_year < d->_year) ||
			(_year == d->_year && _month < d->_month) ||
			(_year == d->_year && _month == d->_month && _day < d->_day);
	}
	bool operator>(const Date* d)const
	{
		return (_year > d->_year) ||
			(_year == d->_year && _month > d->_month) ||
			(_year == d->_year && _month == d->_month && _day > d->_day);
	}*/
	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
	
private:
	int _year;
	int _month;
	int _day;
};
class  Less
{
public:
	bool operator()(const Date* pLeft, const Date* pRight){
		return *pLeft < *pRight;

	}
};

void Test1(){
	vector<int> v{ 2, 5, 3, 8, 9, 0, 1 };
	priority_queue<int> q1(v.begin(), v.end());     //默认以大根堆创建
	priority_queue<int, vector<int>, greater<int>> q2(v.begin(), v.end());


	priority_queue<Date*, vector<Date*>, Less> q3;    //最后一个要传参，所以第二个参数也要传

	Date d1(2019, 10, 21);
	Date d2(2019, 10, 20);
	Date d3(2019, 10, 22);


	q3.push(&d1);
	q3.push(&d2);
	q3.push(&d3);

}


namespace MyStack{
	template<class T,class Container=deque<T>>
	class stack{
	public:
		stack(){

		}
		void push(const T &value){
			q.push_back(value);
		}
		void pop(){
			q.pop_back();
		}
		T& top(){
			return q.back();
		}
		const T& top() const
		{
			return q.back();
		}
		size_t size(){
			return q.size();
		}
		bool empty(){
			return q.empty();
		}
	private:
		Container  q;
	};
}

void Test2()
{
	MyStack::stack<int,list<int>> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.pop();
	cout << s1.size() << endl;
	cout << s1.empty() << endl;


}


namespace MyQueue{
	template<class T, class Container = deque<T>>
	class queue{
	public:
		queue(){

		}
		void push(const T &value){
			q.push_back(value);
		}
		void pop(){
			q.pop_front();
		}

		T& front(){
			return q.front();
		}
		const T& front() const
		{
			return q.front();
		}
		T& back() 
		{
			return q.back();
		}
		const T& back() const
		{
			return q.back();
		}

		size_t size(){
			return q.size();
		}

		bool empty(){
			return q.empty();
		}
	private:
		Container  q;
	};
}

void Test3()
{
	MyQueue::queue<int,list<int>> q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.pop();
	
	cout << q1.size() << endl;
	cout << q1.empty() << endl;
}

namespace MyPriorityqueue{
	template <class T,class Contain=deque<T>,class Compare=less<T>>
	class priority_queue{
	public:
		
		priority_queue()
			:_con()
		{

		}
		template <class Iterator>
		priority_queue(Iterator start, Iterator end)
			:_con(start, end)
		{
			
			for (int i =( _con.size()-2)/2; i >=0; i--)
			{
				AdjustDown(i);
			}
		}
		void size(){
			return _con.size();
		}
		bool empty(){
			return _con.empty();
		}
		void push(const T& value){
			_con.push_back(value);
			AdjustUP(_con.size() - 1);
			

		}
		void pop(){
			swap(_con.front(), _con.back());
			_con.pop_back();
			AdjustDown(0);

		}

	private:
		void AdjustDown(int parent){
			int child = parent * 2 + 1;
			while (child<_con.size())
			{
				if (child+1<_con.size()&&_comp(_con[child], _con[child + 1]))
				{
					child += 1;
				}
				if (_comp(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					return;
				
			}
		}
		void AdjustUP(int child)
		{
			int parent = (child - 1) / 2;
			while (child>0){
				if (_comp(_con[parent],_con[child]))
				{
					swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;			
				}
				else{
					return;
				}
			}
		}
	private:
		Contain _con;
		Compare _comp;
	};

}


void Test4(){
	deque<int> dq{ 1, 2, 3 ,5,6,2};
	MyPriorityqueue::priority_queue<int,deque<int>,greater<int>> p1(dq.begin(),dq.end());
	p1.pop();
	p1.push(0);



}






int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();

	



	



	system("pause");
	return 0;
}