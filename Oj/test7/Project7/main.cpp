#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

bool LenthJudge(const vector<string> &v){
	for (int i = 0; i<v.size() - 1; i++){
		if (v[i].size()>v[i + 1].size()){
			return false;
		}
	}
	return true;
}
int strcmp(const string &x, const string &y){
	for (int i=0; i<x.size() && i<y.size(); i++){
		if (x[i]>y[i]){
			return 1;
		}
		if (x[i] < y[i]){
			return -1;
		}
	}
	return 0;
	
}
bool TypeJudge(const vector<string> &v){
	for (int i = 0; i<v.size() - 1; i++){
		if (strcmp(v[i], v[i + 1])>0){
			return false;
		}
	}
	return true;
}

int main(){
	int n;
	while (cin >> n)
	{
		if (n == 0){
			cout << "both" << endl;
			break;
		}
		vector<string> v(n);
		for (int i = 0; i<v.size(); i++){
			cin >> v[i];
		}
		bool len = LenthJudge(v);
		bool type = TypeJudge(v);
		if (len&&type){
			cout << "both" << endl;
		}
		else if (len){
			cout << "lengths" << endl;
		}
		else if (type){
			cout << "lexicographically" << endl;
		}
		else{
			cout << "none" << endl;
		}

	}




}


