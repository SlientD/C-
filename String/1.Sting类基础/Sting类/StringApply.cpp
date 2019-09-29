#define _CRT_SECURE_NO_WARNINGS 1
//String���Ǳ�ʾ�ַ������ࡣ
//��ʹ��string��ʱ���������#includeͷ�ļ��Լ�using namespace std;
//sting�ڵײ�ʵ������basic_stringģ����ı���������������ģ�typedef  basic_string<char, char_traits, allocator>  string;

#include <iostream>
#include <string>
using namespace std;

//Q1:sting ������ù��죺
void Test1()
{
	cout << "Test1:" << endl;

	string s1;       //����һ���յ�string���󼴿��ַ��������ù��캯��sting()
	string s2("Hello string");//��c��ʽ�ַ�������string����󣬵��ù��캯�� sting(const char *s)
	string s3(3, '!');       //����string����󣬰���3�����ַ������ù��캯��string(size_t n, char c)
	string s4(s2);           //�������캯��   �����ù��캯��string(const string&s)
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;     
	//ע��sting�����֧��ֱ��ʹ��cin����cout������������
	cin >> s1;
	cout << s1 << endl;
}

//Q2:sting ����������������
void Test2()
{
	cout << "Test2:" << endl;

	string s1("hello");
	cout << "hello" << endl;


	
	cout << s1.size() << endl;    //�����ַ�����Ч�ַ�����
	cout << s1.length() << endl;    //�����ַ�����Ч�ַ�����
	cout << s1.capacity() << endl;    //����s1��ռ�ռ��ܴ�С

	s1.clear();                    //��s�еĿռ���գ�ֻ����size����0�����ײ�ռ䲻��䣬��capacity��С����
	cout << s1.size() << endl;    
	cout << s1.capacity() << endl;    
	

	cout << "empty:" << endl;   //�п�
	if (s1.empty())            //�շ���true  ���շ���false      
	{
		cout << "s1 is Null" << endl;
	}
	else{
		cout << "si is exist" << endl;
	}
	cout << "resize:" << endl;   //����Ч�ַ��ĸ����ó�n��������Ŀռ����ַ�c���
	s1.resize(5, '!');        //��s1����Ч�ַ��������ӵ�5��������size����5�������λ�ò��ַ���
	cout << s1 << endl;         //helloû������Ϊ����clear��
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.resize(10, 'a');        //��s1����Ч�ַ��������ӵ�10��������size����10�������λ�ò��ַ�a
	cout << s1 << endl;        //!!!!!!!!!!aaaaa
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.resize(15);        //��s1����Ч�ַ��������ӵ�15��������size����15�����޲�ʱ�����λ�ò�ȱʡֵ\0
	cout << s1 << endl;       //\0��ӡ�����������ǿ��Կ����ӣ�sizeҲ�����15
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.resize(5);
	cout << s1 << endl;           //���5����
	cout << s1.size() << endl;    //��5��
	cout << s1.capacity() << endl;


	//��resize���󣬴ﵽ��������ʱresize���Զ����ݣ��������Ĵ�С��reverse������ͬ��������reserveע��
	s1.resize(20,'h');
	cout << s1 << endl;           
	cout << s1.size() << endl;    //��20��
	cout << s1.capacity() << endl;  //����Ϊ31

	s1.resize(15, 'h');
	cout << s1 << endl;
	cout << s1.size() << endl;    //��2��
	cout << s1.capacity() << endl;  //��������


	cout << "reverse:" << endl;   //Ϊ�ַ���Ԥ���ռ�,����ı�������������ı���Ч�ռ��С

	s1.reserve(20);
	cout << s1 << endl;
	cout << s1.size() << endl;           //����
	cout << s1.capacity() << endl;       //���31   
	//����ע�����
	//Ϊʲô���31�أ���Ϊ�����ǳɱ������ģ�����reserve��������capacity���Ƕ��١���vs��capacity��ֵ��ȡ��15 31 47 70 105�����1.5��
	//���ң���reserve��ֵ��ԭ����С��s1������Ҳ����䣬ԭ��capacity�Ǽ����Ǽ�����reserve��ֵС��С�ڵ���15����Ч�ַ�ҲС��reserve��ֵʱ��capacity��ֵ����15
	
	s1.reserve(16);
	cout << s1 << endl;
	cout << s1.size() << endl;           //����
	cout << s1.capacity() << endl;       //���� ��reserve��ֵ��С��15

	s1.reserve(7);
	cout << s1.size() << endl;     //���
	cout << s1.capacity() << endl;//��������

	s1.resize(7, '8');

	s1.reserve(6);                  //capacity��ֵҲ����䣬��Ч�ַ�����Ϊ7����С��reserve��ֵ
	cout << s1 << endl;
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

	s1.clear();
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;
}
//Q2.1 reserveӦ�ã� ����reserve��߲������ݵ�Ч�ʣ��������ݴ����Ŀ���
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
	s1.reserve(200);                       //��֪��������ж�������ǰ���ݣ������Ͳ���ÿ�ζ�������
	cout << "making s growing:" << endl;

	while (j--){

		if (s1.capacity() != cap1){
			cout << s1.capacity() << endl;
			cap1 = s1.capacity();
		}
		s1 += 'x';
	}



}




