#include <map>
#include <string>
#include <iostream>
using namespace std;


void TestMap(){
	map<string, string> m1;
	map<string, string> m2{ { "apple", "ƻ��" }, { "orange", "����" } };
	auto it = m2.begin();
	
}

