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
				return v.first;              //δ��ɣ�kֻ�������Σ��������ܽ�������
			}
		};
		//δ��typename֮ǰ���������ὫHashBucket<value,DFKV>::iterator�������еľ�̬��Ա����������
		//��Ϊ��Ա����Ҳ�Ǹ�������::��̨��Ա�������������ʵ�
		//typename�ڴ˵����þ�����ȷHashBucket<value,DFKV>::iterator�е�һ������
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
		//ͳ��ͨ�ĸ���
		size_t bucket_count()const{
			return _ht.bucket_count();
		}
		//����ĳ��Ͱ��Ԫ�ظ���
		size_t bucket_size(size_t n)const{
			return _ht.bucket_size(n);
		}
		//����ĳ��K����Ͱ��
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
	//�����ֵ�Ե����ַ�ʽ��pair�ṹ��
	m.insert(pair<int, string>(1,"a"));
	m.insert(make_pair(2, "b"));

	cout << m.size() << endl;         //��ȡԪ�ظ���
	cout << m.bucket_count() << endl; //��ȡͰ�ĸ���
	cout << m.bucket_size(0) << endl; //��ȡ0��Ͱ��Ԫ�ظ���
	cout << m.bucket(2) << endl;  //��k����Ͱ��Ͱ��
	//����Ͱ�źͼ����е��±��ǲ�һ����

	cout << m[2] << endl; //��һ�����ڵ�k���������k��Ӧ��v
	cout << m.size() << endl;
	cout << m[3] << endl; //���k�����ڣ�����������k��Ĭ�ϵ�v���գ�����һ����ֵ�Բ��뵽map�У�����Ĭ�ϵ�v
	cout << m.size() << endl;
	m.erase(1);
	cout << m.size() << endl;
	m.clear();

}