#include<bits/stdc++.h>
using namespace std;
using ll =long long;

/*
    原根:
        模数: p选择满足p=q*2^k+1的素数,且q也是素数
            如p=998244353199=119*2^23+1
            此时3是p的原根(p乘法取模群的原根)
            显然3的阶为p-1=q*2^23
        取根:
            设分别为g[0]~g[p-2]
            取n=2^b个对称值,满足g(k,n)=g[(p-1)/n*k]
        指数性:
            g(n,k1)g(n,k2)=g(n,k1+k2)
        周期性:
            g(n,k+n)=g(n,k)
        对称性:
            g(n,k+n/2)=-g(n,k)
            因为g(n,n/2)^2=g(n,n)=1,由于g(n,n/2)≠1所以g(n,n/2)=-1
        折半性:
            g(n,2k)=g(n/2,k)
            g(2k,n)=g[(p-1)/n*2k]=g[(p-1)/(n/2)*k]=g(n/2,k)
            
    剩下分析与FTT完全一致.
*/
const ll M=998244353;
const ll g=3,invg=332748118;

inline ll binpow(ll a, ll b, ll p=M) {
    ll res = 1;
    a = a % p; 
    while (b > 0) {
        if (b & 1) res = (res * a) % p; 
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}


vector<int> rev;//i的二进制逆序后的值
void FFT(vector<ll>&A, int n, int op=1){
    /*
        多项式乘法正变换
        时间复杂度O(n/2logn + lognlogp)
        A数组初始存系数
        最终A返回多项式的点值表达式
    */
    A.resize(n);
    for(int i=0;i<n;++i)
        if(i<rev[i])swap(A[i],A[rev[i]]);

    for(int m=2;m<=n;m<<=1){//枚举块宽
        ll g1=binpow((op==1?g:invg),(M-1)/m);
        for(int i=0;i<n;i+=m){//枚举块数
            ll gk=1;
            for(int j=0;j<m/2;++j){//枚举半块
                ll x=A[i+j], y=A[i+j+m/2]*gk%M;
                A[i+j]=(x+y)%M, A[i+j+m/2]=(x-y+M)%M;
                gk=gk*g1%M;
            }
        }
    }
};

void IFFT(vector<ll>&A,int n){
    /*
        多项式乘法逆变换
        时间复杂度O(n/2logn + lognlogp)
        A数组存储多项式的点值表达式
        最终返回系数
    */
    FFT(A,n,-1);
    ll invn=binpow(n,M-2);
    for(int i=0;i<n;++i)A[i]=A[i]*invn%M;
};

vector<ll> mltp(vector<ll>&A,vector<ll>&B){
    int n=1,m=A.size()+B.size()-1;
    while(n<=m)n<<=1;//求总点数n
    rev.resize(n,0);
    for (int i = 1; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1)?(n>>1):0);
    }
    
    A.resize(n,0);
    B.resize(n ,0);
    FFT(A,n);//求点值
    FFT(B,n);
    for(int i=0;i<n;++i)A[i]=B[i]*A[i]%M;
    IFFT(A,n);
    A.resize(m);
    return A;
};


int main(){
    //https://www.luogu.com.cn/problem/P3803
    int n,m;cin>>n>>m;
    n++,m++;
    vector<ll>A(n),B(m);
    for(auto& i:A)cin>>i;
    for(auto& i:B)cin>>i;
    vector<ll>ans(mltp(A,B));
    for(auto i:ans)cout<<i<<" ";
}
