#include <bits/stdc++.h>

const int MAXN = 1 << 17;
std::vector<int> G[MAXN];

int dp[MAXN];

void dfs(int u, int fa) {
    dp[u] = 0;
    bool allzero = true;
    for (auto& v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);   
        allzero &= (dp[v] == 0);
        dp[u] += dp[v];
    }
    if (allzero) {
        dp[u] = 1;
    } else {
        dp[u]--;
    }

}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    G[1].push_back(0);
    dfs(1, 0);
    // for (int i = 1; i <= n; i++) printf("%d -> %d\n",i,  dp[i]);
    puts(dp[1] ? "Alice" : "Bob");
}
/*
8
1 2
1 3
2 4
4 5
5 6
5 7
5 8

9
1 2
1 3
2 4
4 5
5 6
5 7
5 8
1 9

*/