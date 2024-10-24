#include<bits/stdc++.h>
using namespace std;
using ll =long long;

/*
匈牙利算法：
复杂度：O(nm), 平均随机数据复杂度接近O(n)
过程：
    1.维护match[]作为左部点的匹配点
    2.st[]作为左部点本轮是否被访问
    3.遍历右部点，记为i：
        A.清空st.clear()
        B.寻找匹配的左部点，记为dfs(i)：
            遍历i的相邻点(左部点)，记为j：
                a.如果j未被匹配，则match[j]=i
                b.如果j被匹配则询问match[j]能否解配
                    递归执行dfs(match[j])
*/

class Hungarian{
public:
    vector<vector<int>>edge;
    vector<int>match;
    vector<bool>st;
    int n,m,cnt=0;

    explicit Hungarian(int n,int m,vector<vector<int>>&edge):n(n),edge(edge){
        match.resize(m+1,0);
        st.resize(m+1,0);
        for(int i=1;i<=n;i++){
            fill(st.begin(),st.end(),0);
            if(dfs(i))cnt++;
        }
    }

    bool dfs(int i){
        for(auto j:edge[i]){
            if(!st[j]){
                st[j]=1;
                if(match[j]==0 || dfs(match[j])){
                    match[j]=i;
                    return 1;
                }
            }
        }
        return 0;
    }
};

//https://www.luogu.com.cn/problem/P3386
int main(){
    int n,m,e;
    vector<vector<int>>edge;
    cin >> n>>m>>e;
    edge.resize(n+1);
    while(e--){
        int u,v;
        cin >> u >>v;
        edge[u].push_back(v);
    }
    Hungarian hgr(n,m,edge);
    cout<<hgr.cnt;
}
