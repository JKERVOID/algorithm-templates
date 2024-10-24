#include<bits/stdc++.h>
using namespace std;
#define ll long long

void computeNext(const std::string& pattern, std::vector<int>& next) {
    int m = pattern.size();
    next.resize(m, -1);
    int j = -1;
    int k = -1;
    for (int i = 0; i < m - 1; ++i) {
        while (k >= 0 && pattern[i] != pattern[k]) {
            k = next[k];
        }
        if (pattern[i] == pattern[k]) {
            ++k;
        }
        if (j >= 0 && i == k) {
            next[i] = next[j];
        } else {
            next[i] = k;
        }
        j = (k > j) ? k : j;
    }
}

// KMP搜索算法
int KMP(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0;
    std::vector<int> next;
    computeNext(pattern, next); // 构建部分匹配表
    int i = 0;  // text的索引
    int j = 0;  // pattern的索引
    while (i < n && j < m) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            return i - j; // 匹配成功，返回匹配的起始索引
        }
        if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = next[j - 1];
            } else {
                i++;
            }
        }
    }
    return -1; // 未找到匹配项
}

int main() {
    std::string text ;
    std::string pattern;
    while(cin >> text >> pattern){
        int position = KMP(text, pattern);
        if (position != -1) {
            std::cout << "Pattern found at index: " << position << std::endl;
        } else {
            std::cout << "Pattern not found." << std::endl;
        }
        
    }return 0;
    
}