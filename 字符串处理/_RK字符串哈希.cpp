#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll p = 31, m = 1e9 + 9, pchar = 7; 
// 质数列表, 字符c[k]对hash的贡献为 (p**k)*asc(c) % m,字符串总hash为所有字符贡献之和 % m
inline ll asc(char c){return (c*pchar)^(3*p*pchar) % m;}//XOR

inline ll binpow(ll a, ll b, ll p=1e9+7) {
    ll res = 1;
    a = a % p; 
    while (b > 0) {
        if (b & 1) res = (res * a) % p; 
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}// 快速幂
int rabinKarp(const std::string& text, const std::string& pattern) {
        
    ll pattern_hash = 0, text_hash = 0;
    ll n = text.size();
    ll pattern_length = pattern.size();

    

    // 计算p的pattern_length-1次幂，用于后续的哈希计算
    ll p_pow = binpow(p, pattern_length - 1, m);

    // 计算文本串第一个子串的哈希值和模式串的哈希值
    for (int i = 0; i < pattern_length; ++i) {
        pattern_hash = (pattern_hash * p + asc(pattern[i])) % m;
        text_hash = (text_hash * p + asc(text[i])) % m;
    }

    // 遍历文本串
    for (int i = 0; i <= n - pattern_length; ++i) {
        // 如果哈希值匹配，则进行详细比对
        if (pattern_hash == text_hash) {
            if (std::equal(pattern.begin(), pattern.end(), text.begin() + i)) {
                return i; // 匹配位置
            }
        }
        // 计算下一个子串的哈希值
        if (i < n - pattern_length) {
            text_hash = (text_hash - p_pow * asc(text[i])) % m;
            while(text_hash < 0) text_hash += m; // 防止负数
            text_hash = (text_hash * p % m + asc(text[i + pattern_length])) % m;
        }
    }
    return -1; // 未找到匹配项
}


int main() {
    std::string text ;
    std::string pattern;
    while(cin >> text >> pattern){
        int position = rabinKarp(text, pattern);
        if (position != -1) {
            std::cout << "Pattern found at index: " << position << std::endl;
        } else {
            std::cout << "Pattern not found." << std::endl;
        }
        
    }return 0;
    
}