#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int FindStr(string str1, string str2, int pos1){
	
	int max = 0;
	int pos2 = -1;	
	do{
		pos2 = str2.find(str1[pos1], pos2 + 1);
		if (pos2 < 0){
			break;
		}
		int tmp2 = pos2;
		int tmp1 = pos1;
		int count = 0;
		while (str1[tmp1] == str2[tmp2] && tmp1<str1.size() && tmp2<str2.size()){
			tmp1++;
			tmp2++;
			count++;
		}
		if (max<count){
			max = count;
		}
	} while ( pos2<str2.size());
	return max;
}
int main(){
	string str1, str2;
	while (cin >> str1 >> str2){

		if (str1.size()>str2.size()){
			swap(str1, str2);
		}
		vector<int> v(str1.size());
		for (int i = 0; i<str1.size(); i++){
			v[i] = FindStr(str1, str2, i);
		}
		int max = 0, pos = 0;
		for (int i = 0; i<v.size(); i++){
			if (v[i]>max){
				max = v[i];
				pos = i;
			}
		}
		string str = str1.substr(pos, v[pos]);
		cout << str << endl;
	}
}