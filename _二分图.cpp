#include<bits/stdc++.h>
using namespace std;
using ll =long long;

/*
染色法判定二分图：
原理：二分图<==>图中不含奇数环<==>可二染色
过程: dfs或bfs过程中对于当前的节点的子节点染反色
特点：邻接表存图
*/
vector<vector<int>>edge;
vector<int>color;//0未染色; 1、2为两种颜色
int n;
bool dfs(int u, int c){
    color[u]=c;
    for(auto v:edge[u]){
        if(!color[v]){
            if(!dfs(v,3-c))return false;
        }else if(color[v]==c)
            return false;
    }
    return true;
}
bool colorBipartite(int _n){
    color.resize(_n+1,0);
    for(int i=1;i<=_n;i++){
        if(!color[i])
            if(!dfs(i,1))
                return false;
    }
    return true;
}

//https://www.luogu.com.cn/problem/UVA10004
int main(){
    int n,m;
    while(1){
        cin>>n>>m;
        if(n==0)break;
        color.clear();
        edge.clear();
        edge.resize(n+1);
        while(m--){
            int u,v;
            cin >>u>>v;
            u++,v++;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        if(colorBipartite(n))cout<<"BICOLORABLE."<<endl;
        else cout<<"NOT BICOLORABLE."<<endl;
    }
}
