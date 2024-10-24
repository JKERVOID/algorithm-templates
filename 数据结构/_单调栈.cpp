#include<bits/stdc++.h>
#define ll long long

using namespace std;
/*
应用：f(i)表示a[i]右边第一个比它大的数的下标
     当然可以做两次求作为最大值管的范围
时间复杂度：O(n)
原理：对于ai>=aj且i<j,那么aj一定不会是目标

*/

const int N=3e6+10;

void mono_stk(int a[],int n,int f[]){
    /*
    f[i]:= a[i]右边第一个比它大的数的下标
    */
    int stk[N],tt=0;
    for(int i=n;i>=1;i--){
        while(tt &&a[stk[tt]]<=a[i]) tt--;
        f[i]=( !tt?-1:stk[tt] );
        stk[++tt]=i;
    }
}


int main(){
    //需要快读
    int a[N],f[N];
    int n;  scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    mono_stk(a,n,f);
    for(int i=1;i<=n;i++) printf("%d ",a[f[i]]);

}