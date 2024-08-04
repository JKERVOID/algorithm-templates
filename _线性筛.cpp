#include<bits/stdc++.h>
using namespace std;


const int pN = 1e5+7;

std::vector<int> primes;
std::vector<bool> is_prime(pN + 1, true);
std::vector<int> min_factor(pN + 1);//最小质因子

inline void get_primes(int n) {//n以内的素数
    is_prime[0] = is_prime[1] = false;
    min_factor[0] = 0;
    min_factor[1] = 1;

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

int main(){
    get_primes(100);
    for (int i = 0; i < primes.size(); ++i) {
        cout << primes[i] << " ";
    }cout<<endl;
    for(int i=0;i<=100;++i){
        cout<<i<<" min_factor= "<<min_factor[i]<<endl;
    }
}

