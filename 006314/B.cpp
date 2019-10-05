#include <bits/stdc++.h>

const int MAXN = 400005;
std::vector<int> G[MAXN];
int e[MAXN];
int d[MAXN];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 0, m; i < n; i++) {
        std::cin >> e[i];
        std::cin >> m;
        for (int j = 0, b; j < m; j++) {
            std::cin >> b;
            G[i].push_back(b - 1);
            d[b - 1]++;
        }
    }
    std::priority_queue<std::pair<int, int>> q;
    for (int i = 0; i < n; i++)
        if (!d[i]) q.emplace(-e[i], i);
    int p = n, ans = 0;
    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        --p;
        int u = t.second;
        ans = std::max(ans, p - t.first);
        for (auto& v : G[u])
            if (!--d[v]) q.emplace(-e[v], v);
    }
    std::cout << ans << std::endl;
}
