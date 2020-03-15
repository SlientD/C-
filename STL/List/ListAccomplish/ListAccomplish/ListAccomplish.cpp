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

	template <class Iterator,class T>
	struct reverse_list_iterator{
		
		typedef reverse_list_iterator<Iterator,T> iterator;
		reverse_list_iterator(Iterator it)
			:_pNode(it)
		{

		}

		T& operator*()          //返回值是元素值
		{
			Iterator tmp = _pNode;
			--tmp;
			return *tmp;
		}
		T* operator->()         //返回值：->返回的是_date的地址
		{
			
		    return &(operator*());      /////////////////!!!!!!!!!!!!!!!!!!
		}
		iterator& operator++()      //返回的是和自身类型相同的元素类型
		{
			--_pNode;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp(*this);    //tmp的_it和this的it指向同一块空间
			--_pNode;
			return tmp;
		}

		iterator& operator--()
		{
			++_pNode;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp(*this);    //tmp的_it和this的it指向同一块空间
			++_pNode
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


		Iterator _pNode;
	};








	template <class T>
	class list{
		typedef ListNode<T> Node;
		typedef list_iterator<T> iterator;
		typedef reverse_list_iterator<iterator, T> reverse_iterator;
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
		~list()
		{
			clear();
			_phead = nullptr;
		}
		iterator begin()const
		{
			return iterator(_phead->_next);
		}
		iterator end()const
		{
			return iterator(_phead);
		}
		reverse_iterator rbegin()const
		{
			return end();
		}
		reverse_iterator rend()const
		{
			return begin();
		}
		int size(){
			int n=0;
			iterator it = begin();
			while (it != end())
			{
				n++;
				it++;
			}
			return n;
		}
		void push_back(const T &value)
		{
			insert(end(), value);
		}
		void pop_back()
		{
			erase(--end());
		}
		void push_front(const T &value)
		{
			insert(begin(), value);
		}
		void pop_front()
		{
			erase(begin());
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

		iterator erase(iterator pos)
		{
			if (pos._pNode == _phead)
				return end();
			
			Node *cur = pos._pNode;
			++pos;
			cur->_pre->_next = pos._pNode;
			pos._pNode->_pre = cur->_pre;
			delete cur;
			return pos;
		}
		void clear()
		{
			iterator it = begin();
			while (begin() != end())
			{
				it=erase(it);
			}
		}
		
		list<T> operator=(const list<T> &L)
		{
			if (L.begin() != L.end())
			{
				clear();
			}
			auto it = L.begin();
			while (it != L.end())
			{
				push_back(*it);
				++it;
			}
		}
		void swap(list<T>& L)
		{
			std::swap(_phead, L._phead);
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
	cout << L4.size() << endl;
	auto it1 = L4.begin();
	while (it1 != L4.end())
	{
		cout << *it1 << " ";
		it1++;
	}
	cout << endl;

	auto it2 = L4.rbegin();
	while (it2 != L4.rend())
	{
		cout << *it2 << " ";
		it2++;
	}
	cout << endl;

	auto it3 = L4.end();
	while (it3 != L4.begin())
	{
		--it3;
		cout << *it3 << " ";
		
	}
	cout << endl;

	auto it4 = L4.rend();
	while (it4 != L4.rbegin())
	{
		--it4;
		cout << *it4 << " ";

	}
	cout << endl;
	L4.erase(L4.begin());
	it4 = L4.rend();
	while (it4 != L4.rbegin())
	{
		--it4;
		cout << *it4 << " ";

	}
	cout << endl;
	L4.push_back(10);
	L4.push_front(10);
	it4 = L4.rend();
	while (it4 != L4.rbegin())
	{
		--it4;
		cout << *it4 << " ";

	}
	cout << endl;
	L4.pop_back();
	L4.pop_front();
	it4 = L4.rend();
	while (it4 != L4.rbegin())
	{
		--it4;
		cout << *it4 << " ";

	}
	cout << endl;
	L4.swap(L2);
	it4 = L4.rend();
	while (it4 != L4.rbegin())
	{
		--it4;
		cout << *it4 << " ";

	}
	cout << endl;

	L4.clear();
	it4 = L4.rend();
	while (it4 != L4.rbegin())
	{
		--it4;
		cout << *it4 << " ";

	}
	cout << endl;
}


int main()
{
	Test1();





	system("pause");
	return 0;
}