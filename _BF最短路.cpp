#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
bellman-ford
复杂度：O(nm)
步骤：
    1. dis[j]=INF, dis[2]=0;
    2. for i=1 to n
        for each edge (u,v,w)
            dis[v]=min(dis[v], dis[u]+w)
原理：第i次更新保证能找到共经过i条边的最短路
特点：
    1. 可以处理负权边
    2. 可以判断负环(当第n次仍存在被更新的点时，存在负环)
    3. 可以处理包含特定点数量的最短路
    4. 对边的存储方式没有要求
*/

using  TIIL=tuple<int,int,ll>;//(u->v:w)
const ll INF=0x3f3f3f3f3f3f3f3f;

void bellmanford(vector<ll> &dis, vector<TIIL> &edges, int _n, int s=1,int k=-1){
    //1.
    dis.resize(_n+1, INF);
    dis[s]=0;
    //2.
    if(k<0) k=_n-1;//最多经过n-1条边
    while(k--){
        vector<ll>prev(dis);//防止更新顺序影响其他边的更新
        for(auto &e:edges){
            auto [u,v,w]=e;
            dis[v]=min(dis[v], prev[u]+w);
        }
    }
    //由于可能存两个到达不了的边之间被负权边相连的更新
    //所以到达不了的边应使用dis[v]>=INF/2来判断
}

//判断负环
bool bellmanford_judge(vector<ll> &dis, vector<TIIL> &edges, int _n, int s=1){
    //1.
    dis.resize(_n+1, INF);
    dis[s]=0;
    //2.
    for(int i=1;i<=_n;i++){
        vector<ll>prev(dis);//防止更新顺序影响其他边的更新
        for(auto [u,v,w]:edges){
            if(dis[v]<=INF/2){
                //使得只判断从s能到达的负环，若不加，则判断全图是否存在负环
                if(i==_n && dis[v]>prev[u]+w)return true;
            }
            dis[v]=min(dis[v], prev[u]+w);
        }
    }
    return false;
}

/*
优化bellman-ford：SPFA
复杂度：最坏O(nm)
步骤：
    1. dis[j]=INF, dis[2]=0;
    2. st[j]=0, st[1]=1, st数组用于防止队列中出现重复点
    3. while(que.size())
        a.取队首为t, st[t]=0
        b.处理临边
            若被更新且st[v]=0,则入队并设st[v]=1
            
原理：相较于BF，SPFA只会更新有可能被更新的点，因此复杂度更低
特点：
    1. 可以处理负权边
    2. 可以判断负环(记录一下当前点到a需经过几个点，若超出n-1个则存在负环)
    3. 要求存储方式为邻接表
*/

struct SPFA{
    typedef pair<ll,int>PLI;
    const ll INF=0x3f3f3f3f3f3f3f3f;
    vector<vector<PLI>>edge;
    vector<ll>dis;
    vector<bool>st;
    vector<int>fa;
    queue<int>que;
    int _n,_m,s;
    explicit SPFA(int _n,int _m,int s=1):_n(_n),_m(_m),s(s){
        //1.2.
        edge.resize(_n+1);
        dis.resize(_n+1,INF);
        st.resize(_n+1,0);
        fa.resize(_n+1,-1);
        dis[s]=0;
        que.push(s);

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
        while(que.size()){
            //a
            int t=que.front();
            que.pop();
            st[t]=0;
            //b
            for(auto [w,j]:edge[t]){
                if(dis[j] > dis[t] + w){
                    dis[j]=dis[t]+w;
                    fa[j]=t;
                    if(!st[j]){
                        que.push(j);
                        st[j]=1;
                    }
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

//https://www.acwing.com/problem/content/855/
int main(){
    int n,m,k;cin>>n>>m>>k;
    vector<TIIL>edges(m);
    for(auto &[u,v,w]:edges) cin>>u>>v>>w;
    vector<ll>dis;
    bellmanford(dis, edges, n, 1, k);
    cout<<(dis[n]>=INF/2?"impossible":to_string(dis[n]));

}
//https://www.luogu.com.cn/problem/P3371
int main(){
    int n,m,s;cin>>n>>m>>s;
    SPFA spfa(n,m,s);
    for(int i=1;i<=n;i++){
        cout<<(spfa.query(i)==-1?2147483647:spfa.query(i))<<' ';
    }
    
}