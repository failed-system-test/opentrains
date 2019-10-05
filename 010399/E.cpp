#include <bits/stdc++.h>

const int MAXN = 101000;
const int MINX = 33, MAXX = 126;

int l, n;
char s[MAXN], t[MAXN];
int next[MAXN * 2][MAXX - MINX + 1];

int main() {
    std::scanf("%[^\n]", s);
    while (std::getchar() != '\n')
        ;
    l = std::strlen(s);

    for (int i = 0; i <= MAXX - MINX; ++i) next[l * 2][i] = -1;
    for (int i = l * 2 - 1; i >= 0; --i) {
        std::memcpy(next[i], next[i + 1], sizeof(next[i]));
        int x = s[i % l] - MINX;
        next[i][x] = i;
    }

    long long result = 0;
    while (~std::scanf("%[^\n]", t)) {
        while (std::getchar() != '\n')
            ;
        n = std::strlen(t);
        if (!n) break;
        int cur = result % l;
        int d = 0;
        for (int i = 0; i < n; ++i) {
            if (t[i] == ' ') continue;
            int x = t[i] - MINX;
            int pos = (cur + i) % l;
            d = std::max(d, next[pos][x] - pos);
        }
        result += d + 1;
        t[0] = 0;
    }
    std::cout << result << std::endl;
}
