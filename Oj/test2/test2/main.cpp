#define _CRT_SECURE_NO_WARNINGS 1

#if 0
#include <iostream>
#include <string>
using namespace std;
void reverse(string &str, int start, int end){
	while (start<end){
		swap(str[start], str[end]);
		start++;
		end--;
	}
}
int main(){
	string str;
	while (getline(cin,str)){
		reverse(str, 0, str.length() - 1);
		int start = 0;
		for (int i = 0; i<str.size(); i++){
			start = i;
			while (str[i] != ' '&&str[i] != '\0'){
				i++;
			}
			reverse(str, start, i - 1);
		}
		cout << str << endl;
	}

}
#endif
#include <iostream>
#include <vector>
using namespace std;

int main(){
	int num;
	while (cin >> num){
		if (num == 0){
			cout << num << endl;
			continue;
		}
		vector<int> arr(num);

		int count = 0;
		for (int j = 0; j<arr.size(); j++){
			cin >> arr[j];
		}
		int i = 0;
		while (i<arr.size() - 1){

			if (i<(arr.size() - 1) && arr[i] <= arr[i + 1]){
				while (i<(arr.size() - 1) && arr[i] <= arr[i + 1]){
					i++;
				}
				count++;
				i++;
			}
			if (i<(arr.size() - 1) && arr[i] >= arr[i + 1]){
				while (i<(arr.size() - 1) && arr[i] >= arr[i + 1]){
					i++;
				}
				count++;
				i++;
			}
		}
		if (i == arr.size() - 1)
		{
			count++;
		}
		cout << count << endl;
	}



}