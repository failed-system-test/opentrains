#include <bits/stdc++.h>

using i64 = long long;

const i64 INF = 1000000000000000000;
const int MAXN = 600;

int n, s1, s2;
int x[MAXN], t[MAXN], y[MAXN], r[MAXN];
i64 dp[2][MAXN][MAXN];

void update(i64& a, i64 b) { a = std::min(a, b); }

struct Object {
    int x, t, y, r;
    void read() {
        std::scanf("%d%d%d%d", &x, &t, &y, &r);
    }
    bool operator < (const Object& rhs) const {
        return x < rhs.x;
    }
} object[MAXN];

int main() {
    std::scanf("%d%d%d", &n, &s1, &s2);
    clock_t st = clock();
    i64 result = INF;
    for(int i = 0; i < n; ++i) object[i].read();
    std::sort(object, object + n);
    for(int i = 0; i <= s1; ++i)
        for(int j = 0; j <= s2; ++j)
            dp[0][i][j] = INF;
    dp[0][0][0] = 0;
    for(int tt = 0; tt < n; ++tt) {
        int cur = tt & 1, next = !cur;
        for(int i = 0; i <= s1; ++i)
            for(int j = 0; j <= s2; ++j)
                dp[next][i][j] = INF;
        for(int i = 0; i <= s1; ++i)
            for(int j = 0; j <= s2; ++j) {
                i64 xx = dp[cur][i][j];
                if(xx == INF) continue;
                update(dp[next][i][j], xx);
                if(i < s1) {
                    int ii1 = i + object[tt].x, jj1 = j;
                    if(ii1 > s1) jj1 = std::min(s2, jj1 + (ii1 - s1)), ii1 = s1;
                    update(dp[next][ii1][jj1], xx + object[tt].t);
                }
                int ii2 = i, jj2 = std::min(s2, j + object[tt].y);
                update(dp[next][ii2][jj2], xx + object[tt].r);
            }
    }
    result = std::min(result, dp[n & 1][s1][s2]);
    if(result == INF) result = -1;
    std::printf("%lld\n", result);

}
