#include<bits/stdc++.h>
using namespace std;

using ll =long long;

class Point{
public: 
    double x,y;
    Point(double _x,double _y):x(_x),y(_y){};

    std::ostream& operator<<(std::ostream& os){
        os<<'('<<x<<','<<y<<")";
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
    double cross(Point o)const{
        //叉积：=|a||b|sinθ (平行四边形的有向面积)
        //o在*this逆时针方向(左侧)为正
        return x*o.y-y*o.x;
    }


};

