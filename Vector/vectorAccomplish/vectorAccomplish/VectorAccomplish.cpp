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
		vector(int n, const T& value = 0)
		{
			_start = new T[n + 1];
			while (n--)
			{
				_start[n] = value;
			}
			_finish = _start + n;
			_endOfStorage = _finish;
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)    
		{
			int n=0;
			auto tmp = first;
			while (tmp != last)                //
			{
				n++;
				tmp++;
			}
			_start = new T[n + 1];
			while (first!=last)
			{
				_start[n] = *first;
				first++;
			}
			_finish = _start + n;
			_endOfStorage = _finish;
		}
		vector(const T &v)
		{
			int n = v.capacity();
			_start = new T[n+1];
			memcpy(_start, v._start);
			_finish = _start + v.size();
			_endOfStorage = _start + n;
		}
		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endOfStorage = nullptr;
		}
		//容量操作
		//元素访问
		//元素修改
		//迭代器


	private:
		T *_start;
		T *_finish;
		T *_endOfStorage;

	};




}
int main()
{
	MyVector::vector<int> v(2,0);
	

}