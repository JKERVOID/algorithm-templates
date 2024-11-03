#include<bits/stdc++.h>
using namespace std;
using ll =long long;

/*
KM算法
问题：解决二分图最大权完美匹配问题
复杂度：O(n^4),平均复杂度可以到O(n^3),网络流优化后复杂度到严格O(n^3)
过程：
    1. 维护vl[]vr[]表示左部点和右部点顶标
        > vl[i]+vr[j]==w[i][j]表示可以纳入交错路的边
    2. sl[]sr[]标记本轮是否被访问
    3. match[]表示右部点此时的匹配点
    4. 初始化所有左部点顶标为所有临边中的最大值
    5. 循环左部点,记为i：
        A. 初始化sl[]sr[]
        B. 匈牙利算法dfs确定i是否可以无损纳入匹配，如果可以则进入下一个i
            > 注意考虑可以纳入交错路的边的条件
        C. 如果不能,找到一组点，满足：
            i) 左部点l在B所求的交错路中
            ii) 右部点r不在B所求的交错路中
            iii) 损失loss:=vl[l]+vr[l]-w[l][r],最小
        D. 所有在B所求的交错路中的左部点j的顶标vl[j]减去loss
           所有在B所求的交错路中的右部点j的顶标vr[j]加上loss
        E. 返回A解决match[r]的失配(感觉这里可以优化)
        
[*特别说明]：
    1. 5.B可以使用网络流做法降低复杂度到O(n^3)
    2. 需要用临接矩阵存储
    3. 要求题目有完美匹配，如果没有需要增加点至左部点数量等于右部点
*/

class HK{
public:
    const int INF=0x3f3f3f3f; 
    vector<vector<int>>w;
    vector<int>vl,vr;
    vector<int>match;
    vector<bool>sl,sr;
    int n;

    explicit HK(int n,vector<vector<int>>&w):n(n),w(w){
        match.resize(n+1,0);
        vl.resize(n+1,-INF),vr.resize(n+1,0);//使得负边权可以适用
        sl.resize(n+1,0);sr.resize(n+1,0);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                vl[i]=max(vl[i],w[i][j]);

        
        for(int i=1;i<=n;i++){
            while(1){
                for(int j=1;j<=n;j++)
                    sl[j]=sr[j]=0;
                if(dfs(i))break;

                int loss=INF;
                for(int l=1;l<=n;l++)   if(sl[l])
                  for(int r=1;r<=n;r++)   if(!sr[r])
                    loss=min(loss,vl[l]+vr[r]-w[l][r]);
                if(loss==INF)   throw std::invalid_argument("cannot perfectly match");
                for(int j=1;j<=n;j++){
                    if(sl[j])vl[j]-=loss;
                    if(sr[j])vr[j]+=loss;
                }
            }
        }
    }

    bool dfs(int l){
        sl[l]=1;
        for(int r=1;r<=n;r++){
            if(!sr[r] && vl[l]+vr[r]==w[l][r]){
                sr[r]=1;
                if(match[r]==0 || dfs(match[r])){
                    match[r]=l;
                    return 1;
                }
            }
        }
        return 0;
    }

    ll sum_w(){
        ll sum=0;
        for(int i=1;i<=n;i++)
            sum+=(ll)w[match[i]][i];
        return sum;
    }
};


int main(){
    int n,m;
    while(1){
        cin >> n >>m;
        if(n==0 && m==0)break;
        vector<string> mp(n);
        for(auto &s:mp){
            cin >> s;
        }
            
        int cnt=0;
        vector<pair<int,int>>h;
        h.push_back({0,0});
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                char ch=mp[i][j];
                if(ch=='H'){
                    h.push_back({i,j});
                    cnt++;
                }
            }
        int r=0;
        vector<vector<int>>w(cnt+1,vector<int>(cnt+1));
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                char ch=mp[i][j];
                if(ch=='m'){
                    r++;
                    for(int l=1;l<=cnt;l++){
                        int dis = abs(h[l].first-i) + abs(h[l].second-j);
                        w[l][r]=-dis;
                    }
                }
            }
        HK hk(cnt,w);
        
        cout<<-hk.sum_w()<<endl;
    }
}
