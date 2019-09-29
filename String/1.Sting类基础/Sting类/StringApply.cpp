#define _CRT_SECURE_NO_WARNINGS 1
//String类是表示字符串的类。
//在使用string类时，必须包含#include头文件以及using namespace std;
//sting在底层实际上是basic_string模板类的别名。是这样定义的：typedef  basic_string<char, char_traits, allocator>  string;

#include <iostream>
#include <string>
using namespace std;

//Q1:sting 类对象常用构造：
void Test1()
{
	cout << "Test1:" << endl;

	string s1;       //构造一个空的string对象即空字符串，调用构造函数sting()
	string s2("Hello string");//用c格式字符串构造string类对象，调用构造函数 sting(const char *s)
	string s3(3, '!');       //构造string类对象，包含3个！字符，调用构造函数string(size_t n, char c)
	string s4(s2);           //拷贝构造函数   ，调用构造函数string(const string&s)
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;     
	//注：sting类对象支持直接使用cin或者cout进行输入和输出
	cin >> s1;
	cout << s1 << endl;
}

//Q2:sting 类对象的容量操作：
void Test2()
{
	cout << "Test2:" << endl;

	string s1("hello");
	cout << "hello" << endl;


	
	cout << s1.size() << endl;    //返回字符串有效字符长度
	cout << s1.length() << endl;    //返回字符串有效字符长度
	cout << s1.capacity() << endl;    //返回s1所占空间总大小

	s1.clear();                    //将s中的空间清空，只是让size等于0，但底层空间不会变，即capacity大小不变
	cout << s1.size() << endl;    
	cout << s1.capacity() << endl;    
	

	cout << "empty:" << endl;   //判空
	if (s1.empty())            //空返回true  不空返回false      
	{
		cout << "s1 is Null" << endl;
	}
	else{
		cout << "si is exist" << endl;
	}
	cout << "resize:" << endl;   //将有效字符的个数该成n个，多出的空间用字符c填充
	s1.resize(5, '!');        //将s1中有效字符个数增加到5个（即让size等于5），多出位置补字符！
	cout << s1 << endl;         //hello没了是因为上面clear了
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.resize(10, 'a');        //将s1中有效字符个数增加到10个（即让size等于10），多出位置补字符a
	cout << s1 << endl;        //!!!!!!!!!!aaaaa
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.resize(15);        //将s1中有效字符个数增加到15个（即让size等于15），无参时，多出位置补缺省值\0
	cout << s1 << endl;       //\0打印不出来，但是可以看监视，size也变成了15
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.resize(5);
	cout << s1 << endl;           //输出5个！
	cout << s1.size() << endl;    //变5了
	cout << s1.capacity() << endl;


	//当resize增大，达到大于容量时resize会自动扩容，扩容最后的大小和reverse扩容相同，见下面reserve注意
	s1.resize(20,'h');
	cout << s1 << endl;           
	cout << s1.size() << endl;    //变20了
	cout << s1.capacity() << endl;  //扩容为31

	s1.resize(15, 'h');
	cout << s1 << endl;
	cout << s1.size() << endl;    //变2了
	cout << s1.capacity() << endl;  //容量不变


	cout << "reverse:" << endl;   //为字符串预留空间,请求改变容量，但不会改变有效空间大小

	s1.reserve(20);
	cout << s1 << endl;
	cout << s1.size() << endl;           //不变
	cout << s1.capacity() << endl;       //输出31   
	//扩容注意事项：
	//为什么输出31呢？因为扩容是成倍增长的，不是reserve多少最后的capacity就是多少。在vs中capacity的值可取：15 31 47 70 105差不多是1.5倍
	//而且，若reserve的值比原来的小，s1的容量也不会变，原来capacity是几还是几，当reserve的值小到小于等于15且有效字符也小于reserve的值时，capacity的值会变成15
	
	s1.reserve(16);
	cout << s1 << endl;
	cout << s1.size() << endl;           //不变
	cout << s1.capacity() << endl;       //不变 ，reserve的值不小于15

	s1.reserve(7);
	cout << s1.size() << endl;     //会变
	cout << s1.capacity() << endl;//满足条件

	s1.resize(7, '8');

	s1.reserve(6);                  //capacity的值也不会变，有效字符个数为7，不小于reserve的值
	cout << s1 << endl;
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.clear();
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;
}
//Q2.1 reserve应用： 利用reserve提高插入数据的效率，避免增容带来的开销
void Test21(){
	string s(1,'x');
	int i = 200;
	int cap=s.capacity();
	cout << "making s growing:" << endl;

	while (i--){

		if (s.capacity() != cap){
			cout << s.capacity() << endl;
			cap = s.capacity();
		}
		s += 'x';
	}

	string s1(1, 'x');
	int j = 0;
	int cap1 = s.capacity();
	s1.reserve(200);                       //已知大概最少有多大，因而提前扩容，这样就不用每次都扩容了
	cout << "making s growing:" << endl;

	while (j--){

		if (s1.capacity() != cap1){
			cout << s1.capacity() << endl;
			cap1 = s1.capacity();
		}
		s1 += 'x';
	}



}




