#include <iostream>
#include <string>
using namespace std;
bool JudgeDouJoker(string str){
	if (str == "joker JOKER" || str == "JOKER joker"){
		return true;
	}
	else{
		return false;
	}
}
bool JudgeSinJoker(string str){
	if (str == "joker" || str == "JOKER"){
		return true;
	}
	else{
		return false;
	}
}
void SinJoker(string str1, string str2){
	if (JudgeSinJoker(str1)){
		if (str2.size()>1 && str2 != "joker"&&str2 != "JOKER"){
			cout << "ERROR" << endl;
			return;
		}
		if (str1[0]>str2[0]){
			cout << str1 << endl;
			return;
		}
		else{
			cout << str2 << endl;
			return;
		}
	}

}

bool JudgeBoom(string str){
	if (str.size() != 7){
		return false;
	}
	for (int i = 0; i<str.size() - 2; i += 2){
		if (str[i] != str[i + 2]){
			return false;
		}
	}
	return true;

}
void JudgeTen(string str1, string str2)
{
	if (str1[0] == '1'&&str1[1] == '0'){
		if (str2.size() == (str1.size() + 1) / 2 || str2.size() == str1.size() - 1)
		{
			if (str2[0]>10 + '0' || str2[0] == '2'&&str2.size() == 1)
			{
				cout << str2 << endl;

			}
			else{
				cout << str1 << endl;
			}
			return;
		}
		else{
			cout << "ERROR" << endl;

			return;
		}

	}
}
int main(){
	string str;
	while (getline(cin, str)){
		string str1 = str.substr(0, str.find("-"));
		string str2 = str.substr(str.find("-") + 1);
		string tmp = "3456789JQKA2";


		if (JudgeDouJoker(str1)){
			cout << str1 << endl;
			break;
		}
		if (JudgeDouJoker(str2)){
			cout << str2 << endl;
			break;
		}
		if (JudgeSinJoker(str1)){
			SinJoker(str1, str2);
			break;
		}
		if (JudgeSinJoker(str2)){
			SinJoker(str2, str1);
			break;
		}
		if (JudgeBoom(str1) && !JudgeBoom(str2)){
			cout << str1 << endl;
			break;
		}
		if (JudgeBoom(str2) && !JudgeBoom(str1)){
			cout << str2 << endl;
			break;
		}
		if (str1[0] == '1'&&str1[1] == '0'){

			JudgeTen(str1, str2);
			break;
		}
		if (str2[0] == '1'&&str2[1] == '0'){

			JudgeTen(str2, str1);
			break;
		}
		if (str1.size() == str2.size() + 1 || str1.size() == str2.size() || str1.size() + 1 == str2.size()){
			if (tmp.find(str1[0])>tmp.find(str2[0])){
				cout << str1 << endl;
				break;
			}
			else{
				cout << str2 << endl;
				break;
			}
		}
		cout << "ERROR" << endl;

	}
}