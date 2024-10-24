#include<bits/stdc++.h>
using namespace std;
#define ll long long

inline ll binpow(ll a, ll b, ll p=1e9+7) {
    ll res = 1;
    a = a % p; 
    while (b > 0) {
        if (b & 1) res = (res * a) % p; 
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}


int main(){
    ll a,b;
    cin>>a>>b;
    cout<<binpow(a,b)<<endl;
    return 0;
}