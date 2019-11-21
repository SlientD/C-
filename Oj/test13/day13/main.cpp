#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
	string str;

	while (getline(cin, str)){
		vector<string> res;
		//int count=0;
		string tmp;
		for (int i = 0; i<str.size(); i++){
			
			if (str[i] != '"'){
				tmp = str.substr(i, str.find(' ', i) - i);
				res.push_back(tmp);
				i = str.find(' ', i);
			}
			else{
				tmp = str.substr(i + 1, str.find('"', i+1) - i-1);
				res.push_back(tmp);
				i = str.find('"', i+1);
			}
			if (i == -1){
				break;
			}
		}
		cout << res.size() << endl;
		for (int i = 0; i<res.size(); i++){
			cout << res[i] << endl;
		}
	}



}