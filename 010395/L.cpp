#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e4 + 5;
using pii = pair<int, int>;
int n, m, k;
vector<pii> g[maxn], G[maxn];
int d[maxn], p[maxn], pw[maxn];

void dij() {
    for (int i = 1; i <= n; i++) d[i] = 1e9, p[i] = 1e9;
    d[1] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto now = pq.top();
        pq.pop();
        int u = now.second;
        if (d[u] < now.first) continue;
        for (auto &V : g[u]) {
            int v = V.second;
            int w = V.first;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                p[v] = u;
                pw[v] = w;
                pq.push({d[v], v});
            } else if (d[v] == d[u] + w && p[v] > u)
                p[v] = u, pw[v] = w;
        }
    }
    for (int i = 2; i <= n; i++)
        G[p[i]].push_back({pw[i], i}), G[i].push_back({pw[i], p[i]});
}

int heavySonSz[maxn], sz[maxn];
int rt, treesz;
bool vis[maxn];

void findrt(int u, int fa) {
    sz[u] = 1, heavySonSz[u] = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].second;
        if (vis[v] || v == fa) continue;
        findrt(v, u);
        sz[u] += sz[v];
        heavySonSz[u] = max(heavySonSz[u], sz[v]);
    }
    heavySonSz[u] = max(heavySonSz[u], treesz - sz[u]);
    if (heavySonSz[u] < heavySonSz[rt]) rt = u;
}
map<int, int, greater<int>> val[maxn];
// multiset<int,greater<int>> val[maxn];
int ans, cnt;

void add(int u, int fa, int w, int h, int sign) {
    if (h > k) return;
    if (sign == 1)
        val[h][w]++;
    else
        val[h][w]--;
    if (val[h][w] == 0) val[h].erase(w);

    for (auto &V : G[u]) {
        int v = V.second;
        if (v == fa || vis[v]) continue;
        add(v, u, w + V.first, h + 1, sign);
    }
}
void cal(int u, int fa, int w, int h) {
    if (h > k) return;
    if (!val[k - h].empty()) {
        auto it = *val[k - h].begin();
        if (it.first + w > ans) {
            ans = it.first + w;
            cnt = it.second;
        } else if (it.first + w == ans) {
            cnt += it.second;
        }
    }

    for (auto &V : G[u]) {
        int v = V.second;
        if (v == fa || vis[v]) continue;
        cal(v, u, w + V.first, h + 1);
    }
}
void solve(int u) {
    vis[u] = 1;
    for (int i = 1; i < G[u].size(); i++) {
        int v = G[u][i].second;
        if (vis[v]) continue;
        int w = G[u][i].first;
        add(v, u, w, 1, 1);
    }
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].second;
        int w = G[u][i].first;
        if (vis[v]) continue;
        if (i) add(v, u, w, 1, -1);
        cal(v, u, w, 1);
        // cerr << "u = " << u << " v = " << v << "  ans = " << ans << " cnt = "
        // << cnt << endl;
    }
    for (auto &V : G[u]) {
        int v = V.second;
        if (vis[v]) continue;
        rt = 0, treesz = sz[v];
        findrt(v, u);
        solve(rt);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }
    dij();
    rt = 0, heavySonSz[rt] = 1e9, treesz = n;
    findrt(1, -1);
    k--;
    val[0][0]++;
    solve(rt);

    printf("%d %d\n", ans, cnt);
}
