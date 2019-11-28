#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>

#include <algorithm>        //reverse所在头文件  ,oj中也可使用该头文件来直接对 字符串/vector容器 进行反转(只要给一个区间)，不用用户自己实现

using namespace std;
int main(){
	string str="abc";
	char s[] = "abc";
	reverse(str.begin(), str.end());   //reverse函数是反转容器中的内容，对字符数组无效。
	cout << str << endl;
	reverse(&s[1],&s[2]);        //值是不会更改的
	cout << s << endl;

	//_strrev:使用这个函数可以实现对字符数组的逆转,注意是字符数组，整形数组不可以！
	_strrev(s);
	cout << s << endl;
	
	vector<int> v{ 1, 2, 3 };
	reverse(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << endl;
	}

	


	system("pause");

}