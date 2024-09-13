#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
高斯消元法求n元一次方程组：
先做倒三角再带入求{xi}
复杂度：O(n^3)
*/

const int N=110;

int gauss(vector<vector<double>> &a, int n){
    //a[i][j]代表i行a^j的系数，等式右边为0；
    const double eps= 1e-6;
    int c=1,r=1;
    for(;c<=n;c++){
        int t=r;
        for(int i=r;i<=n;i++){
            if(fabs(a[i][c]) > fabs(a[t][c]))t=i;
        } 
        if(fabs(a[t][c])<eps)continue;

        for(int j=0;j<=n;j++)swap(a[t][j],a[r][j]);

        a[r][0] /= a[r][c];
        for(int j=n;j>=c;j--)a[r][j] /= a[r][c];
        
        for(int i=r+1;i<=n;i++){
            if(fabs(a[i][c])>eps){
                a[i][0]-=a[r][0]*a[i][c];
                for(int j=n;j>=c;j-- ) 
                    a[i][j]-=a[r][j]*a[i][c];
            }

        }
        r++;
    }
    if(r<=n){
        for(int i=r;i<=n;i++){
            if(fabs(a[i][0])>eps)
                return -1;//无解
        }
        return 1;//有无穷多解
    }

    for(int i=n;i>=1;i--){
        for(int j=i+1;j<=n;j++){
            a[i][0]-=a[i][j]*a[j][0];
        }
    }
    for(int i=n;i>=1;i--)a[i][0]=-a[i][0];
    return 0;//有唯一解
}



//https://www.luogu.com.cn/record/176835066
signed main(){
    vector<vector<double>> a;
    int n;cin>>n;
    a.resize(n+1);
    for(int i=1;i<=n;i++){
        a[i].resize(n+1);
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
        cin>>a[i][0];
        a[i][0]=-a[i][0];
    }
    
    int ans=gauss(a,n);
    
    if(ans==0){
        for(int i=1;i<=n;i++){
            cout<<"x"<<i<<"="<<fixed<<setprecision(2)<<a[i][0]<<endl;
        }
    }else if(ans<0){
        cout<<-1<<endl;
    }else{
        cout<<0<<endl;
    }
    
}