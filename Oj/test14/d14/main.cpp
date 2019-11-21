#define _CRT_SECURE_NO_WARNINGS 1
#if 0
#include <iostream>
#include <vector>
using namespace std;
class Date{
public:
	Date(int _year, int _month, int _day)
		:year(_year)
		, month(_month)
		, day(_day)
	{

	}
	int Getday(int i){
		vector<int> mon{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			mon[2] += 1;
		}
		return mon[i];
	}
	int getOutDay(){
		int res = 0;
		for (int i = 0; i<month; i++){
			res += Getday(i);
		}
		res += day;
		return res;
	}
public:
	int year;
	int month;
	int day;
};

bool judge(Date d){
	if (d.month<13 && d.day>0 && d.day <= d.Getday(d.month)){
		return true;

	}
	else return false;
}

int main(){
	int year, month, day;
	cin >> year >> month >> day;

	Date d(year, month, day);
	int res;
	if (judge(d)){
		res = d.getOutDay();
	}
	else{
		res = -1;
	}
	cout << res << endl;
	system("pause");


}
#endif

#if 0
#include <iostream>
#include <vector>
#include <climits>

using namespace std;
void SetDiv(vector<int> &v, int num){
	for (int i = 2; i*i<=num; i++){
		if (num%i == 0){
			if ((num + i)<v.size()&&v[num] + 1<v[num + i]){
				v[num + i] = v[num] + 1;
			}
			if ((num + num/i)<v.size() && v[num] + 1<v[num + num/i]){
				v[num + num/i] = v[num] + 1;
			}
		}
	}
}
int main(){
	int N, M;
	while (cin >> N >> M){

		vector<int> v(M + 1, INT_MAX);
		v[N] = 0;
		for (int i = N; i < M; i++){
			if (v[i] != INT_MAX)
				SetDiv(v, i);
		}
		if (v[M] != INT_MAX){
			cout << v[M] << endl;
		}
		else
			cout << -1 << endl;
	}
}

#endif
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int res = 0;
void Cal(vector<int> v, int start, int add, int mul){
	for (int i = start; i<v.size(); i++){
		add += v[i];
		mul *= v[i];
		if (add>mul){
			cout << add << " " << mul << endl;
			res++;

		}
		else{
			break;
		}

		Cal(v, start + 1, add, mul);
		add -= v[i];
		mul /= v[i];
		while (i<v.size()-1 && v[i] == v[i + 1]){
			i++;
		}



	}
}

int main(){
	int n;
	while (cin >> n){
		res = 0;
		vector<int> v(n);
		for (int i = 0; i<v.size(); i++){
			
			cin >> v[i];
		}

		sort(v.begin(), v.end());

		
		int count1 = 0;
		while (v[count1] == 1){
			count1++;
		}
		res += (count1 - 1);

		for (int i = 1; i<=count1; i++){
			Cal(v, count1, i, 1);
		}
		cout << res << endl;
	}




}

#endif


#if 0
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int cont = 0;
void ContOne(int, vector<int>, int, int, int); //（1的个数，非1数，当前位数, 和, 积）
int main(void)
{
	int n, numb, OneCont(0);        //OneCont用来记录1的总个数
	vector<int> list;
	cin >> n;
	while (n--)
	{
		cin >> numb;
		if (numb > 1)
			list.push_back(numb);
		else
			OneCont++;
	}
	cont = OneCont - 1; //将纯1数组先计算出来
	if (!list.empty())
	{
		sort(list.begin(), list.end()); //对数组排序
		for (int i = 1; i <= OneCont; i++) ContOne(i, list, 0, i, 1);
	}
	cout << cont << endl;
	system("pause");
	return 0;
}
void ContOne(int OneNub, vector<int> list, int nowBit, int sum, int mult)
{
	for (int i = nowBit; i < list.size(); i++) //迭代计算和与积
	{
		sum += list[i], mult *= list[i];
		if (sum <= mult) //如果不符合，回溯至上一位
			break;
		else
			cont++;
		ContOne(OneNub, list, i + 1, sum, mult);
		sum -= list[i], mult /= list[i]; //回到上一位后需要恢复数值
		while (i < list.size() - 1 && list[i] == list[i + 1])
			i++;  //寻找不重复
	}

	
}
#endif