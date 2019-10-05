#include <bits/stdc++.h>

const int MAXN = 101000;

int n, m;
std::vector<std::tuple<int, int, int>> edges[MAXN];

void addEdge(int u, int v, int value, int index) {
    edges[u].emplace_back(v, value, index);
    edges[v].emplace_back(u, value, index);
}

int color[MAXN];
void dfs1(int u, int c = 0) {
    color[u] = c;
    for (auto&& t : edges[u]) {
        int v = std::get<0>(t), value = std::get<1>(t);
        if (color[v] >= 0) {
            if (color[v] != (c ^ value)) throw - 1;

        } else {
            dfs1(v, c ^ value);
        }
    }
}

bool visited[MAXN];
bool rs[MAXN];
void dfs2(int u) {
    visited[u] = true;
    for (auto&& t : edges[u]) {
        int v = std::get<0>(t), index = std::get<2>(t);
        if (visited[v]) continue;
        rs[index] = false;
        dfs2(v);
    }
}

int main() {
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);

    std::scanf("%d%d", &n, &m);

    for (int i = 0; i < m; ++i) {
        char op[10];
        std::scanf("%s", op);
        if (op[0] == 'h') {
            int u;
            std::scanf("%d", &u);
            --u;
            addEdge(u, n, 0, i);

        } else if (op[0] == 'v') {
            int u;
            std::scanf("%d", &u);
            --u;
            addEdge(u, n, 1, i);

        } else if (op[1] == 'a') {
            int u, v;
            std::scanf("%d%d", &u, &v);
            --u, --v;
            addEdge(u, v, 0, i);

        } else {
            int u, v;
            std::scanf("%d%d", &u, &v);
            --u, --v;
            addEdge(u, v, 1, i);
        }
    }

    try {
        for (int i = 0; i <= n; ++i) color[i] = -1;
        for (int i = 0; i <= n; ++i)
            if (color[i] == -1) dfs1(i);

        for (int i = 0; i <= n; ++i) visited[i] = false;
        for (int i = 0; i < m; ++i) rs[i] = true;
        for (int i = 0; i <= n; ++i)
            if (!visited[i]) dfs2(i);

        std::vector<int> result;
        for (int i = 0; i < m; ++i)
            if (rs[i]) result.push_back(i);

        std::puts("consistent");
        std::printf("%d\n", int(result.size()));
        for (int i = 0; i < int(result.size()); ++i)
            std::printf("%d%c", result[i] + 1,
                        " \n"[i == int(result.size() - 1)]);

    } catch (...) {
        std::puts("inconsistent");
    }
}
