#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;

//https://www.luogu.com.cn/problem/P1177
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

const int N=1e5+10;
int tmp[N];
void merge_sort(int q[],int l=1,int r=n){
    if(l>=r) return;
    int mid=(l+r)>>1;
    merge_sort(q,l,mid);
    merge_sort(q,mid+1,r);
    int i=l,j=mid+1,k=0;
    while(i<=mid&&j<=r){
        if(q[i]<=q[j]) tmp[k++]=q[i++];
        else tmp[k++]=q[j++];
    }
    while(i<=mid) tmp[k++]=q[i++];
    while(j<=r) tmp[k++]=q[j++];

    for(int i=l,j=0;i<=r;i++,j++) q[i]=tmp[j];

}

int main(){
    cin>>n;
    int q[n+1];
    for(int i=1;i<=n;i++) cin>>q[i];
    merge_sort(q);
    for(int i=1;i<=n;i++) cout<<q[i]<<" ";
    return 0;
}