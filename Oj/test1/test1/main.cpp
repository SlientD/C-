#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>
#include <string>
using namespace std;






#if 1

#include <iostream>
#include <vector>
using namespace std;
int sort(vector<int> &arr, int begin, int end){
	int i = arr[begin];
	while (begin<end)
	{

		while (arr[end] <= i&&begin<end)
		{
			end--;
		}
		if (begin<end)
			arr[begin] = arr[end];
		while (arr[begin] >= i&&begin<end)
		{
			begin++;
		}
		if (begin<end)
			arr[end] = arr[begin];
	}
	arr[end] = i;
	return end;
}
void quick_sort(vector<int> &arr, int start, int end){
	if (start<end){

		int mid = sort(arr, start, end);
		quick_sort(arr, start, mid - 1);
		quick_sort(arr, mid + 1, end);
	}
	else{
		return;
	}
}
using namespace  std;
int main()
{

	int num;

	while (cin >> num)
	{
		vector<int> team(num * 3);
		long sum = 0;
		for (int i = 0; i<num * 3; i++)
		{
			cin >> team[i];
		}
		//sort(team.begin(),team.end())
		quick_sort(team, 0, team.size() - 1);
		for (int i = 0; i<num; i++)
		{
			sum += team[1+i*2];
		}
		cout << sum << endl;
	}
	system("pause");
	return 0;


}
#endif

#if 0
bool StringIn(const char &c, string str){
	for (int i=0; i<str.size(); i++)
	{
		if (c == str[i]){
			return true;
		}
	}
	return false;

}
int main(){
	string str1;
	string str2;

	while (getline(cin, str1)){
		getline(cin, str2);
		for (int i = 0; i<str1.size(); i++)
		{
			if (StringIn(str1[i], str2))
			{
				str1.erase(i,1);
				i--;
			}
		}
		cout << str1 << endl;
	}
}
#endif