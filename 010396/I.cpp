#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;

unordered_map<int, int> G[maxn];
int cnt[maxn], tot[maxn];
multiset<int> val[maxn];

int main() {
    int n;
    scanf("%d", &n);
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        scanf("%d", &cnt[i]);
        bool ok = 0;
        for (int j = 0, x; j < cnt[i]; j++) {
            scanf("%d", &x);
            tot[x]++;
            G[i][x]++;
            if (G[i][x] > 1) ok = 1;
        }
        if (ok) ans = min(ans, (int)G[i].size() + 1);
        for (auto& v : G[i]) val[v.first].insert(G[i].size());
    }
    for (int i = 0; i < n; i++) {
        // int res = 0, tmp = 0;
        // for(auto &v:G[i])
        //     if(tot[v.first] == 1) tmp++;

        // for (auto &v : G[i]) {
        //     val[v.first].erase(val[v.first].find(G[i].size()));

        //     if (!val[v.first].empty())
        //         res = max(res, tmp + 1 + *val[v.first].begin());

        //     val[v.first].insert(G[i].size());
        // }
        // if (res) ans = min(ans, res + tmp);
        for (auto& v : G[i]) {
            val[v.first].erase(val[v.first].find(G[i].size()));
        }
        std::vector<int> vec;
        for (auto& v : G[i]) {
            if (val[v.first].empty())
                vec.push_back(INT_MAX >> 1);
            else
                vec.push_back(*val[v.first].begin());
        }
        sort(vec.begin(), vec.end());
        int cur = vec.size();
        for (auto& it : vec) it += cur, cur--;
        ans = min(ans, *min_element(vec.begin(), vec.end()));
        for (auto& v : G[i]) {
            val[v.first].insert(G[i].size());
        }
    }
    printf("%d\n", ans);
}
/*
7
4 1 2 3 4
1 1
1 2
1 3
1 4
7 4 7 4 4 7 7 4
1 5
*/
