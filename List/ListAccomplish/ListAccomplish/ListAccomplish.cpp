#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;

namespace MyList{
	template <class T>
	struct ListNode{
		ListNode(const T &value=T())
		:_pre(nullptr)
		, _next(nullptr)
		, _date(value)
		{

		}
	
		ListNode<T> *_pre;
		ListNode<T> *_next;
		     T    _date;


	};
	template <class T>
	struct list_iterator{
		typedef ListNode<T> Node;
		typedef list_iterator<T> iterator;
		list_iterator(Node* ptr=nullptr)
			:_pNode(ptr)
		{

		}

		T& operator*()          //返回值是元素值
		{
			return _pNode->_date;
		}
		T* operator->()         //返回值：->返回的是_date的地址
		{
			return &(_pNode->_date);
		}
		iterator& operator++()      //返回的是和自身类型相同的元素类型
		{
			_pNode = _pNode->_next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp(*this);    //tmp的_it和this的it指向同一块空间
			_pNode = _pNode->_next;
			return tmp;
		}
		iterator& operator--()      
		{
			_pNode = _pNode->_pre;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp(*this);    //tmp的_it和this的it指向同一块空间
			_pNode = _pNode->_pre;
			return tmp;
		}
		bool operator==(const iterator &it)
		{
			return _pNode == it._pNode;
		}
		bool operator!=(const iterator &it)
		{
			return _pNode != it._pNode;
		}

		iterator& operator=(const iterator &it)
		{
			_pNode = it._pNode;
			return *this;
		}
		

		Node *_pNode;
	};
	template <class T>
	class list{
		typedef ListNode<T> Node;
		typedef list_iterator<T> iterator;
	public:
		list()
		{
			CreateNode();
		}
		
		list(int num, const T &val=T()){
			CreateNode();
			while (num--)
			{
				push_back(val);
			}
		}

		template <class Iterator>
		list(Iterator begin, Iterator end)
		{
			CreateNode();
			while (begin != end)
			{
				push_back(*begin);
				++begin;
			}
		}
		list(const list &L)
		{
			CreateNode();
			iterator it =L.begin();
			while (it != L.end())
			{
				push_back(*it);
				it++;
			}	
		}
		iterator begin()const
		{
			return iterator(_phead->_next);
		}
		iterator end()const
		{
			return iterator(_phead);
		}
		

		void push_back(const T &value)
		{
			insert(end(), value);
		}

		iterator insert(iterator pos, const T &value)
		{
			Node* newNode = new Node(value);
			Node* pcur = pos._pNode;
			newNode->_next = pcur;
			newNode->_pre = pcur->_pre;
			pcur->_pre->_next = newNode;
			pcur->_pre = newNode;

			return iterator(newNode);
		}

		

	private:
		void CreateNode()
		{
			_phead = new Node;
			_phead->_pre= _phead;
			_phead->_next = _phead;
		}
	private:
		
		Node *_phead;

	};

}

void Test1()
{
	MyList::list<int> L1;
	MyList::list<int> L2(5, 2);
	vector<int> v{ 1, 2, 3, 4, 5, 6 };
	MyList::list<int> L3(v.begin(), v.end());
	MyList::list<int> L4(L3);
	MyList::list_iterator<int> it = L4.begin();
	while (it != L4.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;


}


int main()
{
	Test1();





	system("pause");
	return 0;
}