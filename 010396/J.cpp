#include <bits/stdc++.h>

const int MAXN = 10001000;

using i64 = long long;

unsigned int s;
unsigned int getNext() {
    s = s ^ (s << 13);
    s = s ^ (s >> 17);
    s = s ^ (s << 5);
    return s;
}

int n, m;
i64 minw[MAXN];
int mini[MAXN];
unsigned int result[(MAXN + 31) / 32];

int main() {
    std::scanf("%d%d%u", &n, &m, &s);
    for (int i = 0; i < n; ++i) minw[i] = LONG_LONG_MAX, mini[i] = -1;

    for (int i = 0; i < m; ++i) {
        int u = getNext() % n;
        int v = getNext() % n;
        i64 w = getNext() / 4;
        w = w * getNext();
        if (u != v) {
            if (minw[u] > w) minw[u] = w, mini[u] = i;
            if (minw[v] > w) minw[v] = w, mini[v] = i;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (mini[i] < 0) continue;
        int x = mini[i];
        result[x >> 5] |= 1u << (x & 31);
    }
    int c = (m + 31) / 32;
    for (int i = 0; i < c; ++i)
        std::printf("%u%c", result[i], " \n"[i == c - 1]);
}
