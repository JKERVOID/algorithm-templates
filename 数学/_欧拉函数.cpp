#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
φ[n]表示1-n中与n互质的数的个数
如果n=p1^a1*p2^a2*...*pk^ak
则φ[n]=n*(1-1/p1)*(1-1/p2)*...*(1-1/pk)
证明：
    φ[n]= N - ∑N/pi + ∑N/(pi*pj)-...+...-...+...-∑N/(pi*pj*...*pk)
    上式与表达式展开式完全一致
以上除号均为整除，向下取整
*/

/*
欧拉定理：若a与m互质，那么a^φ(m)≡1(mod m)
证明思路：{a^pi}≡{pj},其中{i}与{j}是1到φ(m)的不同排列

扩展欧拉定理: (欧拉降幂)
a^b(mod m) = 
    b <  φ(m),  a^b
    b >= φ(m),  a ^ ( b mod φ(m) + φ(m) )
    注:两种情况不能合并
*/

//欧拉函数，时间复杂度O(sqrt(n))
int euler_phi(int n){
    int res = n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            while(n%i==0) n/=i;
            res-=res/i;
        }
    }
    if(n>1) res-=res/n;
    return res;
}

//欧拉筛法求phi[n],时间复杂度O(n)
const int N = 1e6+10;
inline void euler_seive_phi(vector<int>& phi, int n) {
    vector<int> primes;
    vector<bool> is_prime(N + 1, true);
    //n以内的素数
    is_prime[0] = is_prime[1] = false;
    phi[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            phi[i] = i - 1;
            primes.push_back(i);
        }
            
        for (int j = 0; j < primes.size() && 1LL * i * primes[j] <= n; ++j) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                //i与i * primes[j]的质因子组合完全一致
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
                //primes[j]=i*k，没必要对i*k筛选了,也就是说对于(i*k)*q一定会在i*(k*q)时筛掉
            }else
            //i * primes[j]比i的质因子组合多了primes[j]这个质因子
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
            //primes[j]乘除各一次被消去
        }
    }
}

signed main(){
    int t;cin>>t;
    vector<int> phi(N+1);
    euler_seive_phi(phi,N);
    while(t--){
        int n;cin>>n;
        cout<<phi[n]<<endl;
    }
}