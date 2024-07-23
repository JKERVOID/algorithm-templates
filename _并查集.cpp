#include<bits/stdc++.h>

using namespace std;


class UniF{
   public:
       vector<int> f, rank;

       explicit UniF(int size):f(size), rank(size, 0){
           iota(f.begin(), f.end(), 0);
           //从0开始为f[]赋值
      }

       int find(int a){
           return f[a]==a ? a : (f[a]=find(f[a]));
      }

       void merge(int x, int y){
           int rootx = find(x);
           int rooty = find(y);
           if(rootx == rooty)return;
           if(rank[rootx] > rank[rooty]) swap(rootx, rooty);
           f[rootx] = rooty;
           if(rank[rootx] == rank[rooty])rank[rooty]++;
      }
};

//初始化：UniF uf(n+1);
int main(){
    int n;
    UniF uf(n+1);//f[]下标从0-n
}

