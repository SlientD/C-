#define _CRT_SECURE_NO_WARNINGS 1
//c++11底层是哈希结构的关联式容器
//什么是关联式容器？ kv模型 k模型
//给一个文件 ：存储的是ip地址，找出出现次数最多的前k掉ip地址--top k
//1.统计每个ip地址所出现的次数  <ip,出现次数>键值对
//2.优先级队列创建小堆

//给一个英文词典，检测一个单词是否拼写正确
//1.将单词中的单词存储
//2.在存储的单词集合中找带检测的单词是否存在
//unordered_map ：元素类型为《k，v》模型键值对，k是不能重复的
//unordered_set ：元素类型为k，k不可重复
//unordered_multimap ：元素类型为《k，v》模型键值对，k是可重复的
//unordered_multiset ：元素类型为k，k不可重复
//共同点：底层结构都是相同的（哈希桶），查找效率很快都是O(1)


#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

void TestUnordered_map(){
	unordered_map<string, string> m;
	//构造键值对的两种方式：pair结构体
	m.insert(pair<string, string>("宋江", "及时雨"));
	m.insert(pair<string, string>("宋江", "及时雨"));
	m.insert(pair<string, string>("宋江", "及时雨"));

	m.insert(make_pair("武松","行者"));

	cout << m.size() << endl;         //获取元素个数
	cout << m.bucket_count() << endl; //获取桶的个数
	cout << m.bucket_size(0) << endl; //获取0号桶中元素个数
	cout << m.bucket("宋江") << endl;  //求k所在桶的桶号
	//所在桶号和监视中的下标是不一样的

	cout << m["武松"] << endl; //给一个存在的k，返回与该k对应的v
	cout << m.size() << endl;
	cout << m["鲁达"] << endl; //如果k不存在，会用所给的k与默认的v（空）构建一个键值对插入到map中，返回默认的v
	cout << m.size() << endl;
	m.erase("鲁达");
	m.clear();

}

void TestUnordered_multimap(){
	//没有下标运算符重载  因为有重复的
	//count接口相比之下就有意义了


}















