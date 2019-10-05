#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;

int dp[maxn][maxn];
int path[maxn][maxn];
int x[maxn], y[maxn];

int dfs(int l, int r) {
    if (l >= r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int ans = INT_MAX, k;
    for (int i = l; i < r; i++) {
        int res = dfs(l, i) + dfs(i + 1, r) + x[i] - x[l] + y[i + 1] - y[r];
        if (res < ans) {
            ans = res;
            k = i;
        }
    }
    path[l][r] = k;
    return dp[l][r] = ans;
}

vector<pair<pair<int, int>, pair<int, int>>> ans;

void add(int x1, int y1, int x2, int y2) {
    if (x1 < x2) swap(x1, x2), swap(y1, y2);
    assert(x1 >= x2 && y1 >= y2);
    assert(x1 == x2 || y1 == y2);
    if (x1 == x2 && y1 == y2) return;
    ans.push_back({{x1, y1}, {x2, y2}});
}

void dfs2(int l, int r) {
    if (l >= r) return;
    int k = path[l][r];

    add(x[k], y[k], x[l], y[k]);
    add(x[k + 1], y[k + 1], x[k + 1], y[r]);

    dfs2(l, k);
    dfs2(k + 1, r);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
    if (n == 1) {
        add(x[1], y[1], 0, y[1]);
        add(0, y[1], 0, 0);
        printf("%d %d\n", static_cast<int>(ans.size()), x[1] + y[1]);
        for (auto& t : ans) {
            printf("%d %d %d %d\n", t.first.first, t.first.second,
                   t.second.first, t.second.second);
        }
        return 0;
    }
    dfs(1, n);
    add(x[1], y[1], x[1], y[n]);
    add(x[n], y[n], x[1], y[n]);
    add(x[1], y[n], x[1], 0);
    add(x[1], 0, 0, 0);
    dfs2(1, n);
    printf("%d %d\n", static_cast<int>(ans.size()), dp[1][n] + x[n] + y[1]);
    for (auto& t : ans) {
        printf("%d %d %d %d\n", t.first.first, t.first.second, t.second.first,
               t.second.second);
    }
}
