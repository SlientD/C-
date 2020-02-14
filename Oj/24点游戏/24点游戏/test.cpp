#include <iostream>
#include <vector>
using namespace std;
//Description
//����4��1 - 10�����֣�ͨ���Ӽ��˳����õ�����Ϊ24����ʤ��
//���룺
//4��1 - 10�����֡�[���������ظ�����ÿ�����ֽ�����ʹ��һ�Σ�����������֤���쳣����]
//�����
//true or false


//����

#if 0
//ȫ���к������ܣ�����ͷ�ļ�<algorithm>
// ����
//��һ������ȫ����
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
		sort(a, a + n);//Ҫ�����򣬷����ֻ���յ�ǰ�Ĵ�С���ֵ���������ӵ�����
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
		} while (next_permutation(num, num + 4));   //ȫ���к���
		if (isSolve)
			printf("true\n");
		else
			printf("false\n");
	}
	return 0;
}



#if 0
//��һ��
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