#include <bits/stdc++.h>
using namespace std;
#define ll long long

/*
集合-nim游戏：
仅可取S集合中的石子数
nim游戏的必胜态为XOR{ai}!=0
mex({vi}):={vi}中不存在的最小自然数
sg(v):=mex({sg(ui)}),{ui}为v的所有可达状态
集合nim游戏必胜态为XOR{mex(ai)}!=0
*/




int main()
{
    //https://www.luogu.com.cn/problem/AT_arc168_b
    /*
    题目是nim中只能取1~k的石子，求先手必胜的最大k
    sg(i)=i%(k+1)
    由于a!=b时a^b!=0
    仅需无视所有成对的数，让k+1为最大的剩余数即可
    */
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;cin >>n;
    int xum=0,x;
    set<int,greater<int>>a;
    while(n--){
        cin >> x;
        xum^=x;
        if(a.find(x)==a.end())a.insert(x);
        else a.erase(x);
    }
    if(xum!=0)cout<<-1<<endl;
    else{
        if(a.empty())cout<<0<<endl;
        else{
            cout<<*a.begin()-1<<endl;
        }
    }
}