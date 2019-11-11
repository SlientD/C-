#define _CRT_SECURE_NO_WARNINGS 1
#if 0
#include <iostream>
#include <vector>
using namespace std;

int main(){
	int x = -3;
	int y = x / 2;
	int z = x % 2;
	cout << x << y << z<<endl;

	system("pause");
	return 0;
}
#endif
#include <iostream>
using namespace std;
void Func(int num, int b){
	if (num != 0){
		Func(num / b, b);
		if (num%b<10)
			cout << num%b;
		else
			cout << (char)(num%b - 10 + 'A');
	}



}
int main(){
	int num, b;
	while (cin >> num >> b){
		Func(num, b);
		cout << endl;





	}
}