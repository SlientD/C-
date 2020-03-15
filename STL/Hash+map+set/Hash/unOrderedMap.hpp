#pragma once
#include "hashBuckt.hpp"
#include "common.hpp"
namespace Map{
	template<class K,class V>
	class unordered_map{
		typedef pair<K, V> value;
		class DFKV{		
		public:
			K operator()(const value &v){
				return v.first;              //未完成：k只能是整形，这样才能进行运算
			}
		};
		//未加typename之前，编译器会将HashBucket<value,DFKV>::iterator当做类中的静态成员变量来处理
		//因为成员变量也是根据类型::讲台成员变量名字来访问的
		//typename在此的作用就是明确HashBucket<value,DFKV>::iterator中的一种类型
		typename typedef HashBucket<value,DFKV>::iterator iterator;
	public:
		unordered_map()
			:_ht()
		{
				
		}
		~unordered_map(){
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
		pair<iterator,bool> insert(const value &v){
			return _ht.insert(v);
			
		}
		size_t erase(const K &key){
			return _ht.erase(value(key, V()));
		}
		iterator find(const K &key){
			return _ht.find(value(key, V()));
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
			return _ht.bucket(value(key, V()));
		}
		void clear(){
			_ht.clear();
		}
		void swap(unordered_map<K, V> &m){
			_ht.swap(m._ht);
		}
		V& operator[](const K &key){
			return (*(insert(value(key, V())).first)).second;

		}
	private:
		HashBucket<value,DFKV> _ht;

	};
}
void TestMyUnordered_map(){
	Map::unordered_map<int, string> m;
	//构造键值对的两种方式：pair结构体
	m.insert(pair<int, string>(1,"a"));
	m.insert(make_pair(2, "b"));

	cout << m.size() << endl;         //获取元素个数
	cout << m.bucket_count() << endl; //获取桶的个数
	cout << m.bucket_size(0) << endl; //获取0号桶中元素个数
	cout << m.bucket(2) << endl;  //求k所在桶的桶号
	//所在桶号和监视中的下标是不一样的

	cout << m[2] << endl; //给一个存在的k，返回与该k对应的v
	cout << m.size() << endl;
	cout << m[3] << endl; //如果k不存在，会用所给的k与默认的v（空）构建一个键值对插入到map中，返回默认的v
	cout << m.size() << endl;
	m.erase(1);
	cout << m.size() << endl;
	m.clear();

}