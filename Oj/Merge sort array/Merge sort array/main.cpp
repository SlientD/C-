#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;


//discription:
//Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
//
//Note:
//The number of elements initialized in nums1 and nums2 are m and n respectively.
//You may assume that nums1 has enough space(size that is greater or equal to m + n) to hold additional elements from nums2.

int main(){
	vector<int> nums1{ 1, 2,3};
	vector<int> nums2{ 2,5,6};
	int m = 3, n = 3;

	nums1.resize(m + n);
	for (int i = m - 1; i >= 0; i--){
		nums1[n + i] = nums1[i];
	}
	int i = n, j = 0, pos = 0;
	while (i<m + n&&j<n){
		if (nums1[i]<nums2[j]){
			nums1[pos] = nums1[i];
			i++;
		}
		else{
			nums1[pos] = nums2[j];
			j++;
		}
		pos++;
	}
	while (j<n){
		nums1[pos] = nums2[j];
		j++;
		pos++;
	}

	system("pause");
	return 0;;
}