#include"MyMap.h"

Map::Map()
{
    size_=0;
}

Map::~Map()
{
    item._t.~RBTree();
}
//==null找不到；==99999为空；
bool Map::insert(const string& key, int value) {
    if(item.find(key)!=nullptr&&item[key]!=99999)return false;
    else if(item.find(key)!=nullptr&&item[key]==99999)
    {
        size_++;
        item[key] = value;
        return true;
    }
    else
    {
        item.insert(make_pair(key, value));
        size_++;
        return true;
    }
}

bool Map::find(const string& key) {
    if(item.find(key)!=nullptr&&item[key]!=99999) return true;
    else return false;
}

bool Map::erase(const string& key) {
    if(item.find(key)!=nullptr&&item[key]!=99999)
    {
        size_--;
        item[key]=99999;
        return true;
    }
    else
    {
        return false;
    }
}

int & Map::operator[](const string &key) {
    if(item.find(key)!=nullptr&&item[key]!=99999)
    {
        return item[key];
    }
    else if(item.find(key)!=nullptr&&item[key]==99999)
    {
        size_++;
        item[key]=0;
        return item[key];
    }
    else
    {
        size_++;
        item.insert(make_pair(key,0));
        return item[key];
    }
    
}

int Map::size() const { return size_; }



int main()
{
    
Map id2grade;
// 插入两个键值对
id2grade.insert("202200001", 99);
id2grade.insert("202200002", 98);
std::cout << id2grade.size() << std::endl; // 2
// 删除一个已经存在的键："202200002"后查找不到改键；删除一个不存在的键；
std::cout << id2grade.erase("202200002") << std::endl; // 1(true)
std::cout << id2grade.find("202200002") << std::endl; // 0(false)
std::cout << id2grade.erase("202200000") << std::endl; // 0(false)
std::cout << id2grade.size() << std::endl; // 1
// 用下标访问方式查询键对应的值，包含已存在的键值对和不存在的键值对
// 注意，用下标访问的方式访问了不存在的key，你需要为该key创建一个键值对，值的初始值为0
std::cout << id2grade["202200001"] << std::endl; // 99
std::cout << id2grade["202200002"] << std::endl; // 0
std::cout << id2grade.find("202200002") << std::endl; // 1(true)
std::cout << id2grade.size() << std::endl; // 2
// 用insert插入键值对，但该键已存在，插入失败，原有的键值对不变
std::cout << id2grade.insert("202200002", 100) << std::endl; // 0(false)
std::cout << id2grade["202200002"] << std::endl; // 0
std::cout << id2grade.size() << std::endl; // 2
// 用下标访问方式修改键值对
id2grade["202200002"] = 95;
id2grade["DZ00001"] = 100;
std::cout << id2grade["202200002"] << std::endl; // 95
std::cout << id2grade["DZ00001"] << std::endl; // 100
std::cout << id2grade.size() << std::endl; // 3
}
