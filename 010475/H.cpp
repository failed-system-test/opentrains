#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 251000;

int n;
int arr[2][MAXN];
int id[2][MAXN];
int pm[2];

i64 calc() {
    
    i64 result = 0;
    int cur = 0;
    for(int i = 0; i < n; ++i) {
        
        if(id[0][i] == id[1][i]) {
            
            if(id[0][i]) ++cur;
            else --cur;
            
        }
        result += std::abs(cur);
        
    }
    return result;
    
}

int main() {
    
    std::scanf("%d", &n);
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < n; ++j)
            std::scanf("%d", &arr[i][j]);
    
    if(n & 1) {
        
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < n; ++j)
                if(arr[i][j] == n / 2 + 1) { pm[i] = j; break; }
        
    }
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < n; ++j)
            id[i][j] = arr[i][j] > n / 2;
    
    i64 result = 1e18;
    if(n & 1) {
        
        id[0][pm[0]] = 0, id[1][pm[1]] = 1;
        result = std::min(result, calc());
        id[0][pm[0]] = 1, id[1][pm[1]] = 0;
        result = std::min(result, calc());
        
    } else result = std::min(result, calc());
    std::printf("%lld\n", result);
    
}
