#include <bits/stdc++.h>

const int MAXN = 1 << 17;
std::vector<std::pair<int, int>> G[MAXN];
std::vector<std::pair<int, int>> GG[MAXN];

std::vector<int> rG[MAXN];

bool bfs(int s, int t) {
    std::queue<int> q;
    static bool vis[MAXN];
    vis[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& [c, v] : G[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    return vis[t];
}

bool can[MAXN];
void rbfs(int s) {
    std::queue<int> q;
    can[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& v : rG[u]) {
            if (!can[v]) {
                can[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0, u, v, c; i < m; i++) {
        scanf("%d%d%d", &u, &v, &c);
        G[u].emplace_back(c, v);
        rG[v].push_back(u);
    }
    if (!bfs(s, t)) {
        puts("IMPOSSIBLE");
        return 0;
    }

    rbfs(t);

    for (int u = 1; u <= n; u++) {
        for (auto& [c, v] : G[u]) {
            if (can[v]) {
                GG[u].emplace_back(c, v);
            }
        }
        std::sort(GG[u].begin(), GG[u].end());
    }

    int u = s;
    std::vector<int> ans;
    ans.reserve(1000000);
    while (u != t && ans.size() <= 1000000) {
        for (auto& [c, v] : GG[u]) {
            if (can[v]) {
                u = v;
                ans.push_back(c);
                break;
            }
        }
    }
    if (ans.size() <= 1000000) {
        for (auto& t : ans) {
            printf("%d ", t);
        }
    } else {
        puts("TOO LONG");
    }
}
