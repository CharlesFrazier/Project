#include<list>
#include<string>
#include<string.h>
#include "RBTree.h"
namespace sk
{
	template<class K, class V>
	class mymap
	{
	public:
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::_iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}
		iterator find(const K& key)
		{
			return _t.Find(key);
		}
		V& operator[](const K& key)
		{
			auto ret = (_t.Insert(make_pair(key, V()))).first;
			return ret->second;
		}
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};
}

class Map{
private:
    sk::mymap<string,int> item;
    int size_;
public:
    Map(); // 构造函数，构造一个空映射表，初始化数据成员
   ~Map(); // 析构函数，释放申请的内存空间

   bool insert(const string& key, int value);

   bool erase(const string &key);

   bool find(const string &key);

   int & operator[](const string &key);

   int size() const;
};
