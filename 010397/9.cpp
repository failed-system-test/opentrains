#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll pow(ll a, ll n, ll mod) {
    a %= mod;
    ll t = 1;
    for (; n; n >>= 1, (a *= a) %= mod)
        if (n & 1) (t *= a) %= mod;
    return t;
}

const int p_max = 1e7 + 1;
ll prime[p_max], p_sz;
void init() {
    static bool vis[p_max];
    for (int i = 2; i < p_max; i++) {
        if (!vis[i]) prime[p_sz++] = i;
        for (int j = 0; j < p_sz; j++) {
            if (prime[j] * i >= p_max) break;
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

bool check(int q, int n, int p) {
    if (n == 1) return true;
    if (q % p == 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (pow(q, i, p) == 1) return false;
        if (pow(q, n / i, p) == 1) return false;
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    vector<int> ans;
    init();
    int q, n;
    scanf("%d%d", &q, &n);
    for (int i = 0; i < p_sz; i++) {
        if (pow(q, n, prime[i]) == 1) {
            if (check(q, n, prime[i])) {
                ans.push_back(prime[i]);
            }
        }
    }
    printf("%d\n", (int)ans.size());
    for (auto& t : ans) printf("%d ", t);
}
