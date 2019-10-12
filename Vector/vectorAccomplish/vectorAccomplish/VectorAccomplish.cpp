#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

namespace MyVector{
	template <class T>
	class vector{
		typedef T* iterator;
	public:
		//构造析构
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
		}
		vector(int n, const T &value = 0)
		{
			_start = new T[n+1];
			int i = n;
			while (i--)
			{
				_start[i] = value;
			}
			_start[n] = '\0';
			_finish = _start + n;
			_endOfStorage = _finish;
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)    
		{
			int n=0;
			auto tmp = first;
			while (tmp != last)                
			{
				n++;
				tmp++;
			}
			_start = new T[n + 1];
			_finish = _start + n;
			_endOfStorage = _finish;
			
			last--;
			while (n--)
			{
				_start[n] = *last;
				last--;
			}
			
			
		}
		vector(const vector<T>& v)
		{
			reserve(v.capacity());
			//memcpy(_start, v._start,v.size());
			for (int i = 0; i < v.size(); i++)
			{
				_start[i] = v._start[i];
			}
 			_finish = _start + v.size();
			_endOfStorage = _start + v.capacity();
		}
		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endOfStorage = nullptr;
		}
		//迭代器
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		//容量操作
		int size()const
		{
		
			return _finish - _start;
		}
		int capacity()const
		{
			return  _endOfStorage - _start;
		}
		bool empty()
		{
			if (_start == nullptr)
			{
				return _start == _finish;
			}
			else
				return false;
		}
		void reserve(int newCapacity)
		{
			int oldCapacity = capacity();
			int n = size();
			T *tmp = new T[newCapacity + 1];
			if (newCapacity > oldCapacity)
			{
				for (int i = 0; i < n; i++)
				{
					tmp[i] = _start[i];
				}
				if (_start == nullptr)
				{
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + n;
				_endOfStorage = _start + newCapacity;
			}

		}
		void resize(int newSize, int value = T())
		{

			if (newSize > size())
			{
				if (newSize > capacity())
				{
					reserve(newSize);
				}
				for (int i = size(); i < newSize; i++)
				{
					_start[i] = value;
				}
			}
			_finish = _start + newsize;
		}
		//元素访问

		//元素修改
		void push_pack(T value)
		{
			if (_finish == _endOfStorage)
			{
				int n = (capacity() == 0 ? 1 : (int)capacity()*1.5);
				reserve(n);

			}

			*_finish = value;
			_finish++;
		}
		void pop_back()
		{
			if (_start == _finish)
			{
				return;
			}
			_finish--;
		}
		void Print()
		{
			iterator e = begin();
			while (e!=end())
			{
				cout << *e << ' ';
				e++;
			}
			cout << endl;
			cout << "size(): " << size() << endl;
			cout << "capacity(): " << capacity() << endl;
		}

		friend ostream operator<<(ostream _cout, const vector<T> &v);
	private:
		T *_start;
		T *_finish;
		T *_endOfStorage;

	};
	template <class T>
	ostream operator<<(ostream _cout, const vector<T> &v)
	{
		for (auto &e : v)
		{
			_cout << e;
		}
	}



}



void Test1()
{
	MyVector::vector<int> v1;
	MyVector::vector<int> v2(2);
	int a[] = { 1, 2, 3 };
	MyVector::vector<int> v3(a,a+sizeof(a)/sizeof(a[0]));
	MyVector::vector<int> v4(v3);
	v1.size();
	v4.Print();
	v4.push_pack(2);
	v4.Print();
	v4.pop_back();
	v4.Print();
}

int main()
{
	Test1();



	system("pause");
	return 0;

}