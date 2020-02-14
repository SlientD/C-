#include <iostream>
#include <vector>
using namespace std;
//Description
//给出4个1 - 10的数字，通过加减乘除，得到数字为24就算胜利
//输入：
//4个1 - 10的数字。[数字允许重复，但每个数字仅允许使用一次，测试用例保证无异常数字]
//输出：
//true or false


//法二

#if 0
//全排列函数介绍：包含头文件<algorithm>
// 栗子
//对一个数组全排列
#include <stdio.h>
#include <algorithm>
using namespace std;
int main(){
	int n;
	while (scanf("%d", &n) && n){
		int a[1000];
		for (int i = 0; i<n; i++){
			scanf("%d", &a[i]);
		}
		sort(a, a + n);//要先排序，否则会只按照当前的大小按字典序逐个增加的排序
		do{
			for (int i = 0; i<n; i++)
				printf("%d ", a[i]);
			printf("\n");
		} while (next_permutation(a, a + n));
	}
	return 0;
}
#endif




#include <stdio.h>
#include <algorithm>
using namespace std;
const int N=4;
int num[N];
int isSolve=0;
void dfs(int index,double currentNum,int arr[])
{
	if (index >= 4){
		if (currentNum == 24)
			isSolve = 1;
		return;
	}
	
	for(int operFlag=0;operFlag<4;operFlag++)
	{
		switch(operFlag)
		{
		case 0:
			dfs(index+1,currentNum+arr[index],arr);
			break;
		case 1:
			dfs(index+1,currentNum-arr[index],arr);
			break;
		case 2:
			dfs(index+1,currentNum*arr[index],arr);
			break;
		case 3:
			dfs(index+1,currentNum/arr[index],arr);
			break;
		}
		if(isSolve)
			return;
	}
}
int main()
{
	while (cin>>num[0]>>num[1]>>num[2]>>num[3])
	{
		isSolve = 0;
		sort(num, num + 4);
		do
		{
			dfs(1, num[0], num);
			if (isSolve)
				break;
		} while (next_permutation(num, num + 4));   //全排列函数
		if (isSolve)
			printf("true\n");
		else
			printf("false\n");
	}
	return 0;
}



#if 0
//法一：
bool CALL(vector<int> v, double res){
	if (v.empty()){
		return res == 24;
	}
	for (int i = 0; i<v.size(); i++){
		vector<int> tmp(v);
		tmp.erase(tmp.begin() + i);
		if (CALL(tmp, res + v[i]) || CALL(tmp, res*v[i]) || CALL(tmp, res - v[i]) || CALL(tmp, res / v[i])){
			return true;
		}
		return false;


	}
}

int main(){
	vector<int> v(4);
	while (cin >> v[0]){
		for (int i = 1; i<v.size(); i++){
			cin >> v[i];
		}

		if (CALL(v, 0)){
			cout << "true" << endl;
		}
		else
			cout << "false" << endl;
	}





	return 0;
}
#endif