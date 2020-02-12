#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
//discrimination：
//Given a string S, return the "reversed" string where all characters that are not a letter stay in the same place,
//and all letters reverse their positions.
bool Judge(char x){

	if ((x <= 'Z'&&x >= 'A') || (x <= 'z'&&x >= 'a') || (x <= '9'&&x >= '0')){
		return false;
	}
	else
		return true;
}
int main(){
	
	string S = "ab-cd";
		int start = 0, end = S.size() - 1;
		char tmp;
		while (start<end){
			while (Judge(S[start]) && start<end){
				start++;
			}
			while (Judge(S[end]) && start<end){
				end--;
			}

			tmp = S[start];
			S[start] = S[end];
			S[end] = tmp;
			start++;
			end--;

		}
		cout<<S<<endl;
}