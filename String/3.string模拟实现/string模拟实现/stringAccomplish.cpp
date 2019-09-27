#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

//�Զ������Ͳ��ܿ�������ʱ��������Ĭ�Ͽ������캯������Ϊ��ǳ����ֻ�ǽ���ַ���˶Է�ָ����ͬһ��ռ�
//���
namespace String1{
	class string{
	public:
		string(char *s =""){
			if (s == nullptr)
			{
				s = "";
			}
			_str = new char[strlen(s) + 1];
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
			return *this;

		}


		friend ostream& operator<<(ostream &_cout, const string &str);
		
	private:
		char *_str;
	};
	ostream& operator<<(ostream &_cout, const string &str)
	{
		_cout << str._str;                    //_cout����cout
		return _cout;
	}
}
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
		_cout << str._str<<":"<<*str.count;                    //_cout����cout
		return _cout;
	}
}

void Test(const String3::string &str)
{
	cout << str << endl;            //-->2
	String3::string str1("hello");
	String3::string str2(str1);

}

int main()
{
	String3::string str1("hello");
	String3::string str2(str1);
	Test(str1);
	String3::string str3("heihei");
	String3::string str4(str3);
	str4 = str1;
	
	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;
	cout << str4 << endl;


	system("pause");
	return 0;;
}