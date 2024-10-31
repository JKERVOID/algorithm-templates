#include<bits/stdc++.h>
using namespace std;
#define ll long long

//二分本质是找出一个 左半边满足某性质右半边满足相反性质的 边界位置
//https://www.luogu.com.cn/problem/P2249

int binary_search1(int l, int r, std::function<bool(int)> check){
    //找右半边的边界
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    return check(l) ? l : -1;
    //此法终止条件时l一定等于r，所以返回l或者r都可以
}

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

int main(){
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    const int N = 1e6 + 5;
    int n,m,p,q[N];
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> q[i];
    while(m--){
        cin >> p;
        int l=binary_search1(1,n,[&](int x){return q[x] >= p;});
        int r=binary_search2(1,n,[&](int x){return q[x] <= p;});
        if(l == -1 || r == -1 || r<l ) cout << -1 << " ";
        else cout << l <<" ";
    }

}