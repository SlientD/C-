#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


//链接：https://www.nowcoder.com/questionTerminal/1624bc35a45c42c0bc17d17fa0cba788
//来源：牛客网
//给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。
//例如，如果输入数组{ 2, 3, 4, 2, 6, 2, 5, 1 }及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{ 4, 4, 6, 6, 6, 5 }；
//针对数组{ 2, 3, 4, 2, 6, 2, 5, 1 }的滑动窗口有以下6个：{ [2, 3, 4], 2, 6, 2, 5, 1 }，{ 2, [3, 4, 2], 6, 2, 5, 1 }，{ 2, 3, [4, 2, 6], 2, 5, 1 }，{ 2, 3, 4, [2, 6, 2], 5, 1 }，{ 2, 3, 4, 2, [6, 2, 5], 1 }，{ 2, 3, 4, 2, 6, [2, 5, 1] }。


class Solution {
public:
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		deque<int> q;       //保存比当前元素大的值的下标和当前元素下标
		vector<int> res;     //保存结果
		for (int i = 0; i<num.size(); i++){
			//擦除队中比现在元素小的元素的下标，这样同时也能保证有序
			while (!q.empty() && num[q[q.size() - 1]]<num[i]){
				q.pop_back();
			}
			q.push_back(i);
			//删掉是最大值但是已经不在滑动窗口的下标
			//cout << i - (int)size << endl;   // 0-size变成了无符号大整数
			
			while (!q.empty() && q[0] <= i - (int)size){
				q.pop_front();
			}
			//拿到一个滑动窗口后再开始放入
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


//当然也可以暴力解法但是。。。时间复杂度为O(N^2)。。


//双端队列是有下标访问操作的，也支持头尾都push pop