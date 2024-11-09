#include<bits/stdc++.h>

using namespace std;
using ll = long long ;
/*
tarjan：
目标：求有向图强联通分量
过程：
    1.维护dfn[]代表dfs搜索到顺序
    2.维护一个栈来存储待处理的点
    2.维护low[]表示当前边点其子树通过一条返祖边或横叉边所能连接到的dfn最小值
    3.dfs遍历：
        a. 第一次访问某点就将其入栈
        b.返回后若dfn[u]==low[u]，出栈到当前点为止，这些点构成一个强连通分量
原理：
    dfn[u]==low[u]时，u就是这个强连同分量中最高的点
    因为任意的环返祖或横叉时，构成强连通分量，同时dfn减小
*/



const int N = 1e5+11;

int n,m,_dfn[N]={0},_low[N],_tot=0,ans=0,_top=0,_vis[N]={0},_st[N],col[N]={0};
//同一个联通分类有相同的num
vector<int> e[N];
void tarjan(int i){
    _dfn[i]=_low[i]=++_tot;
    _st[++_top]=i;
    _vis[i]=1;//记录在栈
    for(auto j:e[i]){
        if(!_dfn[j]){//未被赋值则未被遍历，纳入dfs树
            tarjan(j);
            _low[i]=min(_low[i],_low[j]);
            //通过子孙及子孙通过一条非树边路径可以达到的一个最小dfn
        }else if(_vis[j])_low[i]=min(_low[i],_dfn[j]);
    }
    if(_dfn[i]==_low[i]) {
        ans++;
        int cur;
        do{
            cur=_st[_top--];
            _vis[cur]=0;
            col[cur]=ans;
        }while(i!=cur);
    }
}//被访问过的点也显然都在属于root的连通分量中


//https://www.luogu.com.cn/problem/P3388
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        if(u!=v)e[u].push_back(v);
    }

    for(int i=1;i<=n;i++) if(!_dfn[i])tarjan(i);


    vector<set<int>>a(ans+1);
    for(int i=1;i<=n;i++)a[col[i]].insert(i);
    cout<<ans<<endl;
    sort(a.begin()+1,a.end(),[](set<int>x,set<int>y){
        return *(x.begin())<*(y.begin());
    });
    for(int i=1;i<=ans;i++){
        for(auto j:a[i])cout<<j<<" ";
        cout<<endl;
    }
    


}