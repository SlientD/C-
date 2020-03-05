#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


//���ӣ�https://www.nowcoder.com/questionTerminal/1624bc35a45c42c0bc17d17fa0cba788
//��Դ��ţ����
//����һ������ͻ������ڵĴ�С���ҳ����л�����������ֵ�����ֵ��
//���磬�����������{ 2, 3, 4, 2, 6, 2, 5, 1 }���������ڵĴ�С3����ôһ������6���������ڣ����ǵ����ֵ�ֱ�Ϊ{ 4, 4, 6, 6, 6, 5 }��
//�������{ 2, 3, 4, 2, 6, 2, 5, 1 }�Ļ�������������6����{ [2, 3, 4], 2, 6, 2, 5, 1 }��{ 2, [3, 4, 2], 6, 2, 5, 1 }��{ 2, 3, [4, 2, 6], 2, 5, 1 }��{ 2, 3, 4, [2, 6, 2], 5, 1 }��{ 2, 3, 4, 2, [6, 2, 5], 1 }��{ 2, 3, 4, 2, 6, [2, 5, 1] }��


class Solution {
public:
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		deque<int> q;       //����ȵ�ǰԪ�ش��ֵ���±�͵�ǰԪ���±�
		vector<int> res;     //������
		for (int i = 0; i<num.size(); i++){
			//�������б�����Ԫ��С��Ԫ�ص��±꣬����ͬʱҲ�ܱ�֤����
			while (!q.empty() && num[q[q.size() - 1]]<num[i]){
				q.pop_back();
			}
			q.push_back(i);
			//ɾ�������ֵ�����Ѿ����ڻ������ڵ��±�
			//cout << i - (int)size << endl;   // 0-size������޷��Ŵ�����
			
			while (!q.empty() && q[0] <= i - (int)size){
				q.pop_front();
			}
			//�õ�һ���������ں��ٿ�ʼ����
			if (i >= size - 1){
				res.push_back(num[q[0]]);
			}
		}
		return res;
	}
};


int main(){
	vector<int> v{ 2, 3, 4, 2, 6, 2, 5, 1 };
	
	vector<int> res = Solution().maxInWindows(v, 3);
}


//��ȻҲ���Ա����ⷨ���ǡ�����ʱ�临�Ӷ�ΪO(N^2)����


//˫�˶��������±���ʲ����ģ�Ҳ֧��ͷβ��push pop