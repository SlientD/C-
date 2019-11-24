#define _CRT_SECURE_NO_WARNINGS 1
#if 0
#include <iostream>
#include <string>
using namespace std;


string AddLongInteger(string addend,string augend){
	int len1=addend.size();
	int len2=augend.size();

	if(len1<len2){
		swap(addend,augend);
	}
	int flag=0;
	int tmp=0;
	int i=addend.size()-1,j=augend.size()-1;
	for(i,j;i>=0&&j>=0;i--,j--){
		addend[i]+=(augend[j]-'0'+flag);
		flag=0;
		if(addend[i]>'9'){
			flag=1;
			addend[i] -= 10;
		}
	}
	while (flag != 0 && i >= 0){
		addend[i] += flag;
		flag = 0;
		if (addend[i]>'9'){
			flag = 1;
			addend[i] -= 10;
		}
		i--;
	}
	if (flag == 1){
		addend.insert(0, 1, '0' + flag);
	}
	return addend;
}

int main(){
	string str1, str2;
	while (cin >> str1 >> str2){
		string res = AddLongInteger(str1, str2);
		cout << res << endl;

	}
}

#endif


#if 1
#include <iostream>
using namespace std;

template <class T>
struct sum{
	static void foo(T x, T y){
		cout << x << y;
	}
	
};
struct A{
	void foo(int x, int y){
		cout << x << y;
	}

};


int main(){
	sum<int>::foo(1, 2);
	//A::foo(1, 2);   //报错，必须通过对象访问非静态成员
}
#endif