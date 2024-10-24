#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
/*
高斯消元法求异或空间线性基：
A)从高到低枚举每一列c:
    (1)找到一个二进制第c位是1的数
    (2)将这个数换到第c个
    (3)将所有第c位是1的数与该数异或

复杂度O(n^2),但数字需要在ull范围内
*/
ull deg(ull num, int i){return num & (1ull << i);}

int gauss_LBase(vector<ull> &x){
    int n=x.size()-1;
    int c,r;
    for(c=63,r=1; ~c && r<=n; c--){
        //(1)(2)
        for(int i=r;i<=n;i++)
            if(deg(x[i],c)){
                swap(x[r],x[i]);
                break;
            };
        if(!deg(x[r],c))continue;
        //(3)
        for(int i=1;i<=n;i++)
            if(i!=r && deg(x[i],c))
                x[i]^=x[r];
        
        r++;
    }
    x.resize(--r);
    return  r;
}
/*
贪心法求线性基：
由于线性基可以看做是一个拟阵，故必有贪心解
判断是否插入时从高到低按位执行：
    1、如果插入数该位为0，continue
    2、如果已有数使得该位为1，异或插入数使其该位置0
    3、如果该位无数字，直接插入
特点：
    1、可以直接判断插入数是否可以作为基底
    2、优先插入先进的数
*/
struct LBase{
    ull x[63];
    explicit LBase(){
        memset(x, 0, sizeof (x));
    }
    bool insert(ull num){
        for(int i=62;~i;i--)
            if(num & (1ull << i )){
                if(x[i]) num^=x[i];
                else{
                    x[i]=num;
                    break;
                }
            }
        return num>0;
    }
    ull get_max(){
        ull xum=0;
        for(int i=62;~i;i--)
            if (x[i])
                xum =max(xum,xum^x[i]);
        return xum;
    }
    void print(){
        for(int i=0;i<=62;i++)cout<<x[i]<<endl;
    }
};



//https://www.luogu.com.cn/problem/P3812
signed main(){
    LBase lb;
    int n;   cin>>n;
    ull x;
    
    for(int i=1;i<=n;i++){
        cin>>x;
        lb.insert(x);
    }
    //lb.print();
    cout<<lb.get_max()<<endl;
}