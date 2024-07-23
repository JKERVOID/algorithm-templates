#include<bits/stdc++.h>
using namespace std;
#define ll long long

//扩展欧几里得
std::tuple<ll,ll,ll> exgcd(ll a,ll b){
    if(a==0)return make_tuple(b,0,1);
    auto [d,x,y]=exgcd(b%a,a);
    return make_tuple(d,y-(b/a)*x,x);
}


//求逆元
ll inv(ll a,ll p){ 
    
    //a与p不满足互质时输出-1，无逆元
    //注意p原则上不能为0、1
    auto[d,x,y]=exgcd(a,p);
    while(x<0)x+=p;//保证逆元为正数
    return d==1?x%p:-1;
}

signed main(){
    ll a,b;
    while(cin>>a>>b){
        auto[d,x,y]=exgcd(a,b);

        if(d==__gcd(a,b))cout<<"gcd("<<a<<","<<b<<")="<<d<<endl;
        else cout<<"error in gcd"<<endl;

        cout<<a<<'*'<<x<<"+"<<b<<'*'<<y<<"="<<d<<endl;
        if(a*x+b*y!=d){
            cout<<"is error, ans is:"<<a*x+b*y<<endl;
        }

        if(__gcd(a,b)==1){
            ll x=inv(a,b);
            cout<<a<<' '<<x<<endl;
            if(x*a%b!=1)
                cout<<"error in inv"<<endl;
        }
        else cout<<inv(a,b)<<endl;
    }
    
}



