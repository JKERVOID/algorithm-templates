#include<bits/stdc++.h>
#define ll long long
#pragma GCC optimize(3)
using namespace std;

//01背包
ll _01pack(int n, int m, int v[], ll w[]){
    ll f[m+1]={0};
    for(int i=1;i<=n;i++){
        /*    
        for(int j=0;j<=m;j++){
            f[i][j]=f[i-1][j];
            if(j>=v[i])
                f[i][j]=max(f[i][j],f[i-1][j-v[i]]+w[i]);
        }
        *///rollback:
        for(int j=m;j>=v[i];j--)
            f[j]=max(f[j],f[j-v[i]]+w[i]); 
    }
    return f[m];
}
//完全背包
ll fullpack(int n, int m, int v[], ll w[]){
    /*
    ∵ f[i,j]=max(f[i-1,j], f[i-1,j-v]+w, f[i-1,j-2v]+2w, f[i-1,j-3v]+3w, ..., f[i-1,j-kv]+kw)
       f[i,j-v]=max(        f[i-1,j-v],   f[i-1,j-2v]+w,  f[i-1,j-3v]+2w, ..., f[i-1,j-kv]+kw-w)
    ∴ f[i,j]=max(f[i-1,j],f[i,j-v]+w)
    rollback: f[j]=max(f[j],f[j-v]+w)
    */
    ll f[m+1]={0};
    for(int i=1;i<=n;i++)
        for(int j=v[i];j<=m;j++)
            f[j]=max(f[j],f[j-v[i]]+w[i]);
    return f[m];
}
//二进制优化多重背包
ll binary_multipack(int n, int m, int v[], ll w[], int s[]){
    /*
    当f[i,j-v]已经使用了s个物品时,f[i,j]不能由f[i-1,j-v]+w转移而来
    f[i,j]=max(f[i-1,j-kv]+kw),k∈[0,s[i]]
    对s个物品进行二进制拆分,类似于快速幂
    使得问题化为i取1，2，4，...，2^k，res 个物品的01背包问题
    可证明这些物品组合包含了所有方案
    */
    ll cnt=n,k;
    for(int i=1;i<=n;i++){
        k=2;s[i]--;//第一个已经在前n个物品中考虑了
        while(k<=s[i]){
            v[++cnt]=v[i]*k;
            w[cnt]=w[i]*k;
            s[i]-=k;
            k<<=1;
            
        }
        if(s[i]){
            v[++cnt]=v[i]*s[i];
            w[cnt]=w[i]*s[i];
        }
    }
    n=cnt;
    return _01pack(n,m,v,w);
}
//单调队列优化多重背包O(nm)
//注意如果n取到20000,则需要使用#define ll long long #pragma GCC optimize(3)否则超时3倍左右
ll mono_multipack(int n, int m, int v[], ll w[], int s[]){
    /*
    f[i,j]=max(f[i-1,j], f[i-1,j-v]+1w, f[i-1,j-2v]+2w, ..., f[i-1,j-sv]+sw)
    f[i,j-v]=max(        f[i-1,j-v]+0w, f[i-1,j-2v]+1w, ..., f[i-1,j-sv]+(s-1)w, f[i-1,j-(s+1)v]+sw)
    f[i,j-2v]=max(                      f[i-1,j-2v]+0w, ..., f[i-1,j-sv]+(s-2)w, f[i-1,j-(s+1)v]+(s-1)w, f[i-1,j-(s+2)v]+sw)
    ...
    上式是一个经典的滑动窗口求最大值问题, 只是求最大值时需要减去公差为w的等差数列的影响
    f[i,j],f[i,j-v],f[i,j-2v],...,f[i,r] 是带求序列，且满足j≡j-v≡j-2v≡...≡r (mod v)
    */
    ll f[m+1]={0},g[m+1]={0};//滚动数组g[j]=f[i-1,j]
    int q[m+1];//单调队列
    for(int i=1;i<=n;i++){
        memcpy(g,f,sizeof(f));
        for(int j=0;j<v[i];j++){
            int head=0,tail=-1;
            for(int k=j;k<=m;k+=v[i]){
                if(head<=tail && q[head]<k-s[i]*v[i]) 
                    head++;
                while(head<=tail && g[q[tail]]+w[i]*(k-q[tail])/v[i]<=g[k])
                    tail--;
                q[++tail]=k;
                f[k]=g[q[head]]+w[i]*(k-q[head])/v[i];
            }
        }
    }
    return f[m];
            
}

int main(){
    const int N=20007;
    int n,m;
    scanf("%d%d",&n,&m);
    int v[N],s[N];
    ll w[N];
    for(int i=1;i<=n;i++){
        scanf("%d%lld%d",&v[i],&w[i],&s[i]);
    }
    printf("%lld\n",mono_multipack(n,m,v,w,s));
}


