#pragma once

#include "RBtree.h"
#include <string>
#include <iostream>
using namespace std;
namespace MY_Set{


	template <class K>
	class set{
		struct KAV{
			K operator()(const K &v)const
			{
				return v;
			}
		};
		
	public:
		typename typedef RBtree<K, KAV>::Iterator iterator;
		set()
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

		pair<iterator, bool> insert(const K &v){
			return RBtr.insert(v);

		}

		iterator& find(const K &k){
			return RBtr.Find(k);
		}

		


	private:
		RBtree<K, KAV> RBtr;
	};


}

void TestMySet(){
	MY_Set::set<string> m1;
	m1.insert("orange");
	m1.insert("apple");

	cout << m1.size() << endl;

	m1.insert("apple");

	cout << m1.size() << endl;
	auto it = m1.begin();
	while (it != m1.end()){
		cout << "K:" << *it << endl;
		it++;
	}
	auto f = m1.find("apple");
	cout << "THE K:" << *f << endl;
    f = m1.find("BANANA");
	if (f._pNode){
		cout << "THE K:" << *f << endl;
	}
	else{
		cout << "NULL" << endl;
	}
	


	//MY_Map::map<string, string> m2{ { "apple", "Æ»¹û" }, { "orange", "éÙ×Ó" } };
	//auto it = m2.begin();
}