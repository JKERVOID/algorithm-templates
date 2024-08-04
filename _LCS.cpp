#include<bits/stdc++.h>
#define ll long long
using namespace std;

/*
问题：求最长公共子序列
https://www.luogu.com.cn/record/170480552[*]
时间复杂度：O(nm)
空间复杂度：O(min(n,m))
[*]特殊说明：
    对于没有重复元素的LCS，可以把a序列视作有序，则变成对b序列的LIS，优化到O(nlogn)
    具体做法为，记录b元素在a中的下标，然后对下标序列求LIS
    本算法为标准LCS算法,此题会TLE

原理：
    当a[i]==b[j]时，dp[i][j]=dp[i-1][j-1]+1
    当a[i]!=b[j]时，dp[i][j]=max(dp[i-1][j],dp[i][j-1])
    滚动一次：
        当a[i]==b[j]时，dp[cur][j]=dp[pre][j-1]+1
        当a[i]!=b[j]时，dp[cur][j]=max(dp[pre][j],dp[cur][j-1])
        swap(pre,cur)
    滚动优化：
        如果优化成一维，当要更新dp[j]前：
            dp[j]=dp[pre][j]
            dp[j-1]=dp[cur][j-1]
        尚缺少了dp[pre][j-1]的值，因此需要额外记录一个old=:=dp[pre][j-1]
        显然，old=更新dp[j]前的dp[j]即可
        综上：
            tmp = dp[j]
            当a[i]==b[j]时，dp[j]=old+1
            当a[i]!=b[j]时，dp[j]=max(dp[j],dp[j-1])
            old = tmp
*/


int LCS(int a[],int b[],int n,int m){
    //int n=a.size(),m=b.size();
    vector<int> dp(m+1,0);
    int old,tmp;
    for(int i=1;i<=n;i++){
        old = dp[0];
        for(int j=1;j<=m;j++){
            tmp = dp[j];
            if(a[i-1]==b[j-1])  dp[j]=old+1;
            else dp[j]=max(dp[j],dp[j-1]);
            old = tmp;
        }
    }
    
    return dp[m];
}

int main(){
    int n;scanf("%d",&n);
    const int N=1e6+5;
    int a[N],b[N];
    int x;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    cout<<LCS(a,b,n,n)<<endl;
    return 0;
}