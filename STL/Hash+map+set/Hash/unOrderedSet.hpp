#pragma once
#include "hashBuckt.hpp"
#include "common.hpp"
namespace Set{
	template<class K>
	class unordered_set{
		
		
		//未加typename之前，编译器会将HashBucket<value,DFKV>::iterator当做类中的静态成员变量来处理
		//因为成员变量也是根据类型::讲台成员变量名字来访问的
		//typename在此的作用就是明确HashBucket<value,DFKV>::iterator中的一种类型
		typename typedef HashBucket<K>::iterator iterator;
	public:
		unordered_set()
			:_ht()
		{

		}
		~unordered_set(){
			_ht.clear();
		}
		iterator begin(){
			return _ht.begin();
		}
		iterator end(){
			return _ht.end();
		}
		bool empty()const{
			return _ht.empty();
		}
		size_t size()const
		{
			return _ht.size();
		}
		/*iterator find(const K &key){
		return _ht.find(key);
		}*/
		pair<iterator, bool> insert(const K &v){
			return _ht.insert(v);

		}
		size_t erase(const K &key){
			return _ht.erase(key);
		}
		iterator find(const K &key){
			return _ht.find(key);
		}
		//统计通的个数
		size_t bucket_count()const{
			return _ht.bucket_count();
		}
		//计算某个桶中元素个数
		size_t bucket_size(size_t n)const{
			return _ht.bucket_size(n);
		}
		//计算某个K所在桶号
		size_t bucket(const K &key){
			return _ht.bucket(key);
		}
		void clear(){
			_ht.clear();
		}
		void swap(unordered_set<K> &m){
			_ht.swap(m._ht);
		}
		
	private:
		HashBucket<K> _ht;

	};
}
void TestMyUnordered_set(){
	Set::unordered_set<int> m;
	//构造键值对的两种方式：pair结构体
	m.insert(1);
	m.insert(2);

	cout << m.size() << endl;         //获取元素个数
	cout << m.bucket_count() << endl; //获取桶的个数
	cout << m.bucket_size(0) << endl; //获取0号桶中元素个数
	cout << m.bucket(2) << endl;  //求k所在桶的桶号
	//所在桶号和监视中的下标是不一样的

	m.erase(1);
	cout << m.size() << endl;
	m.clear();

}