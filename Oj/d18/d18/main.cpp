#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

int main(){
	string str1, str2;
	while (cin >> str1 >> str2){
		int step = 0;
		int i;
		int len = str1.size();
		for (i = 0; i<len; i++){
			while (str1[i] == '?'&&i<len){
				i++;
			}
			if (str1[i] == '*'){
				i++;
				while (str1[i] == '?'&&i<len){    
					i++;
				}
				while (str2[i + step] != str1[i] && i + step<str2.size()){
					step++;
				}
			}
			if (str1[i] != str2[i + step]){
				break;
			}
		}
		if (i < str1.size() || i + step < str2.size()){
			cout << "false" << endl;
		}
		else{
			cout << "true" << endl;
		}
	}

}