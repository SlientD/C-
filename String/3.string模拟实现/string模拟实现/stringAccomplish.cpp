#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

#if 0
//ǳ����:
//˼��Ϊʲô֮ǰǳ��������ִ�����Ϊǳ����ֻ�ǽ���ַ���˶Է�ָ����ͬһ��ռ䣬�ڵ�����������ʱ��ͬһ��ռ����ֱ�����ͷŵ����������ᱨ��
//���ǲ���������������޷�����һ����Դ�ռ䣬ֻҪ��֤����Դ�ռ�ֻ���ͷ�һ�μ��ɡ�
//�����һ�������ֳ����ˣ�Ӧ����һ���������Դ�ռ�Ķ����ͷ��أ�   ----Ӧ�����һ��ʹ�ø���Դ�ռ�Ķ������ͷŸÿռ�
//��ô��һ������Ҫȥ�ͷŸÿռ�ʱ�����֪�����Լ��ǲ������һ���øÿռ�Ķ����أ�     --����������˼�����
//���������ã���¼ʹ�øÿ�ռ�Ķ����м�������ÿ�ζഴ��һ������ʱ����������һ���ͷ�һ����������һ

//��ô������Ӧ����ʲô���͵��أ�
// 1.����������int��ĳ�Ա����
//���� -----ԭ����ͨ�����γ�Ա������ÿ�������ж���һ�ݣ�һ���������޸ĸü���ʱ�򣬲���Ӱ����������

//// ���������ɾ�̬���͵ĳ�Ա����---->����
// ԭ�򣺾�̬���ͳ�Ա���������ж�����,������û�й�����Դ��count���ǹ���ġ����Ǿ��ܲ�������Դ��Ҳ����ͬһ��count�ռ����������Կ϶�˵��ͨ
//      ���������Ӧ������Դ��������һ�£����ǹ���ͬһ��ռ����Դ�Ź���ͬһ��������
namespace String2
{
	class string
	{
	public:
		string(char* str = "")
		{
			if (nullptr == str)
				str = "";

			// ����ռ�
			_str = new char[strlen(str) + 1];
			count = 1;
			// ���str�е��ַ�
			strcpy(_str, str);
		}

		string(const string& s)
			: _str(s._str)
		{
			++count;
		}

		// s2 = s1;
		string& operator=(const string& str)
		{
			if (this == &str)
			{
				return *this;
			}
			if (_str&&--count == 0)     //���ǻ�δ��ʼ���ģ�Ȼ�������һ���øÿռ�Ķ���
			{
				delete[] _str;
				_str = nullptr;
			}
			_str = str._str;

			++count;

			return *this;
		}
		friend	ostream& operator<<(ostream &_cout, const string &str);
		~string()
		{
			if (_str && 0 == --count)
			{
				delete[] _str;
				_str = nullptr;
			}
		}
	private:
		char* _str;
		static int count;
	};

	int string::count = 0;
	ostream& operator<<(ostream &_cout, const string &str)
	{
		_cout << str._str << ":" << str.count;                    //_cout����cout
		return _cout;
	}
}




//ͨ��������������count����Ϊ��_str������ͬ���Ϳ������㹲��ͬһ��ռ����Դ����ͬһ�������������ʹ��int *�����洢������

namespace String3{
	class string{

	public:
		string(char *s = "")
			:count(new int(1))
		{
			if (s == nullptr)
			{
				s = "";
			}
			_str = new char[strlen(s) + 1];
			strcpy(_str, s);
		}
		string(const string &s){
			_str = s._str;
			count = s.count;
			(*count)++;
		}
		string& operator=(const string &str)
		{
			if (this == &str)
			{
				return *this;
			}
			if (_str&&--(*count) == 0)     // �õ�ǰ�������������Դ���뿪,�ֿ�ʱҪ�ж����ǲ������һ��������ռ����Դ
			{
				delete[] _str;
				_str = nullptr;

				delete count;
				count = nullptr;
			}
			_str = str._str;
			count = str.count;          //��ָ�򣬸ļ�����
			++(*count);
			return *this;


		}

		~string()
		{
			if (_str&&--(*count) == 0)     //���ǻ�δ��ʼ���ģ�Ȼ�������һ���øÿռ�Ķ���
			{
				delete[] _str;
				_str = nullptr;

				delete count;
				count = nullptr;
			}
		}
		friend	ostream& operator<<(ostream &_cout, const string &str);






	private:
		char *_str;
		int *count;
	};
	ostream& operator<<(ostream &_cout, const string &str)
	{
		_cout << str._str << ":" << *str.count;                    //_cout����cout
		return _cout;
	}
}

#endif
//�Զ������Ͳ��ܿ�������ʱ��������Ĭ�Ͽ������캯������Ϊ��ǳ����ֻ�ǽ���ַ���˶Է�ָ����ͬһ��ռ�
//���
namespace String1{
	class string{
	public:
		typedef char* iterator;
		string(char *s ="")     //�������޲ι���
		{
			if (s == nullptr)
			{
				s = "";
			}
			_str = new char[strlen(s) + 1];
			resize(strlen(s));
			strcpy(_str, s);
			
		}
		/*string(const string &s)
		{
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}*/
		//�ִ���д��String��
		string(const string &s)
			:_str(nullptr)               //ΪʲôҪ��ʼ����Ҫ��֤�������stmp����ָ��һ����Ч�ռ䣬stmp������ʱ�򲻻ᱨ��
		{
		string stmp(s._str);            //stmp�������������֮����Լ��������������ͷ�
		swap(_str,stmp._str);
		_size = s._size;
		_capacity = s._capacity;
		}
		string(size_t n, char ch)
		{
			_str = new char[n];
			memset(_str, ch, n);
			resize(n);
			
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}

