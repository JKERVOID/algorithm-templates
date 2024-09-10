#include<bits/stdc++.h>
using namespace std;
#define ll long long
/*

中国剩余定理：O(n*logN)
对于一元线性同余方程组{x≡ai(mod mi)}且对任意i≠j满足gcd(mi,mj)==1:
设M=∏mi,Mi=M/mi,Mi模mi意义下的逆为_Mi，则x=∑(ai*Mi*_Mi)
易知存在gcd(mi,mj)≠1时，Mi与mi不互质，无逆元

扩展中国剩余定理：O(n*logN)
为解决不满足gcd(mi,mj)==1的问题，我们每次合并两个线性同余方程为新的线性同余方程即可；
1、任取两个方程并转化形式为：x=ki*mi+ai=kj*mj+aj =>> ki*mi-kj*mj=aj-ai
2、取d=gcd(mi,mj)显然有解的充要条件为d|(aj-ai),并解出k1*mi-k2*mj=d的k1解系
3、k1=k1'+ k*mj/d, 所以ki=k1'*(aj-ai)/d + k*mj/d
4、因此ki'=k1'*(aj-ai), 取解系最小值ki'%=mj/d
5、把ki解系带回式子 x=ki*mi+ai，有x=(ki'+k*mj/d) *mi + ai
6、整理得到x=k*(mi*mj/d) + (mi*ki'+ai) 

*/


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

//中国剩余定理求解x,需保证mi两两互质！
ll C_res(ll a[],ll m[],int n){
    ll _M=1,_x=0,Mi,_Mi;
    for(int i=1;i<=n;i++){
        _M*=m[i];//注意范围会不会超过ll
    }
    for(int i=1;i<=n;i++){
        Mi=_M/m[i];
        _Mi=inv(Mi,m[i]);
        _x+=a[i]*Mi*_Mi;
    }
    return _x;
}

//扩展中国剩余定理
ll exCRT(ll a[],ll m[],int n){
    ll ai=a[1],mi=m[1],aj,mj,k1,k2,ki,d,lcm;
    for(int i=2;i<=n;i++){
        aj=a[i],mj=m[i];
        auto[d,k1,k2]=exgcd(mi,mj);
        if((aj-ai)%d)return -1;//无解
        lcm = abs(mi/d*mj);
        ki = k1*(aj-ai)/d % (mj/d);//取解析中最小值，可能有负数
        ai = ((mi*ki+ai))%lcm;
        if(ai<0)ai+=lcm;//剔除负数
        mi = lcm;
    }
    return ai;
}
/*
//https://www.acwing.com/problem/content/1302/
signed main(){
    ll x,d,a[4],m[4],n=3,cnt=1;
    m[1]=23;
    m[2]=28;
    m[3]=33;
    constexpr ll add = 23*28*33;
    while(1){
        for(int i=1;i<=n;i++){
            cin >> a[i];
        }
        cin>>d;
        if(a[1]==-1 && a[2]==-1 && a[3]==-1)break;
        ll x = C_res(a,m,n);
        x%=add;
        while(x<=d)x+=add;
        cout<<"Case "<<cnt<<": the next triple peak occurs in "<<(x-d)<<" days."<<endl;
        cnt++;
    }
    
}
*/

//https://www.acwing.com/problem/content/206/
signed main(){
    int n;cin >> n;
    const int N=26;
    ll a[N],m[N];
    for(int i=1;i<=n;i++)cin >> a[i] >> m[i];
    cout<< exCRT(m,a,n);
}