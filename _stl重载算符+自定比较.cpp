#include<bits/stdc++.h>
using namespace std;
#define ll long long

//优先队列
struct p_MyStruct {
    int value;
    double priority;
    // 构造函数
    p_MyStruct(int v, double pr) : value(v), priority(pr) {}
    // 重载小于运算符，定义优先队列中的顺序
    bool operator<(const p_MyStruct &other) const {//类内重载该运算符隐式传入了this
        return priority < other.priority;
    }
};priority_queue<p_MyStruct> pq_max;// 创建一个默认的优先队列（最大值优先）

//双关键字map
struct m_ComparePair {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first < b.first;
    }
};map<pair<int, int>, int, m_ComparePair> mp1;

//结构体map
struct m_MyStruct {
    int key1;
    std::string key2;

    // 重载小于运算符，定义map中的顺序
    bool operator<(const m_MyStruct& other) const {
        return key1 < other.key1 || (key1 == other.key1 && key2 < other.key2);
    }

    // 重载等于运算符，用于查找操作
    bool operator==(const m_MyStruct& other) const {
        return key1 == other.key1 && key2 == other.key2;
    }
};map<m_MyStruct, int> mp2;

//自定义结构体排序
struct s_MyStruct { 
    int value;
    string s;
    s_MyStruct(int v, string s) : value(v), s(s) {}
};vector<struct s_MyStruct> s; // 自定义结构体排序
void sort_s(){
    sort(s.begin(), s.end(), 
        [](const s_MyStruct& a, const s_MyStruct& b){
            return a.value < b.value;
        }
    );
}

//自定义hash的map
struct m_MyHash {
    std::size_t operator()(const std::string& s) const {
        std::size_t hash = 0;
        for (char c : s) {
            hash = 31 * hash + c;
        }
        return hash;
    }
};unordered_map<std::string, int, m_MyHash> myUnorderedMap;


    