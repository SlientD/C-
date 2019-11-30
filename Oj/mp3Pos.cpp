#include <iostream>
#include <string>
using namespace std;

int main(){
	int n;
	while (cin >> n){
		string ope;
		cin >> ope;
		int pos = 1;
		if (n <= 4){
			for (int i = 1; i<=n; i++){
				cout << i<<" ";
			}
			cout << endl;
			for (int i = 0; i<ope.size(); i++){
				if (ope[i] == 'U'){
					if (pos == 1){
						pos = n;
					}
					else
						pos--;
				}
				else{
					pos = pos%n + 1;
				}
			}
			cout << pos << endl;
			continue;
		}
		int start = 1, end = 4;

		for (int i = 0; i<ope.size(); i++){
			if (ope[i] == 'U'){
				if (pos == 1){
					pos = n;
					start = n - 4 + 1;
					end = pos;
				}
				else {
					pos--;
					if (start>pos){
						start = pos;
						end = start + 3;
					}
				}
			}
			else if (ope[i] == 'D'){
				if (pos == n){
					pos = 1;
					start = pos;
					end = 4;
				}
				else {
					pos++;
					if (end<pos){
						end = pos;
						start = end - 3;
					}
				}
			}
		}

		for (int i = start; i <= end; i++){
			cout << i << " ";
		}
		cout << endl;

		cout << pos << endl;
	}

	system("pause");
}