#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
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
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
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
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
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
			:_start(nullptr)
			, _finish (nullptr)
			,_endOfStorage(nullptr)
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
			/*if (_finish == _endOfStorage)
			{
				int n = (capacity() == 0 ? 1 : (int)capacity()*1.5);
				reserve(n);

			}

			*_finish = value;
			_finish++;*/
			insert(end(), value);
		}
		void pop_back()
		{
			erase(end()-1);
		}

		iterator insert(iterator pos, const T &value)
		{
			assert(pos <= _finish);
			assert(pos >=_start);
			int n = pos - _start;
			if (_finish == _endOfStorage)
			{
				reserve(capacity() + 1);
			}
			pos = _start + n;
			auto it = _finish;
			while (it != pos)
			{
				*it = *(it-1);
				it--;
			}
			*pos = value;
			_finish++;
			return pos;
		}

		iterator erase(iterator pos)
		{
			auto it = pos+1;
			while (it != end())
			{
				*(it-1) = *it;
				it++;
			}
			_finish--;
			return pos;
		}
		//using namespace std;
		void _swap(vector<T> &v)     //?????????????????????????????????????????
		{
			/*iterator tmp;
			tmp = _start;
			_start = v._start;
			_finish = tmp;*/

			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endOfStorage, v._endOfStorage);

		}


		vector<T>& operator=(vector<T> v)
		{
			_swap(v);
			return *this;
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

		friend ostream& operator<<(const ostream &_cout, const vector<T> &v);
		friend iterator find(iterator begin, iterator end, const T &value);
	private:
		T *_start;
		T *_finish;
		T *_endOfStorage;

	};
	
	

	}
	template <class T>
	T* find(T* begin, T* end, const T &value)
	{
		auto it = begin;
		while (it != end)
		{
			if (*it == value)
			{
				return it;
			}
			it++;
		}
		return nullptr;
	}



	/*template <class T>
	ostream& operator<<(ostream _cout, const MyVector::vector<int> &v)
	{
		for (auto &e : v)
		{
			_cout << e;
		}
	}*/



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
	cout << "pop_back test" << endl;
	v4.pop_back();
	v4.Print();
	
	v3.insert(find(v3.begin(), v3.end(), 2), 7);
	v3.Print();
	v3.erase(find(v3.begin(), v3.end(), 7));
	v3.Print();
	v3._swap(v2);
	v3.Print();
	v3 = v2;
	v3.Print();


	
	//cout << v1 << endl;
}

int main()
{
	
	
	Test1();
	


	system("pause");
	return 0;

}