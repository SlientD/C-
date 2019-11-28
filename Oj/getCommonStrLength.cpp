#define _CRT_SECURE_NO_WARNINGS 1
//计算两个字符串的最大公共字串的长度
#include <iostream>
#include <string>
using namespace std;
int getCommonStrLength(string str1, string str2){
	int count = 0, max = 0;

	for (int i = 0; i<str1.size(); i++){
		int tmp2 = 0;
		while (tmp2<str2.size()){
			tmp2 = str2.find(str1[i], tmp2);
			if (tmp2 == -1){
				break;
			}
			int tmp1 = i;
			count = 0;
			while (str1[tmp1] == str2[tmp2] && tmp1<str1.size() && tmp2<str2.size()){
				tmp1++;
				tmp2++;
				count++;
			}
			if (count>max){
				max = count;
			}
		}
	}
	return max;
}
int main(){
	string str1, str2;
	while (getline(cin, str1)){
		getline(cin, str2);
		int res = getCommonStrLength(str1, str2);
		cout << res << endl;
	}
}