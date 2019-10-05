#include <bits/stdc++.h>

using ll = long long;
struct Query {
    int l, r;
};
const int MAXN = 50005;
const int MAXM = 300005;
int a[MAXN][3];
ll ans[MAXM];
Query queries[MAXM];
int d;
void solve(int l, int r, const std::vector<int>& qid) {
    if (l == r) {
        int curans = -1;
        for (int i = 0; i < 3; i++) {
            if (a[l][i] % d == 0) {
                curans = std::max(curans, a[l][i]);
            }
        }
        for (auto&& id : qid) {
            ans[id] = curans;
        }
        return;
    }
    const int m = l + r >> 1;
    static ll leftdp[MAXN][50];   // l <- m
    static ll rightdp[MAXN][50];  // m + 1 -> r

    for (int i = l; i <= m + 1; i++) memset(leftdp[i], 0xc0, sizeof(leftdp[i]));
    for (int i = m; i <= r; i++) memset(rightdp[i], 0xc0, sizeof(rightdp[i]));

    leftdp[m + 1][0] = 0;

    for (int i = m; i >= l; i--) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < 3; k++) {
                leftdp[i][j] = std::max(
                    leftdp[i][j],
                    leftdp[i + 1][(j - (a[i][k] % d) + d) % d] + a[i][k]);
            }
        }
    }

    rightdp[m][0] = 0;

    for (int i = m + 1; i <= r; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < 3; k++) {
                rightdp[i][j] = std::max(
                    rightdp[i][j],
                    rightdp[i - 1][(j - (a[i][k] % d) + d) % d] + a[i][k]);
            }
        }
    }

    std::vector<int> left, right;
    for (auto&& id : qid) {
        if (queries[id].r <= m)
            left.push_back(id);
        else if (queries[id].l > m)
            right.push_back(id);
        else {
            // [l, r]
            ll curans = -1;
            int l = queries[id].l, r = queries[id].r;
            for (int i = 0; i < d; i++) {
                curans =
                    std::max(curans, leftdp[l][i] + rightdp[r][(d - i) % d]);
            }
            ans[id] = curans;
        }
    }
    solve(l, m, left);
    solve(m + 1, r, right);
}

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    ::d = d;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int q;
    scanf("%d", &q);
    std::vector<int> qid;
    for (int i = 0, l, r; i < q; i++) {
        scanf("%d%d", &queries[i].l, &queries[i].r);
        qid.push_back(i);
    }
    solve(1, n, qid);
    for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
}
