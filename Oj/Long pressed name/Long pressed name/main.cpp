#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
int main(){

	string name = "saeed", typed = "ssaaed";
	int pos = 0;
	for (int i = 0; i<name.size(); ){
		if (name[i] == typed[pos]){
			pos++;
			i++;
			
		}
		else if (name[i - 1] == typed[pos]){
			while (name[i - 1] == typed[pos]){
				pos++;
			}

		}
		else
			cout<< false;

	}
	cout<< true;

	system("pause");
	return 0;
}