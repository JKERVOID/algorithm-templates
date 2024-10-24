#include<bits/stdc++.h>
#define ll long long

using namespace std;
/*
应用:滑动窗口最大值,滑动窗口最小值
时间复杂度:O(n)
原理：队列尾部元素小于待加入的值,则弹出,因为永远没机会出线了
*/

void mono_que(int a[],int n,int k,int fmax[],int fmin[]){
    int que[n+1],head=0,tail=-1;
    for(int i=1;i<=n;i++){
        //判断队列头部元素是否在窗口内
        if(head<=tail && que[head]<i-k+1) 
            head++;
        //维护单调性
        while(head<=tail && a[que[tail]]>=a[i]) 
            tail--;
        que[++tail]=i;
        if(i>=k)//若需要前k个元素的最小值,则删掉此句
            fmin[i]=que[head];       
    }
    head=0,tail=-1;
    for(int i=1;i<=n;i++){
        if(head<=tail && que[head]<i-k+1) 
            head++;
        while(head<=tail && a[que[tail]]<=a[i]) 
            tail--;
        que[++tail]=i;
        if(i>=k)
            fmax[i]=que[head];
    }
}

int main(){
    int n,k;  cin >> n >>k;
    const int N = 1e3+5;
    int a[N],fmax[N],fmin[N];
    for(int i=1;i<=n;i++) cin >> a[i];
    mono_que(a,n,k,fmax,fmin);
    for(int i=k;i<=n;i++) cout << a[fmin[i]] << " ";   cout << endl;
    for(int i=k;i<=n;i++) cout << a[fmax[i]] << " ";   cout << endl;
    return 0;
}