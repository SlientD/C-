#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

//Description:
//Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
//return the length of last word (last word means the last appearing word if we loop from left to right) in the string.
//If the last word does not exist, return 0.


int main(){
	string s = "h";
	int end = s.size() - 1;
	while (end>0 && s[end] == ' '){
		end--;
	}
	int start = end;
	while (start >= 0 && s[start] != ' '){
		start--;
	}
	cout<< end - start<<endl;
	/*if (s.size() == 0){
		cout<<0<<endl;
	}
	int pos = s.rfind(' ');
	if (pos == -1){
		printf("%d\n", s.size());
	}
	else{
		string tmp=s.substr(pos+1);
		while (tmp == " "&&pos != -1){
			pos = s.rfind(' ', pos - 1);
			tmp = s.substr(pos);
			
		}
		if (tmp == " "){
			cout << 0 << endl;
		}
		printf("%d\n", tmp.size());
	}*/


	system("pause");
	return 0;
}