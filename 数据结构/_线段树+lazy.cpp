#include<bits/stdc++.h>
typedef long long ll;

//线段树
using namespace std;
const int N=1e6+10;
ll a[N];
class SegTree{
    public:
        ll n;
        vector<ll> tree,tag;

        inline ll ls(ll i){return i<<1;}
        inline ll rs(ll i){return i<<1|1;}
        void push_up(ll i){
            //以求和为例
            tree[i]=tree[ls(i)]+tree[rs(i)];
        }
        //void push_up_min(ll x){tree[x]=min(tree[ls(x)],tree[rs(x)]);}

        inline void change(ll i,ll l,ll r,ll k){
            //以求和为例
            tag[i]=tag[i]+k;
            tree[i]=tree[i]+k*(r-l+1);
        }
        inline void push_down(ll i,ll l,ll r){
            if(tag[i]){
                ll mid=(l+r)>>1;
                change(ls(i),l,mid,tag[i]);
                change(rs(i),mid+1,r,tag[i]);
                tag[i]=0;
            }
        }
        void update(ll i,ll l,ll r,ll ql,ll qr,ll k){
            //以求和为例
            if(ql<=l&&r<=qr){
                change(i,l,r,k);
                return;
            }
            push_down(i,l,r);
            ll mid=(l+r)>>1;
            if(ql<=mid)update(ls(i),l,mid,ql,qr,k);
            if(qr>mid)update(rs(i),mid+1,r,ql,qr,k);
            push_up(i);
        }
        ll query(ll i,ll l,ll r,ll ql,ll qr){
            if(ql<=l&&r<=qr)return tree[i];
            ll mid=(l+r)>>1;
            ll res=0;
            push_down(i,l,r);
            //以求和为例
            if(ql<=mid)res+=query(ls(i),l,mid,ql,qr);
            if(qr>mid)res+=query(rs(i),mid+1,r,ql,qr);
            return res;
        }
        void build(ll i,ll l,ll r){
            if(l==r){tree[i]=a[l];return;}
            ll mid=(l+r)>>1;
            build(ls(i),l,mid);
            build(rs(i),mid+1,r);
            push_up(i);
        }

        explicit SegTree(ll size):n(size),tree((size+1)<<2),tag((size+1)<<2,0){
            build(1,1,n);
        };
        //重载函数以简化使用
        ll query(ll l,ll r){return query(1,1,n,l,r);}
        void update(ll l,ll r,ll k){update(1,1,n,l,r,k);}
};


int main(){
    int n,q;
    cin >> n>>q;
    for(int i=1;i<=n;i++)cin >> a[i];
    SegTree seg(n);
    int op,x,y,k;
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


