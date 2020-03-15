#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int evalRPN(vector<string>& tokens) {
	stack<int> s;
	int index = 0;
	int x, y;
	if (tokens.size() == 1)
	{
		return atoi(tokens[0].c_str());
	}
	while (index<tokens.size())
	{

		while (tokens[index] != "+"&&tokens[index] != "-"&&tokens[index] != "*"&&tokens[index] != "/")
		{
			s.push(atoi(tokens[index++].c_str()));
		}
		y = s.top();
		s.pop();
		x = s.top();
		s.pop();

		
		switch (tokens[index++].c_str()[0])
		{
		case '+':s.push(x + y); break;
		case '-':s.push(x - y); break;
		case '*':s.push(x*y); break;
		case '/':{
					 if (y != 0)
						 s.push(x / y);
					 else
						 s.push(0);
					 break;
				}

		}
	}
	return s.top();
}
int main()
{
	vector<string> tokens{ "4", "13", "5", "/", "+" };
	int res=evalRPN(tokens);
	cout << res << endl;

	system("pause");
	return 0;
}