#include <bits/stdc++.h>

const int N = 86400;
std::vector<std::pair<int, int>> G[N];
long long dp[N + 1];
int readTime() {
    static int h, m, s;
    scanf("%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int main() {
    int n, c;
    scanf("%d%d", &n, &c);
    for (int i = 0; i < N; i++) G[i].emplace_back(i + 1, 0);
    for (int i = 0, p; i < n; i++) {
        int t1 = readTime();
        int t2 = readTime();
        scanf("%d", &p);
        p -= (t2 - t1) * c;
        G[t1].emplace_back(t2, p);
    }
    for (int i = 0, j, p; i < N; i++) {
        for (auto& e : G[i]) {
            std::tie(j, p) = e;
            dp[j] = std::max(dp[j], dp[i] + p);
        }
    }
    printf("%lld\n", dp[N]);
}
