#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>    
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
int main(){
	/*int x = 10;
	int y = 10;
	x = y = ++y;
	printf("%d %d", x, y);
	vector<int> nums{ 1, 2, 3, 4,4 };
	auto pos = find(nums.begin(), nums.end(), 4);

	while (pos != nums.end()){
	nums.erase(pos++);
	auto pos = find(nums.begin(), nums.end(), 4);
	}*/
	/*vector<int> nums{ 1, 3, 5, 6 };
	int target = 4;
	int res = 0;
	int begin = 0, end = nums.size(), mid = nums.size() / 2;
	while (nums[mid] != target&&begin<end-1){
		if (target<nums[mid]){
			end = mid;

		}
		else{
			begin = mid;
		}
		mid = (begin + end) / 2;
	}
	printf("%d\n", mid);*/
	string magazine = "", ransomNote="";
	int pos = magazine.find(ransomNote[0]);
	while (pos != -1){
		string tmp = magazine.substr(pos, magazine.size());
		if (tmp == ransomNote)
			cout<<true<<endl;
		pos = magazine.find(ransomNote[0], pos + 1);
	}

	cout<<false<<endl;
	system("pause");
	return 0;
}