		/*string& operator=(const string &s)
		{
			if (this == &s)
			{
				return *this;
			}
			delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
			return *this;

		}*/
		string& operator=(string s)
		{
			swap(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
			return *this;

		}


		friend ostream& operator<<(ostream &_cout, const string &str);

		

		//��������
		size_t size()
		{
			return _size;
		}
		size_t capacity()
		{
			return _capacity;
		}
		bool isEmpty()
		{
			if (_size <= 0)
			{
				return true;
			}
			else{
				return false;
			}
			
		}
		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}
		void reserve(size_t newcap)
		{
			while (newcap>_capacity)
			{
				_capacity = size_t(1.5*_capacity);
			}

			char *str = new char[_capacity+1];       //capacity,size�������ַ����е�\0,����ʵ�ʵĿռ�Ҫ��1
			strcpy(str, _str);
			swap(str,_str);
		}
		void resize(size_t newsize,char ch='\0')
		{
			if (newsize>_size){
				if (newsize > _capacity)
				{
					reserve(newsize);
				}
				memset(_str + _size, ch, newsize - _size);
					
			}
			
			_size = newsize;
			_str[newsize] = '\0';	
		}
		//���ʡ�����
		const char operator[](size_t index)const
		{
			assert(index < _size&&index >= 0);
			return _str[index];
		}
		char *c_str()
		{

			return _str;
		}
		//��������
		iterator begin(){
			return _str;
		}
		iterator end(){
			return _str + _size;
		}
		//��������Χ��[begin,end��   ����ҿ�

		//�޸Ĳ���
		void push_back(char ch)
		{
			
			resize(_size+1);
			_str[_size-1] = ch;
		}
		void operator+=(char ch)
		{
			push_back(ch);
		}
		void operator+=(const char *str)
		{
			int len = strlen(str);
			int i = 0;
			while (i < len)
			{
				push_back(*(str + i));
				i++;
			}

		}
		void append(int num, char ch)
		{
			resize(_size+num, ch);
			
		}
		void append(const string &s)
		{
			append(s._str);
		}
		void append(const char *str)
		{
			*this += str;
		}
		
		//����
		size_t find(char ch,size_t pos = 0)
		{
			int i = 0;
			while (*(_str + pos + i) != '\0')
			{
				if (*(_str + pos + i) == ch)
				{
					return pos + i;
				}
				i++;
			}
			return npos;

		}
		size_t rfind(char ch, size_t pos = npos)        //Ϊʲô���β��б���Ա���������ֵ��
		{
			int index;
			if (pos != npos)
			{
				index = pos;
			}
			else{
				
				index = _size;
			}
			while (index>=0)
			{
				if (_str[index] == ch)
				{
					return index;
				}
				index--;
			}
			return npos;
		}
		char * substr(size_t pos = 0,size_t n = npos) const
		{
			if (n == npos)
			{
				n = _size - pos;
			}
			char *str = new char[n+1];
			int i=0;
			while (i<n)
			{
				*(str + i) = *(_str + pos + i);
				i++;
			}
			str[i] = '\0';
			return str;
		}
		
		size_t erase(size_t pos=0, size_t len=npos)
		{
			if (len == npos)
			{
				len = _size - pos;
			}
			int i = 0;
			int num=len;
			while (num--&&*(_str + pos + len)!='\0')
			{
				*(_str + pos) = *(_str + pos + len);
				pos++;
			}
			_size -= len;
			_str[_size] = '\0';
			
			return  pos;
		}



	private:
		char *_str;
		size_t _capacity=15;
		size_t _size=0;
		static int npos;
	};
	int string::npos = -1;
	ostream& operator<<(ostream &_cout, const string &str)
	{
		_cout << str._str;                    //_cout����cout
		return _cout;
	}
}


void Test(const String1::string &str)
{
	cout << str << endl;            //-->2
	String1::string str1("hello");
	String1::string str2(str1);

}

int main()
{
	String1::string str1("hello");
	String1::string str2(str1);
	Test(str1);
	String1::string str3("heihei");
	String1::string str4(str3);
	str4 = str1;
	
	cout << str1 << endl;
	cout << "str1:" << str1.size() <<" "<< str1.capacity() << endl;
	cout << str1.isEmpty() << endl;
	str1.resize(10,'!');
	cout << str1 << endl;
	cout << "str1:" << str1.size() << " " << str1.capacity() << endl;
	str1.resize(20,'?');
	cout << str1 << endl;
	cout << "str1:" << str1.size() << " " << str1.capacity() << endl;
	str1.clear();
	cout << str1 << endl;
	cout << "str1:" << str1.size() << " " << str1.capacity() << endl;
	cout << str2 << endl;
	cout << str3 << endl;
	cout << str3.find('i') << endl;
	cout << str3.find('i',3) << endl;
	cout << str3.rfind('i') << endl;
	cout << str3.rfind('i',3) << endl;
	cout << str3.substr(1,3) << endl;
	cout << str4 << endl;
	str4.erase(2);
	cout << str4 << endl;


	system("pause");
	return 0;;
}