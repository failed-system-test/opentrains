#include <bits/stdc++.h>

constexpr unsigned long long ONE = 1ULL;
const int mod = 1e9 + 7;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n < m) std::swap(n, m);
    std::map<std::pair<int, unsigned long long>, int> dp[2];
    int o = 0;
    dp[o].clear();
    dp[o][std::make_pair(0, ONE << ((1 << m) - 1))] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[o ^ 1].clear();
            for (auto& it : dp[o]) {
                int who = it.first.first;
                unsigned long long mask = it.first.second;
                int value = it.second;
                for (int k = 0; k < 2; k++) {
                    unsigned long long nmask = 0;
                    for (int x = 0; x < (1 << m); x++) {
                        if (mask >> x & 1) {
                            if (x >> j & 1) {
                                nmask |= (ONE << (x ^ (1 << j)));
                                if (j && !(x >> (j - 1) & 1) &&
                                    (who >> (j - 1) & 1) == k) {
                                    nmask |= (ONE << (x ^ (1 << (j - 1))));
                                }
                            } else {
                                if ((who >> j & 1) == k) {
                                    nmask |= (ONE << (x ^ (1 << j)));
                                }
                            }
                        }
                    }
                    (dp[o ^ 1][std::make_pair(who ^ (who & (1 << j)) ^ (k << j),
                                              nmask)] += value) %= mod;
                }
            }
            o ^= 1;
        }
    }
    int ans = 0;
    for (auto& it : dp[o]) {
        if (it.first.second >> ((1 << m) - 1) & 1) {
            (ans += it.second) %= mod;
        }
    }
    printf("%d\n", ans);
}
