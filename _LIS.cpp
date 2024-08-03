#include<bits/stdc++.h>
#define ll long long
using namespace std;

//求最长上升子序列
//时间复杂度：O(nlogn)
//原理：长度更短的序列结尾值也更大则没有意义，记录
//https://www.luogu.com.cn/problem/P1020

int binary_search2(int l, int r,std::function<bool(int)> check){
    //找左半边的边界
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    return check(r) ? r : -1;
    //同上
}

int LIS(int n, int a[], int q[]){
    memset(q,0,sizeof(q));
    int ans=0;q[0]=-2e9;
    for(int i=1;i<=n;i++){
        int x = binary_search2(0,ans,[&](int j){
            return q[j] < a[i];
        });
        q[x+1] = a[i];
        ans = max(ans,x+1);
    }
    return ans;
    
}
int main(){
    const int N=1e5+5;
    int n,a[N],q[N];
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cout<<LIS(n,a,q)<<endl;
}
