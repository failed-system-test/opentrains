#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 5;
bool vis[maxn];
int a[maxn];

int main() {
    int n, c, b;
    scanf("%d%d%d", &n, &c, &b);
    for (int i = 1, x; i <= b; i++) scanf("%d", &x), vis[x] = 1;
    int p = 1;
    if (c & 1)
        a[p] = 1, c--, p += 2;
    else
        p++;
    // cerr << "c = " << c << endl;
    for (; p <= n; p++) {
        if (vis[p]) continue;
        if (c) {
            a[p] = 1;
            c -= 2;
            p++;
        } else
            break;
    }
    for (int i = 1; i <= n; i++) printf("%d", a[i]);
    puts("");
}
