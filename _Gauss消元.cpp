#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
高斯消元法求n元一次方程组：
A)枚举每一列c:
    (1)找到绝对值最大的a[t][c],大浮点数作被除数误差更小
    (2)将t行换最上面（第c行）
    (3)将该行缩小倍数，使得c列系数变为1
    (4)将下方所有行减去该行的倍数，使得其c列变为0
B)处理b列使其等于xi
复杂度：O(n^3)
*/

const int N=110;
const double eps= 1e-6;

int gauss(vector<vector<double>> &a, int n){
    //增广矩阵，a[r][c]代表r行x^c的系数，a[r][n+1]为右侧常数
    //A)
    int c,r,t;
    for(c=r=t=1; c<=n; c++,t=r){
        //(1)
        for(int i=r+1;i<=n;i++)
            if(fabs(a[i][c]) > fabs(a[t][c]))t=i;
        if(fabs(a[t][c])<eps)continue;
        //(2)
        for(int j=1;j<=n+1;j++)swap(a[t][j],a[r][j]);
        //(3)
        for(int j=n+1;j>=c;j--)a[r][j] /= a[r][c];
        //(4)
        for(int i=r+1;i<=n;i++)
            if(fabs(a[i][c])>eps)
                for(int j=n+1;j>=c;j--) 
                    a[i][j]-=a[r][j]*a[i][c];
        r++;
    }
    
    if(r<=n){//正常结束时r=n+1
        for(int i=r;i<=n;i++){
            if(fabs(a[i][n+1])>eps)
                return -1;//无解,出现0=x
        }
        return 1;//有无穷多解
    }

    //B)保留了上三角，且答案存在a[r][0]
    for(int i=n;i>=1;i--){
        a[i][0]=a[i][n+1];
        for(int j=i+1;j<=n;j++){
            a[i][0]-=a[i][j]*a[j][0];
        }
    }
    return 0;//有唯一解
}



//https://www.luogu.com.cn/problem/P2455
signed main(){
    vector<vector<double>> a;
    int n;cin>>n;
    a.resize(n+1);
    for(int i=1;i<=n;i++){
        a[i].resize(n+2);
        for(int j=1;j<=n+1;j++){
            cin>>a[i][j];
        }
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