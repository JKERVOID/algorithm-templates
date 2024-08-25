#include<bits/stdc++.h>
using namespace std;
#define ll long long

//归并排序可顺带求逆序对
int n;
void quick_sort(int q[],int l=1,int r=n){
    if(l>=r) return;
    int i=l-1,j=r+1,x=q[(l+r)>>1];
    //边界问题：
    //(l+r)>>1可以取到l，因此l>=r时，左侧已经排序完成，右侧需取j+1否则死循环
    while(i<j){
        do i++;while(q[i]<x);
        do j--;while(q[j]>x);
        if(i<j) swap(q[i],q[j]);
    }
    quick_sort(q,l,j);
    quick_sort(q,j+1,r);
}

const int N=5e5+10;
int tmp[N];
ll merge_sort(int q[],int l=1,int r=n){
    if(l>=r) return 0;

    int mid=(l+r)>>1;
    ll res=merge_sort(q,l,mid)+merge_sort(q,mid+1,r);
    int i=l,j=mid+1,k=0;
    while(i<=mid&&j<=r){
        if(q[i]<=q[j]) tmp[k++]=q[i++];
        else{
            res+=mid-i+1;
            tmp[k++]=q[j++];
        } 
    }
    while(i<=mid) tmp[k++]=q[i++];
    while(j<=r) tmp[k++]=q[j++];

    for(int i=l,j=0;i<=r;i++,j++) q[i]=tmp[j];
    return res;
}
/*
int main(){
    //https://www.luogu.com.cn/problem/P1177
    std::ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    int q[N];
    for(int i=1;i<=n;i++) cin>>q[i];
    merge_sort(q);
    for(int i=1;i<=n;i++) cout<<q[i]<<" ";
    return 0;
}*/

int main(){
    //https://www.luogu.com.cn/record/174705434
    std::ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int q[N];
        
    cin>>n;
    for(int i=1;i<=n;i++) cin>>q[i];
    cout<<merge_sort(q)<<endl;
    
}