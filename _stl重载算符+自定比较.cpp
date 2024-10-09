#include<bits/stdc++.h>
using namespace std;
#define ll long long

//优先队列(大根堆)
typedef std::pair<int, ll> PIL;
priority_queue<PIL, vector<PIL>, function<bool(PIL, PIL)>> 
    pq_max([](const PIL& a, const PIL& b) 
        {return a.second < b.second;}
    );

struct PII{int l,r;};
struct Compare {
    bool operator()(const PII& a, const PII& b) {
        return a.r > b.r; 
        // 若 a.r 大于 b.r，则 a 在堆中的位置应该比 b 低
    }
};priority_queue<PII, std::vector<PII>, Compare> pq;

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


    