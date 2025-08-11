#include<bits/stdc++.h>
using namespace std;

using ll =long long;

const double pi=acos(-1);
const double eps=1e-8;

class P{
public: 
    double x,y;
    P(double _x=0,double _y=0):x(_x),y(_y){};

    friend std::ostream& operator<<(std::ostream& os, P self){
        return os<<'('<<self.x<<','<<self.y<<")";
    }
    
    P operator+(P _o)const  {return P(x+_o.x,y+_o.y);} 
    P operator-(P _o)const  {return P(x-_o.x,y-_o.y);}

    //数乘
    friend P operator*(double num,P &self)  {return P(num*self.x,num*self.y);}

    /* 叉积：=|a||b|sinθ (平行四边形的有向面积)，o在*this逆时针方向(左侧)为正*/
    double operator*(P _o)const {return x*_o.y-y*_o.x;}
    
    /*点乘：=|a||b|cosθ*/
    friend double dot(P _a, P _b)   {return _a.x*_b.x+_a.y*_b.y;}

    double len()    {return sqrt(x*x+y*y);}

    friend double angle(P a,P b){
        //起始点为a,终点为b
        if(a*b>-eps)
        //夹角：无方向，小于等于平角
            return acos(dot(a,b)/a.len()/b.len());
        else 
            return 2*pi-acos(dot(a,b)/a.len()/b.len());
    } 

    double get_aph(){
        //计算与x轴的夹角
        return angle(P(1,0),*this);
    }
    
};

bool on_left(P _p, P _va,P _vb){
    //判断点是否在向量左侧
    return (_p-_va)*(_vb-_va)>0;
}

bool is_cross(P _va,P _vb, P _ua, P _ub){
    //判断两线段是否有交点
    return on_left(_va,_ua,_ub)^on_left(_vb,_ua,_ub);
}

P getNode(P _a,P _u, P _b,P _v){
/*
    求两条直线的交点
    需转化成点向式直线，即a代表起点，u代表a为起点的向量
*/
    double _t=(_a-_b)*_v/(_v*_u);
    return _a+_t*_u;
}


// class P{
// public:
//     double x,y,z;
//     P(double _x=0, double _y=0, double _z=0):x(_x),y(_y),z(_z){}
    
//     friend std::ostream& operator<<(std::ostream& os, P self){
//         return os<<'('<<self.x<<','<<self.y<<','<<")";
//     }
//     P operator+(P _o)const{
//         return P(x+_o.x,y+_o.y,z+_o.z);
//     } 
//     P operator-(P _o)const{
//         return P(x-_o.x,y-_o.y,z-_o.z);
//     }
//     friend P operator*(double num,P &self){
//         //数乘：此写法只允许左乘数字
//         return P(num*self.x,num*self.y,num*self.z);
//     }
//     P operator*(P _o)const{
//         //叉积：=|a||b|sinθ (平行四边形的有向面积)
//         //方向右手定则
//         return P(y*_o.z-z*_o.y, z*_o.x-x*_o.z, x*_o.y-y*_o.x);
//     }

//     friend double dot(P _a, P _b){
//         //点乘：=|a||b|cosθ
//         return _a.x*_b.x + _a.y*_b.y + _a.z*_b.z;
//     }

// };