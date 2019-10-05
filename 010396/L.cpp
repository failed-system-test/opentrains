#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
int a[maxn][maxn];
int vis[maxn * maxn];
int tot;
int b[maxn * maxn];

struct Node {
    int up, down, l, r;
    Node() {
        up = 1e9, l = 1e9;
        down = -1, r = -1;
    }
} comp[maxn * maxn];

void work(int t, int r, int c) {
    comp[t].up = min(comp[t].up, r);
    comp[t].down = max(comp[t].down, r);
    comp[t].l = min(comp[t].l, c);
    comp[t].r = max(comp[t].r, c);
}
bool in(int i, int j) {
    auto &m1 = comp[i], &m2 = comp[j];
    if (m1.up < m2.up) return false;
    if (m1.down > m2.down) return false;
    if (m1.l < m2.l) return false;
    if (m1.r > m2.r) return false;
    return true;
}

int cal(int t) {
    int ret = 0;
    for (int i = comp[t].up; i <= comp[t].down; i++) {
        for (int j = comp[t].l; j <= comp[t].r; j++) {
            int tmp = a[i][j];
            if (t == tmp || vis[tmp] == t) continue;
            vis[tmp] = t;
            if (in(tmp, t)) ret++;
        }
    }
    return ret;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            b[tot++] = a[i][j];
        }
    }
    sort(b, b + tot);
    int sz = unique(b, b + tot) - b;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = lower_bound(b, b + sz, a[i][j]) - b + 1;
            work(a[i][j], i, j);
        }
    }
    long long ans = 0;
    for (int i = 1; i <= sz; i++) ans += cal(i);

    printf("%lld\n", ans);
}
/*
3 4
1 2 2 4
1 1 1 4
5 1 7 4
*/
