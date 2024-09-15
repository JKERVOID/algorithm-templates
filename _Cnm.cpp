#include<bits/stdc++.h>
using namespace std;
#define ll long long
/*
求组合数：
1、纯递归预处理N^2
2、预处理阶乘：p是质数，NlogN
3、公式法直接算：NlogN
4、lucas: plogN
*/


//扩展欧几里得
std::tuple<ll,ll,ll> exgcd(ll a,ll b){
    if(a==0)return make_tuple(b,0,1);
    auto [d,x,y]=exgcd(b%a,a);
    return make_tuple(d,y-(b/a)*x,x);
}
//快速幂
inline ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
//求逆元
inline ll inv(ll a,ll p){ 
    //a与p不满足互质时输出-1，无逆元
    //注意p原则上不能为0、1
    auto[d,x,y]=exgcd(a,p);
    while(x<0)x+=p;//保证逆元为正数
    return d==1?x%p:-1;
}
//阶乘取模
ll fac(ll n,ll p=1e9+7){
    ll res=1;
    for(ll i=2;i<=n;i++)res=res*i%p;
    return res;
}
//Cnm%p
ll Cnm(ll n,ll m,ll p){
    if(n==m || m==0)return 1;
    if(n%m==0)return n/m * Cnm(n-1,m-1,p)%p;
    if(n-m<m)m=n-m;
    ll denominator=fac(m,p)*fac(n-m,p)%p;
    ll inv_denominator=inv(denominator,p);
    if(inv_denominator==-1){
        //cout<<"C"<<n<<","<<m<<" has no inverse mod "<<p<<endl;
        return(Cnm(n-1,m-1,p)+Cnm(n-1,m,p))%p;
    }
    ll numerator=fac(n,p);
    return numerator*inv_denominator%p;
}
/*
Cnm取模
c[a][b]=c[a-1][b]+c[a-1][b-1]
*/
void Cnm_rec(ll _N,vector<vector<ll>> &_c,ll _p=1e9+7){
    for(int i=0; i<=_N; i++)
        for(int j=0; j<=i; j++)
            if(j) _c[i][j] = (_c[i-1][j]+_c[i-1][j-1])%_p;
            else  _c[i][j] = 0;
}

int main(){
    ll n,p;
    n=200, p=1e9+7;
    vector<vector<ll>>c(n+1);
    for(int i=1;i<=n;i++)c[i].resize(i+1);
    Cnm_rec(n,c,p);
    for(auto i:c){
        for(auto j:i){
            cout<<j<<" ";
        }cout<<endl;
    }
}