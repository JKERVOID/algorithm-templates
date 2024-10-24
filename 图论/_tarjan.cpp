#include<bits/stdc++.h>

using namespace std;
using ll = long long ;
//求割点，割边
//https://www.luogu.com.cn/problem/P3388

const int N = 1e5+5;

int n,m,_dfn[N]={0},_low[N],_tot=0,is_cut[N]={0};
vector<int> e[N];
void tarjan_point(int i,bool root=1){
    int root_son=0;
    _dfn[i]=_low[i]=++_tot;
    for(auto j:e[i]){
        if(!_dfn[j]){//未被赋值则未被遍历，纳入dfs树
            tarjan_point(j,0);
            _low[i]=min(_low[i],_low[j]);
            //通过子孙及子孙非树边/非来时路径可以达到的一个最小dfn
            if(_low[j]>=_dfn[i]&&(!root)) is_cut[i]=1;
            if(root) root_son++;//记录根在dfs树有多少子节点
        }else _low[i]=min(_low[i],_dfn[j]);
        //对于返祖边，使用祖先low值会出错，使用dfn足够满足条件
        //且任意非树边都是返祖边
    }
    if(root&&root_son>=2) is_cut[i]=1;
}//被访问过的点也显然都在属于root的连通分量中

vector<pair<int,int>> bridge;
void tarjan_edge(int i,int p=-1){
    _dfn[i]=_low[i]=++_tot;
    for(auto j:e[i]){
        if(j==p) continue;
        if(!_dfn[j]){
            tarjan_edge(j,i);
            _low[i]=min(_low[i],_low[j]);
            if(_low[j]>_dfn[i] ) bridge.push_back({i,j});
            //比割点多了一边，因此dfn也更大
        }else _low[i]=min(_low[i],_dfn[j]);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    /*
    for(int i=1;i<=n;i++) if(!_dfn[i]) tarjan_point(i);
    //输入有多个连通分量，需要多次tarjan
    int ans=0;
    for(int i=1;i<=n;i++) ans+=is_cut[i];
    cout<<ans<<endl;
    for(int i=1;i<=n;i++) if(is_cut[i]) cout<<i<<" ";
    */
    ///*
    for(int i=1;i<=n;i++) if(!_dfn[i]) tarjan_edge(i);
    for(auto i:bridge) cout<<i.first<<" "<<i.second<<endl;
    ///*
}