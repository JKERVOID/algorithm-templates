#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
prim算法：
问题：求最小生成树
复杂度：O(n^2)
过程：
    1、dis[i]=INF，st[i]=0
    2、n次循环：
        a.找到集合外距离最近的点t
        b.st[i]=1
        c.用t更新其他点到集合的距离
原理：贪心
特点：
    1.邻接表、邻接矩阵存图
    2.适合稠密图
*/
 
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll prim(vector<vector<ll>>&edge, int _n){
    //1.
    vector<ll>dis(_n+1,INF);
    vector<bool>st(_n+1,false);
    ll sum=0;
    //2.
    for(int i=0;i<_n;i++){
        //a.
        int t=-1;
        for(int j=1;j<=_n;j++)
            if(!st[j])
              if(t==-1 || dis[t]>dis[j])
                t=j;
        //cout<<t<<" "<<dis[t]<<endl;
        if(i && dis[t]==INF) return -1;//无法建树
        if(i) sum+=dis[t];
        //b.
        st[t]=1;
        //c.
        for(int j=1;j<=_n;j++)
          if(!st[j])
            dis[j]=min(dis[j],edge[t][j]);
    }
    return sum;
}

/*
kruskal
问题：求最小生成树
复杂度：O(mlogm)
过程：
    1、排序所有边
    2、遍历边(u->v:w):
        如果u,v不在同一个集合里，则此边有效(并查集)

原理：贪心
特点：
    1.存所有边
    2.适合稀疏图
*/
struct Edge{//边
    int u,v;
    ll w;
    bool operator< (const Edge &other)const{
        return w<other.w;
    }
};


class UniF{//并查集模版
    public:
        vector<int> f, rank;

        explicit UniF(int size):f(size+1), rank(size+1, 0){
            iota(f.begin(), f.end(), 0);
            //从0开始为f[]赋值
        }

        int find(int a){
            return f[a]==a ? a : (f[a]=find(f[a]));
        }

        bool merge(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            if(rootx == rooty)return 0;//无需合并
            if(rank[rootx] > rank[rooty]) swap(rootx, rooty);
            f[rootx] = rooty;
            if(rank[rootx] == rank[rooty])rank[rooty]++;
            return 1;
        }
};

ll kruskal(vector<Edge>&edge,int _n){
    sort(edge.begin(),edge.end());
    ll sum=0;
    int cnt=0;
    UniF uf(_n);
    for(auto e:edge){
        if(e.u==e.v)continue;
        if(uf.merge(e.u,e.v)){
            cnt++;
            sum+=e.w;
        }
        if(cnt==_n-1)break;
    }
    if(cnt<_n-1)return -1;
    else return sum;

}




//https://www.luogu.com.cn/problem/P3366(需要ll变int)
int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<ll>>edge(n+1,vector<ll>(n+1,INF));
    while(m--){
        ll u,v,w;
        cin >> u>>v>>w;
        edge[u][v]=edge[v][u]=min(w,edge[u][v]);
    }
    ll ans=prim(edge,n);
    cout<<(ans==-1?"orz":to_string(ans));
}


//https://www.luogu.com.cn/record/184226961
int main(){
    int n,m;cin>>n>>m;
    vector<Edge>edge(m);
    for(auto &[u,v,w]:edge)
        cin >>u>>v>>w;
    ll ans=kruskal(edge,n);
    cout<<(ans==-1?"orz":to_string(ans));
}