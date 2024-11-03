#include<bits/stdc++.h>
using namespace std;
using ll =long long;

/*
树上带权最大独立集：
题意：在树上选择若干两两没有邻边的点，使得所有点的权重和最大
[*]特殊说明：
    1、权值为1的书上带权最大独立集，就是树上最大独立集
    2、树上最大独立集就是树上最大图匹配
时间复杂度：O(n)
原理：
1. 用dp[i][1/0]表示此点是否被选情况下的子树最大权，j为i的子树
2. 转移方程：
    1. dp[i][0]=Σmax{dp[j][0],dp[j][1]}
    2. dp[i][1]=w[i]+Σdp[j][0]
*/
using PII=struct{int y,n;};
vector<PII>dp;//用dp数组记忆结果，dfs负责遍历
vector<int>w;
vector<vector<int>>son;

void dfs(int i){
    dp[i].y=w[i];
    dp[i].n=0;
    for(auto j:son[i]){
        dfs(j);
        dp[i].n+=max(dp[j].n,dp[j].y);
        dp[i].y+=dp[j].n;
    }
}

int main(){
    int n;cin >> n;
    vector<bool>not_root(n+1,true);
    dp.resize(n+1);
    w.resize(n+1);
    son.resize(n+1);
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        son[v].push_back(u);
        not_root[u]=false;
    }
    for(int i=1;i<=n;i++){
        if(not_root[i]){
            dfs(i);
            cout<<max(dp[i].n,dp[i].y);
            break;
        }
    }
}