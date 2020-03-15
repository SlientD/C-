#pragma once
#include "hashBuckt.hpp"
#include "common.hpp"
namespace Set{
	template<class K>
	class unordered_set{
		
		
		//δ��typename֮ǰ���������ὫHashBucket<value,DFKV>::iterator�������еľ�̬��Ա����������
		//��Ϊ��Ա����Ҳ�Ǹ�������::��̨��Ա�������������ʵ�
		//typename�ڴ˵����þ�����ȷHashBucket<value,DFKV>::iterator�е�һ������
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
	//�����ֵ�Ե����ַ�ʽ��pair�ṹ��
	m.insert(1);
	m.insert(2);

	cout << m.size() << endl;         //��ȡԪ�ظ���
	cout << m.bucket_count() << endl; //��ȡͰ�ĸ���
	cout << m.bucket_size(0) << endl; //��ȡ0��Ͱ��Ԫ�ظ���
	cout << m.bucket(2) << endl;  //��k����Ͱ��Ͱ��
	//����Ͱ�źͼ����е��±��ǲ�һ����

	m.erase(1);
	cout << m.size() << endl;
	m.clear();

}