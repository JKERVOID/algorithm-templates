#include<bits/stdc++.h>
typedef long long ll;

//线段树
using namespace std;
const int N=1e5+113;
ll w[N];
class SegTree{//以求和为例
public:
    struct Node{
        int l,r;ll sum;
        ll tag;
    };vector<Node>tree;

    int n;

    inline int ls(int i){return i<<1;}
    inline int rs(int i){return i<<1|1;}

    void push_up(int i){
        //向上一层更新sum
        auto &[l,r,sum,tag]=tree[i];
        sum = tree[ls(i)].sum + tree[rs(i)].sum;
    }

    inline void change(int i,ll d){
        //避免重复，此函数用于处理tag传递到本层带来的修改
        auto &[l,r,sum,tag]=tree[i];
        tag += d;
        sum += d*(r-l+1);
    }

    inline void push_down(int i){
        //向下一层传递tag
        auto &[l,r,sum,tag]=tree[i];
        if(tag){
            change(ls(i),tag);
            change(rs(i),tag);
            tag=0;
        }
    }

    void update(int i,int l,int r,ll d){
        //以求和为例
        if(l<=tree[i].l && tree[i].r<=r){
            change(i,d);
            return;
        }

        push_down(i);//标记需要分裂
        int mid=(tree[i].l+tree[i].r)>>1;
        if(l<=mid)update(ls(i),l,r,d);
        if(r>mid)update(rs(i),l,r,d);
        push_up(i);//更新sum
    }

    ll query(int i,int l,int r){
        if(l<=tree[i].l && tree[i].r<=r) return tree[i].sum;
        int mid=(tree[i].l+tree[i].r)>>1;
        ll res=0;
        push_down(i);//涉及分裂则需要push_down
        //划分成[l,mid],[mid+1,r]
        if(l<=mid)res+=query(ls(i),l,r);
        if(r>mid)res+=query(rs(i),l,r);
        return res;
    }

    void build(int i,int l,int r){
        if(l==r){
            tree[i]={l,r,w[r],0};
            return;
        }
        tree[i]={l,r,0,0};
        int mid=(tree[i].l+tree[i].r)>>1;
        build(ls(i),l,mid);
        build(rs(i),mid+1,r);
        push_up(i);
    }

    explicit SegTree(int size):n(size),tree((size+1)<<2){
        build(1,1,n);
    };
    //重载函数以简化使用
    ll query(int l,int r){return query(1,l,r);}
    void update(int l,int r,ll d){update(1,l,r,d);}
};

//https://www.luogu.com.cn/record/210242245

int main(){
    int n,q;
    cin >> n>>q;
    for(int i=1;i<=n;i++)cin >> w[i];
    SegTree seg(n);
    ll op,x,y,k;
    while(q--){
        cin >> op>>x>>y;
        if(op==1){
            cin >> k; 
            seg.update(x,y,k);
        }else{
            cout << seg.query(x,y) << endl;
        }
    }
}


