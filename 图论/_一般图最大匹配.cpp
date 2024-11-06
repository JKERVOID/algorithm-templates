#include<bits/stdc++.h>
using namespace std;
using ll =long long;

/*
带花树算法：
问题：一般图最大匹配
时间复杂度：O(nmα(n))
原理：bfs匈牙利+奇环缩点
过程：
    bfs过程中黑白染色，如果遇到已搜点，通过染色判断是否是奇环，如果是：
        1、lca求公共祖先
        2、环上所有点染黑，并把所有点入队搜索，相当于缩成了一个点
           > 因为对于任何一条进入奇环的出去的增广路，都可以对应一条经过花的增广路
           > 同时一条经过花的增广路，也可以对应一条进入奇环出去的增广路
*/
class Blossom{
public:
    int ans;
    queue<int>q;
    vector<vector<int>>&e;
    vector<int>pre,match,col,fa;
    
    int find(int a){return fa[a]==a ? a : (fa[a]=find(fa[a]));}
    
    void aug(int v){//从v点开始修改増广路 
        int t;
        while(v){
            t=match[pre[v]];//临时记录下一次的v
            match[v]=pre[v];
            match[pre[v]]=v;
            v=t; 
            //cout<<v<<endl;
        }
    }

    int vis_cnt=0;
    vector<int>vis;//int使得不用每次都清空
    int lca(int x,int y){//寻找两个节点的总花根 
        vis_cnt++;
        while(1){
            if(x){
                x=find(x);
                if(vis[x]==vis_cnt)return x;
                vis[x]=vis_cnt;
                if(match[x])x=pre[match[x]];
                else x=0;
            }
            swap(x,y);
        }
    }

    void shrink(int u,int v,int r){
        while(find(u)!=r)//当已达到总花根，说明缩花任务完成 
        {
            pre[u]=v;//建立反向pre，保证増广路
            v=match[u];
            if(col[v]==2){col[v]=1;q.push(v);}//花内所有v，都应以u身份向外増广 
            //if(col[u]==2){col[u]=1;q.push(u);}
            if(find(u)==u)fa[u]=r;//如果某一点为分花根，将其合并到总花根上 
            if(find(v)==v)fa[v]=r;
            u=pre[v];//切换操作对象 
        }
    }

    bool bfs(int s){
        q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(auto v:e[u]){//枚举可达节点
                if(find(u)==find(v))continue;//该环已被缩成一点，不必处理 
                if(col[v]==2)continue;//偶环
                if(col[v]==1){//奇数环，需要将花缩成花根一点  
                    int r=lca(u,v);//寻找lca，即总花根 
                    shrink(u,v,r);//分别从两个方向，建立反向pre，保证花内部増广路正确性 
                    shrink(v,u,r);
                }else{//未遍历过，即遍历路径仍为树结构 
                    pre[v]=u;//记录前驱 
                    if(!match[v]){aug(v);return 1;}//找到増广路终点，进行増广
                    else{
                        col[v]=2;
                        col[match[v]]=1;
                        q.push(match[v]);
                    }//v点已有匹配，令u=match[v] 
                }
            }
        }
        return 0;//増广失败 
    }
    explicit Blossom(vector<vector<int>>&e, int n):e(e){
        pre.resize(n+1,0);
        match.resize(n+1,0);
        col.resize(n+1,0);
        fa.resize(n+1,0);
        vis.resize(n+1,0);
        ans=0;
        for(int i=1;i<=n;i++){
            for(int i=1;i<=n;i++) pre[i]=col[i]=0,fa[i]=i;
            while(!q.empty()) q.pop();
            if(!match[i]){
                if(bfs(i))
                    ans++;
            }
        }
        
    }

};

//https://uoj.ac/problem/79
int main(){
    int n,m;cin >> n>>m;
    vector<vector<int>>e;
    e.resize(n+1);
    while(m--){
        int u,v;
        cin >>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    Blossom b(e,n);
    cout<<b.ans<<endl;
    for(int i=1;i<=n;i++)
        cout<<b.match[i]<<" ";
}