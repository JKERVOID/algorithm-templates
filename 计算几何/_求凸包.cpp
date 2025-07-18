#include<bits/stdc++.h>
using namespace std;

using ll =long long;

class Point{
public: 
    double x,y;
    Point(double _x,double _y):x(_x),y(_y){};
    Point():x(0),y(0){};//无参构造类型

    friend std::ostream& operator<<(std::ostream& os, Point& self){
        os<<'('<<self.x<<','<<self.y<<")";
        return os;
    }
    Point operator+(Point o)const{
        return Point(x+o.x,y+o.y);
    } 
    Point operator-(Point o)const{
        return Point(x-o.x,y-o.y);
    }
    friend Point operator*(double num,Point &self){
        //数乘：此写法只允许左乘数字
        return Point(num*self.x,num*self.y);
    }
    friend double dot(Point _a, Point _b){
        //点乘：=|a||b|cosθ
        return _a.x*_b.x+_a.y*_b.y;
    }
    double len(){
        return sqrt(x*x+y*y);
    }
    friend double angle(Point a,Point b){
        //夹角：无方向，小于等于平角
        return acos(dot(a,b)/a.len()/b.len());
    } 
    double operator*(Point o)const{
        //叉积：=|a||b|sinθ (平行四边形的有向面积)
        //o在*this逆时针方向(左侧)为正
        return x*o.y-y*o.x;
    }
    bool operator<(Point o)const{
        //重载小于号用于双关键字排序
        return x==o.x ? y<o.y : x<o.x;
    }



};
const int N=1e5+13;
Point st[N];int tt=0;
void Andrew(vector<Point>&ps){
/*
    原理：
        1、双关键字排序所有点，左下角和右上角点必在凸包上；
        2、分别从这两点开始维护下上凸包：
            (*)显然对于凸包边界上的所有向量，满足：
                1)相邻向量都在对方左侧；
                2)所有点顺时针排序顺序 与 按(x:y)双关键字排序 相同
            a、只需按顺序枚举所有点,对于每个点p：
                a.1、一旦出现(top-1,p)在(top-1,top)左侧，
                     就更新top为p，重复操作直到栈内点小于等于2个
    复杂度：<O(4n), 所有点出入栈最多两次
*/
    sort(ps.begin(),ps.end());
    for(auto pt=ps.begin();pt!=ps.end();++pt){
        //下凸包
        while(tt>1 && (st[tt]-st[tt-1])*((*pt)-st[tt-1])<=0)tt--;
        //取等于即删去凸包边界上的共线点
        st[++tt]=(*pt);
        
    }
    int sz=tt;//显然至少sz个点已经是正确的了，栈内至少需要sz+1个点
    for(auto pt=ps.rbegin();pt!=ps.rend();++pt){
        while(tt>sz && (st[tt]-st[tt-1])*((*pt)-st[tt-1])<=0)tt--;
        st[++tt]=(*pt);
    }
    --tt;//逆序加入的最后一个点显然是第一个点
}


int main(){
    int n;cin>>n;
    vector<Point> ps(n);
    for(auto &p:ps){
        cin>>p.x>>p.y;
    }
    stack<Point>s;
    Andrew(ps);
    double sum=0;
    for(int i=1;i<=tt;i++){
        //利用最后一个点(tt+1,一般来说是越界点)是第一个点的性质
        sum+=(st[i+1]-st[i]).len();
    }
    cout<<fixed<<setprecision(2)<<sum<<endl;


}