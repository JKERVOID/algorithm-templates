#include<bits/stdc++.h>

using namespace std;


class UniF{
    public:
        vector<int> f, rank;

        explicit UniF(int size):f(size+1), rank(size+1, 0){
            iota(f.begin(), f.end(), 0);
            //从0开始为f[]赋值
        }

        int find(int a){
            return f[a]==a ? a : (f[a]=find(f[a]));
        }

        bool merge(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            if(rootx == rooty)return 0;//无需合并
            if(rank[rootx] > rank[rooty]) swap(rootx, rooty);
            f[rootx] = rooty;
            if(rank[rootx] == rank[rooty])rank[rooty]++;
            return 1;
        }
};

//初始化：UniF uf(n);
int main(){
    int n;
    UniF uf(n);//f[]下标从0-n
}

