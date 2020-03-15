#define _CRT_SECURE_NO_WARNINGS 1
//c++11�ײ��ǹ�ϣ�ṹ�Ĺ���ʽ����
//ʲô�ǹ���ʽ������ kvģ�� kģ��
//��һ���ļ� ���洢����ip��ַ���ҳ����ִ�������ǰk��ip��ַ--top k
//1.ͳ��ÿ��ip��ַ�����ֵĴ���  <ip,���ִ���>��ֵ��
//2.���ȼ����д���С��

//��һ��Ӣ�Ĵʵ䣬���һ�������Ƿ�ƴд��ȷ
//1.�������еĵ��ʴ洢
//2.�ڴ洢�ĵ��ʼ������Ҵ����ĵ����Ƿ����
//unordered_map ��Ԫ������Ϊ��k��v��ģ�ͼ�ֵ�ԣ�k�ǲ����ظ���
//unordered_set ��Ԫ������Ϊk��k�����ظ�
//unordered_multimap ��Ԫ������Ϊ��k��v��ģ�ͼ�ֵ�ԣ�k�ǿ��ظ���
//unordered_multiset ��Ԫ������Ϊk��k�����ظ�
//��ͬ�㣺�ײ�ṹ������ͬ�ģ���ϣͰ��������Ч�ʺܿ춼��O(1)


#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

void TestUnordered_map(){
	unordered_map<string, string> m;
	//�����ֵ�Ե����ַ�ʽ��pair�ṹ��
	m.insert(pair<string, string>("�ν�", "��ʱ��"));
	m.insert(pair<string, string>("�ν�", "��ʱ��"));
	m.insert(pair<string, string>("�ν�", "��ʱ��"));

	m.insert(make_pair("����","����"));

	cout << m.size() << endl;         //��ȡԪ�ظ���
	cout << m.bucket_count() << endl; //��ȡͰ�ĸ���
	cout << m.bucket_size(0) << endl; //��ȡ0��Ͱ��Ԫ�ظ���
	cout << m.bucket("�ν�") << endl;  //��k����Ͱ��Ͱ��
	//����Ͱ�źͼ����е��±��ǲ�һ����

	cout << m["����"] << endl; //��һ�����ڵ�k���������k��Ӧ��v
	cout << m.size() << endl;
	cout << m["³��"] << endl; //���k�����ڣ�����������k��Ĭ�ϵ�v���գ�����һ����ֵ�Բ��뵽map�У�����Ĭ�ϵ�v
	cout << m.size() << endl;
	m.erase("³��");
	m.clear();

}

void TestUnordered_multimap(){
	//û���±����������  ��Ϊ���ظ���
	//count�ӿ����֮�¾���������


}















