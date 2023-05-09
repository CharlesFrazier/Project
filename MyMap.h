#include<list>
#include<string>
#include<string.h>
#include "RBTree.h"
//99999为空；
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
	//private:
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};
}
	// void MapTest()//hide();
	// {
	// 	mymap<string, int> m;
		
	// 	m.insert(make_pair("1", 1));
	// 	m.insert(make_pair("1", 1));
	// 	m.insert(make_pair("1", 1));
	// 	m.insert(make_pair("1", 1));
	// 	m.insert(make_pair("1", 1));
	// 	m["5"] = 5;
	// 	m["6"];
	// 	mymap<string, int> m2(m);
	// 	mymap<string, int> m3 = m2;
	// 	mymap<string, int>::iterator it = m.begin();
	// 	cout << "map: " << endl;
	// 	for (auto& e : m3)
	// 	{
	// 		cout << e.first << ":" << e.second << endl;
	// 	}
	// }

class Map{
private:
    sk::mymap<string,int> item;
	int size_;
public:
    Map(); // 构造函数，构造一个空映射表，初始化数据成员
   ~Map(); // 析构函数，释放申请的内存空间

   bool insert(const string& key, int value); // 插入键值到映射表中
   // 成功插入返回true；若对应键已存在旧值，插入失败，返回false

   bool erase(const string &key); // 删除该键的键值对
   // 成功删除返回true；若不存在对应键的键值对，删除失败，返回false

   bool find(const string &key); // 返回映射表中是否含有对应键的键值对

   int & operator[](const string &key); // 数组下标访问操作符重载
   // 可以通过下标访问的方式直接用键得到值的引用
   // 需要注意的是，如果用下标访问的方式访问了不存在的key，你需要为该key创建一个键值对
   // 此法创建的值初始为0，你需要返回该值的引用

   int size() const; // 返回映射表中当前记录的键值对总数
};