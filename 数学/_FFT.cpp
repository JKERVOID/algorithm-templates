#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const double PI = acos(-1);

/*
    单位圆:z=cosθ+isinθ
    单位根:
        定义:z^n=1的根
        第k个:ω(n,k)=cos(2πk/n)+isin(2πk/n)
        性质:
            ω(n,k1)ω(n,k2) = ω(n,k1+k2)
            ω(n,k)^m = ω(n,km)
            1/ω(n,k) = 1/(cosθ+isinθ) = cosθ-isinθ =cos-θ+isin-θ = ω(n,-k)
        FTT性质要求n=2^b(b∈N): 
            周期性: ω(n,k+n)=ω(n,k)
            对称性: ω(n,k+n/2)=-ω(n,k)
            折半性: ω(n,2k)=ω(n/2,k)
            
    由系数求点值:
        A(x) = a0 + a1*x^1 + a2*x^2 + a3*x^3 + ... + a(n-1)*x^(n-1)
             = [a0 + a2*x^2 + ... + a(n-2)*x^(n-2)]   
             + [a1 + a3*x^3 + ... + a(n-1)*x^(n-2)]x  
        设:
          A1(x) = a0 + a2*x + a4*x^2 + ... + a(n-2)*x^(n/2-1)
          A2(x) = a1 + a3*x + a5*x^2 + ... + a(n-1)*x^(n/2-1)
        则:
          A(x) = A1(x^2)+A2(x^2)x
        带入ω(n,k),k<n/2:
          A(ω(n,k)) = A1(ω(n,2k)) + A2(ω(n,2k))*ω(n,k)
                    = A1(ω(n/2,k)) + A2(ω(n/2,k))*ω(n,k)
        带入ω(n,k+n/2),k<n/2:
          A(ω(n,k)) = A1(ω(n,2k+n)) + A2(ω(n,2k+n))*ω(n,k+n/2)
                    = A1(ω(n/2,k)) - A2(ω(n/2,k))*ω(n,k)
        
        由点值求系数:
        A(x) = a0 + a1*x^1 + a2*x^2 + a3*x^3 + ... + a(n-1)*x^(n-1)
        依次代入ω(n,0),ω(n,1),ω(n,2)...ω(n,n-1):
          yi = ∑_j aj*ω(n,i)^j
        构造多项式
          B(x) = y0 + y1*x^1 + y2*x^2 + y3*x^3 + ... + y(n-1)*x^(n-1)
        依次代入单位根倒数ω(n,0),ω(n,-1),ω(n,-2)...ω(n,-n+1):
          zk = ∑_i yi(w,-k)^i
        代入yi = ∑_j aj*ω(n,i)^j:
          zk = ∑_i [∑_j aj*ω(n,i)^j] * (w,-k)^i
             = ∑_i [∑_j aj*ω(n,i*j) * (w,-k*i)]
             = ∑_i [∑_j aj*ω(n,j-k)^i]
             = ∑_j aj * [∑_i ω(n,j-k)^i]
          当j=k,内层和式为∑_i 1^i = n
          当j≠k,内层和式为关于i的等比数列求和,其值为0
        此时:
          ak=zk/n
    位逆序优化:(蝴蝶变换)
      由于序列<ai>每次分治都可以看作是对末位0和1的分类
      使得最终结果序列可以看作从左到右读的二进制数
      因此原排列下标即为最终排列下标的二进制逆序:
      a0 a1 a2 a3 a4 a5 a6 a7
      a0 a2 a4 a6|a1 a3 a5 a7
      a0 a4|a2 a6|a1 a5|a3 a7 
      因此可以使用逆序变换序列自底向上迭代实现
    虚部优化:
      把B放在A的虚部上方程系数变为a+bi
      计算平方(a+bi)^2=(a^2-b^2)+i(2ab)
      答案变成虚部/2,少做依次B正变换

*/
class C{
public:
    double x,y;
    C(double _x=0,double _y=0):x(_x),y(_y){};
    friend std::ostream& operator<<(std::ostream& os, C self){
        return os<<'('<<self.x<<','<<self.y<<")";
    }
    C operator+(C _o)const  {return C(x+_o.x,y+_o.y);} 
    C operator-(C _o)const  {return C(x-_o.x,y-_o.y);}
    friend C operator*(double num,C &self)  {return C(num*self.x,num*self.y);}
    C operator/(double num)const  {return C(x/num,y/num);}
    //复数乘法:z1*z2=(x1x2-y1y2)+i(x1y2+x2y1) 等同于模长相乘,夹角相加
    C operator*(C _o)const {return C(x*_o.x - y*_o.y, x*_o.y + y*_o.x);}

};
vector<int> rev;//i的二进制逆序后的值
void FFT(vector<C>&A, int n, int op=1){
    /*
        多项式乘法正变换
        时空复杂度O(nlogn)
        A数组初始实部存系数,虚部存0
        最终A返回多项式的点值表达式
    */
    A.resize(n);
    for(int i=0;i<n;++i){
        if(i<rev[i])swap(A[i],A[rev[i]]);
    }

    for(int m=2;m<=n;m<<=1){//枚举块宽
        C w1(cos(2*PI/m),sin(2*PI/m)*op);
        for(int i=0;i<n;i+=m){//枚举块数
            C wk(1,0);
            for(int j=0;j<m/2;++j){//枚举半块
                C x=A[i+j], y=A[i+j+m/2]*wk;
                A[i+j]=x+y, A[i+j+m/2]=x-y;
                wk=wk*w1;
            }

        }

    }
};
void IFFT(vector<C>&A,int n){
    /*
        多项式乘法逆变换
        时空复杂度O(nlogn)
        A数组存储多项式的点值表达式
        最终A实部:系数*n,虚部:0            
    */
    FFT(A,n,-1);
    for(int i=0;i<n;++i)A[i]=A[i]/n;
};

vector<int> mltp(vector<int>&A_,vector<int>&B_){
        int n=1,m=A_.size()+B_.size()-1;
        while(n<=m)n<<=1;//求总点数n
        rev.resize(n,0);
        int l = log2(n);
        for (int i = 1; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
        }
        vector<C>A(n);
        for(int i=0; i<A_.size(); i++) A[i].x = A_[i];
        for(int i=0; i<B_.size(); i++) A[i].y = B_[i];
        FFT(A,n);//求点值
        for(int i=0;i<n;++i)A[i]=A[i]*A[i];
        IFFT(A,n);
        vector<int>ans(m);
        for(int i=0;i<m;++i)
            ans[i]=round(A[i].y/2);
        return ans;
    };


int main(){
    //https://www.luogu.com.cn/problem/P3803
    int n,m;cin>>n>>m;
    n++,m++;
    vector<int>A(n),B(m);
    for(auto& i:A)cin>>i;
    for(auto& i:B)cin>>i;
    vector<int>ans(mltp(A,B));
    for(auto i:ans)cout<<i<<" ";
}
