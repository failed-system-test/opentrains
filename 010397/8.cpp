#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)

const int maxn = 150000;
const int N = maxn * 40;
int a[maxn], d[maxn];
ll sa[maxn];

int dfn;
ll sum[N], cnt[N];
int lch[N], rch[N], root[maxn];

inline void pushup(int rt) {
    sum[rt] = sum[lch[rt]] + sum[rch[rt]];
    cnt[rt] = cnt[lch[rt]] + cnt[rch[rt]];
}
inline void newnode(int old, int k) {
    lch[k] = lch[old];
    rch[k] = rch[old];
    sum[k] = sum[old];
    cnt[k] = cnt[old];
}
void update(int old, int &k, int l, int r, int p, int x) {
    k = ++dfn;
    newnode(old, k);
    if (l == r) {
        sum[k] += x;
        cnt[k]++;
        return;
    }
    int m = l + r >> 1;
    if (p <= m)
        update(lch[old], lch[k], l, m, p, x);
    else
        update(rch[old], rch[k], m + 1, r, p, x);
    pushup(k);
}
ll query(int old, int k, int l, int r, int num) {
    if (cnt[k] - cnt[old] <= num) return sum[k] - sum[old];
    if (l == r) return (sum[k] / cnt[k]) * num;
    ll ret = 0;
    int m = l + r >> 1;
    int tmp = cnt[lch[k]] - cnt[lch[old]];
    if (tmp >= num) return query(lch[old], lch[k], l, m, num);
    return sum[lch[k]] - sum[lch[old]] +
           query(rch[old], rch[k], m + 1, r, num - tmp);
}

vector<int> b;
inline int getid(int x) {
    return lower_bound(b.begin(), b.end(), x) - b.begin() + 1;
}

int sz;
ll prek(int l, int r, int k) {
    return query(root[l - 1], root[r], 1, sz, k);
    // ...
}

int main() {
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", d + i);
    for (int i = 1; i <= n; i++) b.push_back(a[i] - d[i]);
    my_sort_unique(b);
    sz = b.size();

    root[0] = 0;
    for (int i = 1; i <= n; i++)
        update(root[i - 1], root[i], 1, sz, getid(a[i] - d[i]), a[i] - d[i]);

    sa[0] = 0;
    for (int i = 1; i <= n; ++i) sa[i] = sa[i - 1] + a[i];

    scanf("%d", &m);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int len = r - l + 1;
        ll result = (sa[r] - sa[l - 1]) * 2 - prek(l, r, len / 3) -
                    prek(l, r, len / 3 * 2);
        if (result & 1)
            std::printf("%lld.5\n", result / 2);
        else
            std::printf("%lld.0\n", result / 2);
    }
}