//Q3 string类的访问及遍历操作

void Test3()
{
	//operator[] 访问，返回pos位置的字符，const string类对象调用
    //s.at()  也可访问，用法同[]，但在越界时报错不一样
	string s("hello");
	cout << s[0] << endl;
	s[0] = 'H';
	// 如果越界---assert触发
	//cout << s[10] << endl;

	cout << s.at(2) << endl;
	s.at(2) = 'L';

	// 如果越界---抛出out_of_range异常
	//cout << s.at(10) << endl;


	//迭代器：
	//1>
	string::iterator it = s.begin();      //前面的类型可用 auto 识别    ；s.begin()返回字符串首元素地址，s.end返回最后一个元素地址  
	while (it != s.end()){
		cout << *it << endl;
		it++;
	}

	
	string::reverse_iterator rit = s.rbegin();    //从后往前读
	while (rit != s.rend())
	{
		cout << *rit << endl;
		rit++;
	}

	//2>
	for (auto t : s){
		cout << t << endl;
	}

	//3>
	for (size_t i=0; i < s.size(); i++)
	{
		cout << s[i] << endl;
	}
}

//Q4:string类对象的修改操作
void Test4()
{
	string s;

	s.push_back('h');     //push_back: 在字符串后尾插字符c
	
	//append 在字符串后追加一个字符串
	//s.append('e');      //不可以加单个字符
	s.append("ello");     //可在后面加字符串
	s.append(3, '!');     //加若干个单个字符
	s.append(s);          //加一个字符串
	s.append("中国");
	cout << s << endl;

	//operator+= 在字符串后追加字符串str
	s += "chinese";
	s += '!';
	cout << s << endl;

	cout << s.c_str() << endl;     //c_str返回C格式字符串

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	//find + npos(可省，默认从开始找) 从字符串pos位置开始往后找字符c/字符串s，返回该字符在字符串/s首元素在字符串在中的位置(下标)
	cout << s.find('[') << endl;
	cout << s.find('h', 3) << endl;
	cout << s.find("hello") << endl;
	cout << s.find("hello",2) << endl;

	//rfind+npos(可省，默认从末尾开始找) 从字符串pos位置开始往前找字符c，返回该字符在字符串中的位置
	cout << s.rfind('h') << endl;
	cout << s.rfind('h', 20) << endl;

	//substr(pos,n) 在str中从pos位置开始，截取n个字符，n可省，默认截到最后，然后将其返回,
	string s1 = s.substr(s.find('h'),2);
	cout << s1 << endl;

	//应用1：获取file的后缀
	string s3("string.cpp.cpp");
	string s4(s3.substr(s3.rfind('.') + 1));
	cout << s4 << endl;
	//应用2： 取出url中的域名
	string url("http://www.cplusplus.com/reference/string/string/find/");
	size_t start = url.find("://") + 3;
	if (start == string::npos)
	{
		cout << "no url" << endl;
		return;
	}
	size_t end = url.find('/', start);
	string u = url.substr(start, end - start);
	cout << u << endl;

	//删除：erase(pos,n),从pos位删除n个字符。n不写删除pos后所有的字符
	cout << s << endl;
	s.erase(0,2);
	cout << s << endl;
	s.erase(20);
	cout << s << endl;
}



int main()
{

	Test4();

	system("pause");
	return 0;
}