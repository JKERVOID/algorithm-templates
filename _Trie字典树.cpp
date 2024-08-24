#include<bits/stdc++.h>
using namespace std;
using ll = long long ;    
/*
Trie树：高效存储和查询字符串集合
时间复杂度：
    单次插入：O(size)，size为字符串长度
    单次查询：O(size)，size为字符串长度

*/
struct Trie{
    int _M,_N;//注意：_M表示字符集大小，_N表示节点数，节点数=单词书*单词长度
    vector<vector<int>>_son;
    vector<int>_cnt;
    int _tot;
    explicit Trie(int _N=1e5+5,int _M = 26):_M(_M),_N(_N){
        _son.resize(_N,vector<int>(_M,0));
        _cnt.resize(_N,0);
        _tot = 0;//0表示根节点，也是空节点
    };

    void insert_str(string &s,//默认取asc码值
        function<int(char)>f=[](char c){
            return c-'a';
        }
    ){
        int p = 0;
        for(auto c:s){
            int u = f(c);
            if(!_son[p][u])_son[p][u] = ++_tot;
            p = _son[p][u];
        }
        _cnt[p]++;
    }

    int query_str(string &s,
        function<int(char)>f=[](char c){
            return c-'a';
        }
    ){
        int p = 0;
        for(auto c:s){
            int u = f(c);
            if(!_son[p][u])return 0;
            p = _son[p][u];
        }
        //if(_cnt[p])_cnt[p]++;//用于应对洛谷P2580
        return _cnt[p];
    }
    //数字情况的trie
    /*
    int query_int(vector<int> &nums,
        function<int(int)>f=[](int i){
            return i;
        }
    ){
        int p = 0;
        for(auto i:nums){
            int u = f(i);
            if(!_son[p][u])return 0;
            p = _son[p][u];
        }
        return _cnt[p];
    }
    
    void insert_int(vector<int> &nums,//默认取数字值
        function<int(int)>f=[](int i){
            return i;
        }
    ){
        int p = 0;
        for(auto i:nums){
            int u = f(i);
            if(!_son[p][u])_son[p][u] = ++_tot;
            p = _son[p][u];
        }
        _cnt[p]++;
    }
    */
};

int main(){//https://www.luogu.com.cn/problem/P2580
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;  cin>>n;
    Trie t(5e5+5,26);
    string s;
    for(int i=0;i<n;i++){
        cin >> s;
        t.insert_str(s);
    }
    int m,q;  cin>>m;
    for(int i=0;i<m;i++){
        cin >> s;
        q = t.query_str(s);
        if(!q) cout<<"WRONG"<<endl;
        else if(q==2)cout<<"OK"<<endl;
        else cout<<"REPEAT"<<endl;
        //cout<<q<<endl;
    }
    
}