#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool Judge(string str, char ch){
	for (int i = 0; i<str.size(); i++){
		if (str[i] == ch){
			return true;
		}
		
	}
	return false;
}


int main(){
	string des, str;
	des = "they are student";
	str = "aeiou";
		
		int step = 0;
		for (int i = 0; i<des.size() - step; i++){
			while (Judge(str, des[i + step])){
				step++;
			}
			des[i] = des[i + step];
		}
		des.resize(des.size() - step);
		cout << des << endl;
	



	system("pause");
	return 0;
}