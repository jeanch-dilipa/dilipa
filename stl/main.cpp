#include <QCoreApplication>
#include <algorithm>        /*stl算法在std中定义，包含于algorithm/numeric中*/
#include <numeric>
#include <iostream>
#include <QDebug>
#include <deque>
#include <map>
#include <utility>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    /*序列式容器*/
    std::vector<int> vec;
    for(int i = 0; i < 10; i++)
    {
//        vec.push_back(i);
        vec.emplace_back(i);        /*效率更高，直接在vec创建元素;push_back先创建再移动/拷贝*/
    }

    std::remove(vec.begin() + 1, vec.end() - 2, 3);

    std::vector<int>::const_reverse_iterator i;
    for(i = vec.crbegin(); i < vec.crend(); i++)
    {
        qDebug() << *i;
    }

    vec.resize(1000);

    vec[500] = 99;
    vec.clear();
    vec.resize(20, 10);

//    vec.begin();
//    vec.end();
//    vec.rbegin();
//    vec.rend();
//    vec.crbegin();
//    vec.crend();
//    vec.assign();
    vec.max_size();
    vec.size();
    vec.capacity();
    vec.empty();
    vec.resize(1000);
    vec.shrink_to_fit();
//    vec.emplace(21);
//    vec.emplace_back();

    std::array<int, 5> arr{1, 2, 3, 4, 5};
    qDebug() << get<3>(arr) << arr.at(3) << arr[3];
//    for(int j = 0; j < arr.size(); j++)
//    {
//        qDebug() << get<j>(arr);      /*get<T>()模板需要在编译时就确定T的值*/
//    }
    int total = 0;
    foreach(auto&& value, arr)
    {
        total += value;
    }

    qDebug() << total;

    int value[] = {1, 2, 3, 4 ,5 ,6};
    std::vector<int> value1{1, 2, 3, 4 ,5 ,6};
    std::vector<int> value2(value, value + 2);
    std::vector<int> value3(std::begin(value1) + 1, std::end(value1) - 1);

    value3.insert(value3.begin() + 2, 15);
    value3.insert(value3.end(), 2, 49);
    value3.insert(value3.end(), value1.begin() + 1, value1.end() - 2);
    value3.insert(value3.end() - 5, {10, 9, 8, 7, 6, 5, 4, 3, 2, 1});

    std::deque<int> deque;
    std::list<int> list;
//    list.unique();  /*去重*/
//    list.reverse(); /*翻转*/
//    list.merge();   /*合并*/
//    list.sort();    /*排序*/
    list.insert(list.begin(), value3.begin(), value3.end() - 1);
    list.remove_if([](int num){return num > 5;});
    list.unique();
    list.sort();
    for(auto&& v: list)
    {
        qDebug() << v;
    }

//    static_cast<>();
//    const_cast<>();
//    reinterpret_cast<>();
//    dynamic_cast<>();
    /*关联式容器*/
    std::map<int, string, std::greater> map;
    map[0] = "快递师傅";
    map[1] = "就很舒服";
    map[2] = "蓝惠首府";
    map.insert(make_pair(3, "suodhf"));
    for(std::map<int, string>::iterator m = map.begin(); m != map.end(); m++)
    {
        std::cout << "一:" << m->first << m->second;/*使用qDebug将报错*/
    }

    std::pair<string, string> pair(make_pair("内双击看到过", "就开始了恢复道格拉斯"));
    std::cout << pair.first << pair.second;

    std::map<std::string, int>newMap(disMap());         /*将使用移动构造函数*/

    return a.exec();
}

std::map<std::string,int> disMap() {
    std::map<std::string, int>tempMap{ {"C语言教程", 10}, {"STL教程", 20} };
    return tempMap;
}

