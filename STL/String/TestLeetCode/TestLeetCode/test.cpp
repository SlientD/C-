#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
void reverse(string &s, int start, int end)
{
	char tmp;
	while (start < end){
		tmp = s[start];
		s[start] = s[end];
		s[end] = tmp;
		start++;
		end--;
	}

}
//string reverseWords(string s) {
//	int len = s.size();
//	int pos = 0;
//	int end = 0;
//	while (end<len&&end >= 0)
//	{
//		end = s.find(pos, ' ');
//		reverse(s, pos, end - 1);
//		pos = end + 1;
//	}
//	reverse(s, s.rfind(' ') + 1, len - 1);
//	return s;
//
//}
int main()
{
	string s = "Let's take LeetCode contest";
	int len = s.size();
	int pos = 0;
	int end = 0;
	while (end<len&&end >= 0)
	{
		end = s.find(pos, ' ');
		reverse(s, pos, end - 1);
		pos = end + 1;
	}
	reverse(s, s.rfind(' ') + 1, len - 1);
	cout << s << endl;

	system("pause");
	return 0;;
}