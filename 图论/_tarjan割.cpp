#include<bits/stdc++.h>

using namespace std;
using ll = long long ;
/*
tarjan：
目标：求割点，割边
概念：
    1. 点双连通图：不存在割点；一个图的极大点双连通图是其点双连通图分量
    2. 边双连通图：不存在割边；一个图的极大边双连通图是其边双连通图分量
    3. dfn: dfs搜索树上的搜索顺序
    4. 返祖边： 搜索树上连接自己祖先的边
    5. 无向图dfs搜索树中只有正常边和返祖边，不存在横叉边
过程：
    1.维护dfn[]代表dfs搜索到顺序
    2.维护low[]表示当前点及其子树通过一条返祖边所能连接到的dfn最小值
    3.dfs遍历
原理：
    对于u的儿子们v，dfn[u]<=low[v], 说明子树中不存在一条非树边连向u上方
    对于u的儿子们v，dfn[u]<low[v], 说明子树中不存在一条非树边连向u->v这条边上方
*/



const int N = 1e5+5;

int n,m,_dfn[N]={0},_low[N],_tot=0,is_cut[N]={0},col[N]={0},col_cnt=0;
vector<int> e[N];
stack<int>st;
void col_merge(int i){
    col[i]=++col_cnt;
    ++col_cnt;
    while(1){
        int cur = st.top();
        if(cur==i)break;
        col[cur]=col_cnt;
        st.pop();
    }
}
void tarjan_point(int i,bool root=1){
    int root_son=0;
    _dfn[i]=_low[i]=++_tot;
    st.push(i);
    for(auto j:e[i]){
        if(!_dfn[j]){//未被赋值则未被遍历，纳入dfs树
            tarjan_point(j,0);
            _low[i]=min(_low[i],_low[j]);
            //通过子孙及子孙通过一条非树边路径可以达到的一个最小dfn
            if(_low[j]>=_dfn[i]&&(!root)) {
                is_cut[i]=1;
                col_merge(i);
            }
            if(root) root_son++;//记录根在dfs树有多少子节点
        }else _low[i]=min(_low[i],_dfn[j]);
    }
    if(root&&root_son>=2) {
        is_cut[i]=1;
        col_merge(i);
    }
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
//https://www.luogu.com.cn/problem/P3388
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