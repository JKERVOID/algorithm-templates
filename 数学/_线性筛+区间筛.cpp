#include<bits/stdc++.h>
#define ll long long
using namespace std;

typedef std::vector<int> _vi;
typedef std::vector<bool> _vb;
inline void get_primes(_vi &primes,_vi &min_factor,_vb &is_prime,int n) {//n以内的素数
    min_factor.resize(n+1);
    min_factor[0] = 0;min_factor[1] = 1;

    is_prime.resize(n+1,true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            min_factor[i] = i;
            primes.push_back(i);
        }
            
        for (int j = 0; j < primes.size() && 1LL * i * primes[j] <= n; ++j) {
            is_prime[i * primes[j]] = false;
            //对于i*primes[j]的合数，i是其最大因子，prime[j]是最小质因子
            min_factor[i * primes[j]] = primes[j];
            if (i % primes[j] == 0) {
                break;
                //primes[j]=i*k，没必要对i*k筛选了,也就是说对于(i*k)*q一定会在i*(k*q)时筛掉
            }
        }
    }

}

inline void get_factors(ll l, ll r,_vi &primes, vector<pair<ll,int>> fac[]) {
    //区间筛，找出区间[l,r]的所有数的质因子，按r+1-i的顺序存入fac[i]中
    int len = r-l+1;
    vector<ll>num(len+1);
    
    for(int i=1;i<=len;++i){
        num[i]=r-i+1;
    }
    
    for(auto i: primes){
        if(i*i>r)break;
        ll k=r%i+1;//如果i<=len说明区间内存在至少两个i的倍数
        if(k>len)continue;//k<=len说明区间内至少一个i的倍数
        for(int j=k;j<=len;j+=i){
            fac[j].push_back({i,0});
            //如果只需判断是否是素数，可以省略下一步
            while(num[j]%i==0){
                fac[j].back().second++;
                num[j]/=i;
            }
        }
    }
    for(int i=1;i<=len;i++){
        //如需判断素数:if(num[i]==r+1-i)is_big_prime[r-i+1]=true;
        if(num[i]!=1)fac[i].push_back({num[i],1});
    }
}

int main(){
    _vi primes,min_factor;
    _vb is_prime;
    get_primes(primes,min_factor,is_prime,100);
    for (int i = 0; i < primes.size(); ++i) {
        cout << primes[i] << " ";
    }cout<<endl;
    for(int i=0;i<=100;++i){
        cout<<i<<" min_factor= "<<min_factor[i]<<endl;
    }
}

