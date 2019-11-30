#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;

#if 0
//WAY1
int main(){

	int T;
	while (cin >> T){
		while (T--){
			int n, k;
			cin >> n >> k;
			vector<int> v(2 * n);
			for (int i = 0; i < v.size(); i++){
				cin >> v[i];
			}
			vector<int> tmp(2 * n);
			while (k--){
				for (int i = 0; i < n; i++){
					tmp[2 * i] = v[i];
					tmp[2 * i + 1] = v[n + i];
				}
				v = tmp;
			}
			for (int i = 0; i < v.size()-1; i++){
				cout<<v[i]<<" ";
			}
			cout<<v[v.size()-1]<<endl;
		}
	}



	system("pause");
	return 0;
}
#endif

int main(){

	int T;
	cin >> T;
	while (T--){
		int n, k;
		cin >> n >> k;
		vector<int> v(2 * n);
		for (int i = 0; i < v.size(); i++){
			int tmp = i;
			int t = k;
			while (t--){
				if (tmp<n)  tmp = tmp * 2;
				else       tmp = (tmp - n) * 2 + 1;
			}
			cin >> v[tmp];
		}
		for (int i = 0; i < v.size() - 1; i++){
			cout << v[i] << " ";
		}
		cout << v[v.size() - 1] << endl;
	}


}