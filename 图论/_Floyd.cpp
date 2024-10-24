#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
Floyed
复杂度：O(n^3)
问题：多源汇最短路问题
原理：
    d[k,i,j]:=从i只经过1~k到达j的最短距
    转移方程：d[k,i,j]=max(d[k-1,i,j], d[k-1,i,k]+d[k-1,k,j])
    优化一维：d[i,j]=min(d[i,j],d[i,k]+d[k,j])
特点：
    可以处理负权但无法处理负环
    需要邻接矩阵存储
*/
const int N=210;
const ll  INF=0x3f3f3f3f3f3f3f3f;
void floyd(vector<vector<ll>>& d,int _n){
    for(int k=1;k<=_n;k++)
     for(int i=1;i<=_n;i++)
      for(int j=1;j<=_n;j++)
        d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    //存在负权边的时候，无解情况处理：
    //使用d[v]>=INF/2来判断
}

int main(){
    int n,m;
    cin >> n>>m;
    vector<vector<ll>> edge;
    edge.resize(n+1);
    for(int i=1;i<=n;i++){
        edge[i].resize(n+1,INF);
        edge[i][i]=0;
    }
    while(m--){
        //处理重边与自环
        ll u,v,w;
        cin >>u >>v >>w;
        edge[u][v]=min(edge[u][v],w);
        edge[v][u]=edge[u][v];
    }
    floyd(edge,n);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<edge[i][j]<<" ";
        }cout<<endl;
    }
}
