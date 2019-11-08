#define _CRT_SECURE_NO_WARNINGS 1
//#include <iostream>
//#include <string>
//using namespace std;
//
//int main(){
//	string str;
//	while (getline(cin, str)){
//		if (str.size() == 1){
//			cout << str << endl;
//			continue;
//		}
//		int start = 0, end = start + 1;
//		int start1 = start, end1 = end;
//		int count, res = 0;
//		// int flag=1;
//		while (end<str.size()){
//			if (str[start] - str[end] == 1){
//				count = 1;
//				while (str[end - 1] - str[end] == 1 && end<str.size()){
//					end++;
//					count++;
//				}
//				if (count>res){
//					res = count;
//					start1 = start;
//					end1 = end - 1;
//				}
//				start = end - 1;
//
//			}
//			else if (str[start] - str[end] == -1){
//				count = 1;
//				while (str[end - 1] - str[end] == -1 && end<str.size()){
//					end++;
//					count++;
//				}
//				if (count>res){
//					res = count;
//					start1 = start;
//					end1 = end - 1;
//				}
//				start = end - 1;
//
//			}
//			else{
//				start++;
//				end++;
//			}
//
//
//		}
//	}
//
//}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	vector<int> numbers(1);
		int len = numbers.size();
		for (int i = 0; i<numbers.size(); i++){
			cin >> numbers[i];
		}

		
		sort(numbers.begin(), numbers.end());
		for (int i = 0; i<(len+1) / 2; i++){
			int count = 1;
			while (numbers[i] == numbers[i + 1] && i<(len - 1)){
				count++;
				i++;

				if (count>len / 2){
					cout<< numbers[i]<<endl;
					system("pause");
				}
			}
		}
		
		cout << "0" << endl;
		system("pause");
}
