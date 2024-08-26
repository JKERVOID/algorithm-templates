#include<bits/stdc++.h>
using namespace std;
#define ll long long

//ST表,可以作为倍增模版

const int N=1e5+5;
const int M=17;//M=log2(N)+1,包括0
ll w[N];//原数组
int n;

struct ST{
    ll lo2[N];//预处理log更快
    ll _st[N][M];//跳表
    function<ll(ll,ll)>_tr = [](ll a,ll b){
        //2^(j-1)区间到2^j区间的转移函数
        return max(a,b);
    };
    explicit ST(){
        //初始化log函数
        lo2[1]=0;
        for(int i=2;i<=n;i++)lo2[i]=lo2[i>>1]+1;

        //初始化跳表
        for(int j=0;j<=lo2[n];j++)//区间长度=1<<j
            for(int i=1; i+(1<<j)-1<=n; i++){
                if(!j)_st[i][j]=w[i];
                else _st[i][j]=_tr(_st[i][j-1],_st[i+(1<<(j-1))][j-1]);
            }
    }

    ll query(int l,int r){
        //查询区间[l,r]的答案
        int k=lo2[r-l+1];
        //视作l开始的区间和r结尾的区间做一次转移
        return _tr(_st[l][k],_st[r-(1<<k)+1][k]);

    }
};

signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>w[i];
    ST st;
    int l,r;

    while(m--){
        cin>>l>>r;
        cout<<st.query(l,r)<<'\n';
    }

}