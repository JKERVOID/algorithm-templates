#include<bits/stdc++.h>

using namespace std;
using ll = long long ;


//https://www.luogu.com.cn/problem/P3374
//如需解决区间修改单点查询，可以考虑结合差分数组
//memset不要忘记，数组从1开始

const int N=5e5+13;
int tr[N];
int n;

int lowbit(int x){
    return x&-x;//-x=~x+1
}
void add(int x, int num){
    //修改后会影响到的tr[i]如下
    for(int i=x;i<=n;i+=lowbit(i))tr[i]+=num;
}
int sum(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i))res+=tr[i];
    return res;
}

int main(){
    memset(tr,0,sizeof(tr));
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        add(i,x);
    }
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            add(x,y);
        }else{
            cout<<sum(y)-sum(x-1)<<endl;
        }
    }

    

}