//Q3 string��ķ��ʼ���������

void Test3()
{
	//operator[] ���ʣ�����posλ�õ��ַ���const string��������
    //s.at()  Ҳ�ɷ��ʣ��÷�ͬ[]������Խ��ʱ����һ��
	string s("hello");
	cout << s[0] << endl;
	s[0] = 'H';
	// ���Խ��---assert����
	//cout << s[10] << endl;

	cout << s.at(2) << endl;
	s.at(2) = 'L';

	// ���Խ��---�׳�out_of_range�쳣
	//cout << s.at(10) << endl;


	//��������
	//1>
	string::iterator it = s.begin();      //ǰ������Ϳ��� auto ʶ��    ��s.begin()�����ַ�����Ԫ�ص�ַ��s.end�������һ��Ԫ�ص�ַ  
	while (it != s.end()){
		cout << *it << endl;
		it++;
	}

	
	string::reverse_iterator rit = s.rbegin();    //�Ӻ���ǰ��
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

//Q4:string�������޸Ĳ���
void Test4()
{
	string s;

	s.push_back('h');     //push_back: ���ַ�����β���ַ�c
	
	//append ���ַ�����׷��һ���ַ���
	//s.append('e');      //�����Լӵ����ַ�
	s.append("ello");     //���ں�����ַ���
	s.append(3, '!');     //�����ɸ������ַ�
	s.append(s);          //��һ���ַ���
	s.append("�й�");
	cout << s << endl;

	//operator+= ���ַ�����׷���ַ���str
	s += "chinese";
	s += '!';
	cout << s << endl;

	cout << s.c_str() << endl;     //c_str����C��ʽ�ַ���

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	//find + npos(��ʡ��Ĭ�ϴӿ�ʼ��) ���ַ���posλ�ÿ�ʼ�������ַ�c/�ַ���s�����ظ��ַ����ַ���/s��Ԫ�����ַ������е�λ��(�±�)
	cout << s.find('[') << endl;
	cout << s.find('h', 3) << endl;
	cout << s.find("hello") << endl;
	cout << s.find("hello",2) << endl;

	//rfind+npos(��ʡ��Ĭ�ϴ�ĩβ��ʼ��) ���ַ���posλ�ÿ�ʼ��ǰ���ַ�c�����ظ��ַ����ַ����е�λ��
	cout << s.rfind('h') << endl;
	cout << s.rfind('h', 20) << endl;

	//substr(pos,n) ��str�д�posλ�ÿ�ʼ����ȡn���ַ���n��ʡ��Ĭ�Ͻص����Ȼ���䷵��,
	string s1 = s.substr(s.find('h'),2);
	cout << s1 << endl;

	//Ӧ��1����ȡfile�ĺ�׺
	string s3("string.cpp.cpp");
	string s4(s3.substr(s3.rfind('.') + 1));
	cout << s4 << endl;
	//Ӧ��2�� ȡ��url�е�����
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

	//ɾ����erase(pos,n),��posλɾ��n���ַ���n��дɾ��pos�����е��ַ�
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