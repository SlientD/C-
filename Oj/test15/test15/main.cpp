#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<int> left{ 1, 2, 0, 1, 3, 1 };
	vector<int> right{ 0, 0, 0, 2, 0, 1 };
	int sum = 0;
	int leftsum=0,rightsum=0;
	int leftmin=27,rightmin=27;
	for(int i=0;i<left.size();i++){
		if(left[i]==0||right[i]==0)
		{
			sum+=(left[i]+right[i]);
		}
		else{
			if(left[i]<leftmin){
				leftmin=left[i];
			}
			if(right[i]<rightmin){
				rightmin = right[i];
			}
			leftsum += left[i];
			rightsum += right[i];
		}
	}
	leftsum = leftsum - leftmin + 1;
	rightsum = rightsum - rightmin + 1;
	int min;
	if (leftsum<rightsum){
		min = leftsum;
	}
	else{
		min = rightsum;
	}
	sum = sum + min + 1;
	cout << sum << endl;
	system("pause");
}

#if 0
int main(){
	char str[] = "abcdef";
	char *p1 = str;
	char *p2 = p1;
	*p1++ = *p2++;       //这个操作就是分别让p1和p2向后移了
	cout << str << endl;
	cout << p1 << endl;
	cout << p2 << endl;
	system("pause");
	return 0;
}
#endif