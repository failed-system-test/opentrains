#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MAXN = 251000;

using DS = std::multiset<i64, std::greater<>>;

int n;
std::tuple<int, int, int> arr[MAXN];
int cur;

void merge(DS& a,  DS& b) {
    if(a.size() < b.size()) std::swap(a,b);
    auto it1 = a.begin();
    auto it2 = b.begin();
    std::vector<i64> result;

    while(it1 != a.end() && it2 != b.end()) {
        result.push_back(*it1 + *it2);
        it1 = a.erase(it1);
        ++it2;
    }
    for(auto &v:result)
        a.insert(v);
}

DS dfs() {
    
    DS result;
    int r = std::get<1>(arr[cur]);
    int x = std::get<2>(arr[cur]);
    ++cur;
    while(cur < n && std::get<1>(arr[cur]) <= r) {
        
        auto child = dfs();
        merge(result, child);
        
    }
    if(result.empty()) return {x};
    result.insert(x);
    return result;
    
}

int main() {
    
    std::scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        std::scanf("%d%d%d", &std::get<0>(arr[i]), &std::get<1>(arr[i]), &std::get<2>(arr[i]));
    
    std::sort(arr, arr + n, [](const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
        int al = std::get<0>(a), bl = std::get<0>(b);
        int ar = std::get<1>(a), br = std::get<1>(b);
        return al != bl ? al < bl : ar > br;
    });
    
    cur = 0;
    DS result;
    while(cur < n){
        auto child = dfs();
        merge(result, child);
    }
    
    i64 sum = 0;
    int xx = 0;
    for(i64 x : result) {
        
        sum += x;
        std::printf("%lld ", sum);
        ++xx;
        
    }
    for(int i = xx; i < n; ++i)
        std::printf("%lld ", sum);
    
}
