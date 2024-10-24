#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
朴素Dijkstra：
单源正权最短路，O(n^2)
步骤：
    1、dis[i]=INF，dis[1]=0,
    2、初始化已确定最短距离的set,set.empty()
    3、循环n次：(每次循环可以确定一个点的最短路)
        a. 找到不在s中的，距离源最近的点
        b. s.insert(t)
        c. 遍历与t相邻的点，以更新其他点：
            检查是否存在dis[x]>g[x][t]+dis[t]
原理：显然可以保证每个t都已经是最短路了
特点：
    由于复杂度不涉及边，所以适合稠密图
    由于基于贪心策略，存在负权边时，无法保证每次循环可以确定一个点的最短路
*/
 
const int N=100;

class Dijkstra{
public:
    const ll INF=0x3f3f3f3f3f3f3f3f;
    int _n,_m,s;
    ll edge[N][N],dis[N];
    int fa[N];//路径
    bool st[N];//s
    explicit Dijkstra(int _n,int _m,int s=1):_n(_n),_m(_m),s(s){
        for(int i=1;i<=_n;i++){
            //1
            dis[i]= i==s?0:INF;
            //2
            st[i]=0;
            fa[i]=-1;
            for(int j=1;j<=_n;j++)
                edge[i][j]= i==j? 0:INF;
        }
        //输入+处理重边与自环
        while(_m--){
            ll a,b,c;
            cin >> a >> b >> c;
            edge[a][b]=min(edge[a][b],c);
            //无向图
            //g[b][a]=min(g[b][a],c);
        }
        //3
        for(int i=1;i<=_n;i++){
            //a
            int t=-1;
            for(int j=1;j<=_n;j++){
                if(!st[j])
                    if(t==-1 || dis[j]<dis[t])
                        t=j;
            }
            //b
            st[t]=1;
            //c
            for(int j=1;j<=_n;j++){
                if(dis[j]>dis[t]+edge[t][j]){
                    dis[j]=dis[t]+edge[t][j];
                    fa[j]=t;//处理路径
                }
            }
        }
    }

    ll query(int x){return dis[x]==INF?-1:dis[x];}

    vector<int> route(int x){
        //查询路径
        vector<int> ro;
        if(query(x)==-1)return ro;
        while(1){
            ro.push_back(x);
            if(x==s)break;
            x=fa[x];
        }
        reverse(ro.begin(),ro.end());
        return ro;
    }
};


/*
堆优化Dijkstra：
单源正权最短路，O(nlogm)
步骤：
    1、dis[i]=INF，dis[1]=0,
    2、初始化已确定最短距离的set,set.empty()
    3、初始化一个堆heap，存储4.c更新出的{dis[j],j}
    4、循环n次：(每次循环可以确定一个点的最短路)
        a. 用heap找到不在s中的距离源最近的点:O(1)
        b. s.insert(t):O(1)
        c. 遍历与t相邻的点，以更新其他点,
            检查是否存在dis[x]>g[x][t]+dis[t]
           (此步骤用邻接表相当于检查所有边:O(m)
            随后入堆：O(logn))

原理：每个点显然都入堆其入度次，所有点入度之和即为边数量
特点：复杂度包含logm,适合稀疏图
*/

struct Dij_heap{
    const ll INF=0x3f3f3f3f3f3f3f3f;
    typedef pair<ll,int>PLI;
    vector<vector<PLI>>edge;
    vector<ll>dis;
    vector<bool>st;
    vector<int>fa;
    priority_queue<PLI, vector<PLI>, greater<PLI>> heap;
    int _n,_m,s;
    explicit Dij_heap(int _n,int _m,int s=1):_n(_n),_m(_m),s(s){
        //1.2.3.
        edge.resize(_n+1);
        dis.resize(_n+1,INF);
        st.resize(_n+1,0);
        fa.resize(_n+1,-1);
        dis[s]=0;
        heap.push({0,s});

        //输入+处理重边与自环
        while(_m--){
            ll a,b,c;
            cin >> a >> b >> c;
            if(a!=b){
                edge[a].push_back({c,b});
                //无向图
                //edge[b].push_back({c,a});
            }
        }

        //3
        while(heap.size()){
            //a
            int t=heap.top().second;
            heap.pop();
            if(st[t])continue;
            //b
            st[t]=1;
            //c
            for(auto [w,j]:edge[t]){
                if(dis[j] > dis[t] + w){
                    dis[j]=dis[t]+w;
                    fa[j]=t;
                    heap.push({dis[j],j});//m条边，heap最大size为m
                }
            }
        }
    }
    ll query(int x){return dis[x]==INF?-1:dis[x];}

    vector<int> route(int x){
        //查询路径
        vector<int> ro;
        if(query(x)==-1)return ro;
        while(1){
            ro.push_back(x);
            if(x==s)break;
            x=fa[x];
        }
        reverse(ro.begin(),ro.end());
        return ro;
    }
};

//https://www.luogu.com.cn/record/180880249
int main(){
    int n,m,s;  
    cin>>n>>m>>s;
    Dij_heap dij(n,m,s);
    for(int i=1;i<=n;i++){
        cout<<dij.query(i)<<" ";
    }
}
