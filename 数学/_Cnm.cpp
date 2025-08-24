#include<bits/stdc++.h>
using namespace std;
#define ll long long
/*
求组合数：
1、Cnm_rec纯递归预处理：N^2
2、Cnm预处理阶乘(及其逆元)：p是质数，NlogN
3、lucas: p是质数，plogN
4、Cnm_big分子分母分解质因数：高精度，无取模
*/

/*
Cnm取模
c[a][b]=c[a-1][b]+c[a-1][b-1]
*/

//算法1：
void Cnm_rec(ll _N,vector<vector<ll>> &_c,ll _p=1e9+7){
    for(int i=0; i<=_N; i++)
        for(int j=0; j<=i; j++)
            if(j) _c[i][j] = (_c[i-1][j]+_c[i-1][j-1])%_p;
            else  _c[i][j] = 1;
}

//算法2：
inline ll binpow(ll a, ll b, ll &p) {
    ll res = 1;
    a = a % p; 
    while (b > 0) {
        if (b & 1) res = (res * a) % p; 
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}
//阶乘及其逆元预处理,自行决定是否预处理逆元
void ini_fac(vector<ll>&fac,vector<ll>&inv_fac,ll _N,ll& _p){
    fac.resize(_N+1);fac[0]=1;
    for(ll i=1; i<=_N; i++)
        fac[i]=fac[i-1]*i%_p;

    inv_fac.resize(_N+1);
    inv_fac[_N]=binpow(fac[_N],_p-2,_p);
    for(int i = _N-1; i >= 0; i--) 
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % _p; // 反推阶乘逆元
    
}

ll Cnm_res(vector<ll>&fac,vector<ll>&inv_fac,ll n,ll m,ll& _p){
    return inv_fac[m] *inv_fac[n-m] %_p*fac[n]%_p;
}

//算法3：
ll fac(ll&_p, ll end, ll begin=2){
    ll res=1;
    for(ll i=begin;i<=end;i++)res=res*i%_p;
    return res;
}

ll Cnm(ll n,ll m,ll& _p){
    ll ans = fac(_p,n,n-m+1);
    return ans*binpow(fac(_p,m),_p-2,_p)%_p;
}

//C[n][m]≡C[n%p][m%p]*C[n/p][m/p](mod p)
ll lucas(ll n, ll m,ll& _p){
    if(n<_p && m<_p)return Cnm(n,m,_p);
    return Cnm(n%_p,m%_p,_p)* lucas(n/_p,m/_p,_p)%_p;
}

//算法4：
typedef std::vector<int> _vi;
typedef std::vector<bool> _vb;
inline void get_primes(_vi &primes,/*_vi &min_factor,_vb &is_prime,*/int n) {//n以内的素数
    _vb is_prime(n+1,true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            //min_factor[i] = i;
            primes.push_back(i);
        }    
        for (int j = 0; j < primes.size() && 1LL * i * primes[j] <= n; ++j) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
            //primes[j]=i*k，没必要对i*k筛选了,也就是说对于(i*k)*q一定会在i*(k*q)时筛掉
        }
    }
}
//高精度乘法,倒叙存储
_vi mul(_vi a,int b){
    vector<int> c;
    ll t=0;
    for(auto i:a){
        t+=1LL*i*b;
        c.push_back(t%10);
        t/=10;
    }
    while(t){
        c.push_back(t%10);
        t/=10;
    }
    return c;
}
//计算n!中有p的次数time_in_fac
int TIF(int n,int p){
    int res=0;
    while(n) res+=(n/=p);
    return res;
}

_vi Cnm_big(int n, int m){
    _vi pri,sum,ans;
    get_primes(pri,n);
    for(auto p:pri)
        sum.push_back(TIF(n,p)-TIF(m,p)-TIF(n-m,p));

    ans.push_back(1);
    for(int i=0;i<pri.size();i++)
        for(int j=sum[i];j;j--)
            ans=mul(ans,pri[i]);
    return ans;
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t,_N,n,m;
    ll p=998244353;
    cin>>t>>_N;
    vector<ll>fac,inv_fac;
    ini_fac(fac,inv_fac,_N,p);
    //for(auto i:inv_fac)cout<<i<<" ";cout<<endl;
    ll ans=0;
    while(t--){
        cin>>n>>m;
        ans^=Cnm_res(fac,inv_fac,n,m,p);
        //cout<<ans<<endl;
    }
    cout<<ans;
}