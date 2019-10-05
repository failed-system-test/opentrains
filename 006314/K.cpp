#include <bits/stdc++.h>

const int MAXN = 1000;

int n, m;
char a[MAXN], b[MAXN], k[MAXN];

int main() {
    std::scanf("%d%d", &n, &m);
    std::scanf("%s%s", a + (m - n), b);
    for (int i = m - n; i < m; ++i) a[i] -= 'a';
    for (int i = 0; i < m; ++i) b[i] -= 'a';

    for (int i = m - 1; i >= m - n; --i) k[i] = (b[i] - a[i] + 26) % 26;
    for (int i = m - n - 1; i >= 0; --i) {
        a[i] = k[i + n];
        k[i] = (b[i] - a[i] + 26) % 26;
    }

    for (int i = 0; i < m; ++i) std::putchar(a[i] + 'a');
    std::putchar('\n');
}
