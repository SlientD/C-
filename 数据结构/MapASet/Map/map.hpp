#pragma once

#include "RBtree.h"
#include <string>
#include <iostream>
using namespace std;
namespace MY_Map{

	
	template <class K,class V>
	class map{
		typedef pair<K, V> ValType;
		struct KAV{
			K operator()(const ValType &v)const
			{
				return v.first;
			}
		};
	public:
		typename typedef RBtree<ValType, KAV>::Iterator iterator;
		map()
			:RBtr()
		{

		}


		iterator begin(){
			return RBtr.begin();
		}
		iterator end(){
			return RBtr.end();
		}

		bool empty()const{
			return RBtr.empty();
		}
		size_t size()const{
			return RBtr.size();
		}

		pair<iterator, bool> insert(const ValType &v){
			return RBtr.insert(v);

		}

		iterator find(const K &k){
			return RBtr.Find(ValType(k, V()));
		}

		V& operator[](const K &k){
			return RBtr.insert(ValType(k, V())).first->second;
			
		}


	private:
		RBtree<ValType, KAV> RBtr;
	};


}

void TestMyMap(){
	MY_Map::map<string, string> m1;
	m1.insert(make_pair("orange","橘子"));
	m1.insert(make_pair("apple", "苹果"));

	cout << m1["apple"] << endl;
	cout << m1.size() << endl;

	m1["banana"] = "香蕉";
	cout << m1.size() << endl;

	m1.insert(make_pair("apple", "橙子"));  //插不进去了
	cout << m1.size() << endl;


	auto it = m1.begin();
	while (it != m1.end()){
		cout << "K:"<<it->first<<" V:"<<it->second << endl;
		it++;
	}

	//MY_Map::map<string, string> m2{ { "apple", "苹果" }, { "orange", "橘子" } };
	//auto it = m2.begin();
}