#include<bits/stdc++.h>
#define ll long long

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
        */
        //rollback:
        for(int j=m;j>=v[i];j--)
            f[j]=max(f[j],f[j-v[i]]+w[i]); 
        
     
    }
    return f[m];
}
//完全背包
ll fullpack(int n, int m, int v[], ll w[]){
    /*
    ∵ f[i,j]=max(f[i-1,j], f[i-1,j-v]+w, f[i-1,j-2v]+2w, f[i-1,j-3v]+3w,..., f[i-1,j-kv]+kw)
       f[i,j-v]=max(        f[i-1,j-v],   f[i-1,j-2v]+w,  f[i-1,j-3v]+2w,..., f[i-1,j-kv]+kw-w)
    ∴ f[i,j]=max(f[i-1,j],f[i,j-v]+w)
    rollback: f[j]=max(f[j],f[j-v]+w)
    */
    ll f[m+1]={0};
    for(int i=1;i<=n;i++)
        for(int j=v[i];j<=m;j++)
            f[j]=max(f[j],f[j-v[i]]+w[i]);
    return f[m];
}
//多重背包
ll multipack(int n, int m, int v[], ll w[], int s[]){
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


int main(){
    const int N=25000;
    int n,m;
    cin >> n >>m;
    int v[N],s[N];
    ll w[N];
    for(int i=1;i<=n;i++){
        cin >> v[i] >>w[i]>>s[i];
    }
    cout<<multipack(n,m,v,w,s);
}


