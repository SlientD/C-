#define _CRT_SECURE_NO_WARNINGS 1
#if 0
#include <iostream>
using namespace std;

struct A{
	long a1;        //64位占8个字节   32位占4个
	short a2;
	int a3;
	int *a4;       //64位占8个字节   32位占4个
};
char fun(char x, char y){
	if (x < y)
		return x;
	return y;
}
int main(){
	//int x = 00123, y = 123;     //带0表示这个数是8进制

	//printf("%o,%o\n", x, y);    //-->123 173    不带0输出   o是八进制 x是16进制

	//printf("%d\n", sizeof(struct A));     //--->16是为什么？  应该是24啊？？
	//system("pause");

	int a = '1', b = '1', c = '2';
	cout << fun(fun(a, b), fun(b, c)) << endl;   //cout是可以输出一个函数的返回值的
	system("pause");
	return 0;
}
#endif
#if 0
#include <iostream>
#include <string>
using namespace std;

int StrToInt(string str) {
	int res = 0;
	int t = 1;
	int i = str.size() - 1;
	for (i; i>0; i--){
		if (str[i] >= '0'&&str[i] <= '9'){
			res += (str[i] - '0')*t;
			t *= 10;
		}
		else{
			return 0;;
		}
	}
	if (str[0] >= '0'&&str[0] <= '9'){
		return res + (str[0] - '0')*t;
	}
	else if (str[0] == '+'){
		return res;
	}
	
	else if (str[0] == '-'){
		return -res;
	}
	return 0;
}

int main(){
	string s = "123";
	int res = StrToInt(s);
	cout << res << endl;


	system("pause");
	return 0;
}

#endif


#if 0

#include <iostream>
#include <vector>
using namespace std;
bool Judge(vector<vector<int>> &v, int i, int j){
	if (v[i][j] != 1)
	{
		if (!((i - 2) >= 0 && v[i - 2][j] == 1)){

			if (!((j - 2) >= 0 && v[i][j - 2] == 1)){
				
				return true;

			}
		}

	}
	return false;

}
int FindRes(vector<vector<int>> v){
	int res = 0;
	int i, j;
	for (i = 0; i<v.size(); i++){
		for (j = 0; j<v[i].size(); j++){
			if (Judge(v, i, j)){
				res++;
				v[i][j] = 1;


			}
		}
	}
	return res;

}

int main(){
	int W, H;
	while (cin >> W >> H){
		vector<vector<int>> v(H);
		for (int i = 0; i < H; i++){
			vector<int> v1(W);
			v[i] = v1;
		}
		int res = FindRes(v);
		cout << res << endl;
	}

}
#endif