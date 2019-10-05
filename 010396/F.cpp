#include <bits/stdc++.h>

template <size_t SEED, size_t MOD>
class Hash {
   private:
    std::vector<size_t> p, h;

   public:
    Hash() {}
    Hash(const std::string& s) : p(s.size() + 1), h(s.size() + 1) {
        int n = s.length();
        p[0] = 1;
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] * SEED % MOD;
        for (int i = 1; i <= n; i++)
            h[i] = (h[i - 1] * SEED % MOD + s[i - 1]) % MOD;
    }
    size_t seed() const { return SEED; }
    size_t mod() const { return MOD; }
    size_t get(int l, int r) {
        return (h[r] - h[l] * p[r - l] % MOD + MOD) % MOD;
    }
    size_t substr(int l, int m) { return get(l, l + m); }
};

using Myhash = Hash<19260817, 1000000009>;

int main() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    Myhash ha(s), hb(std::string(s.rbegin(), s.rend()));
    if (ha.substr(0, n) != hb.substr(0, n)) {
        return std::cout << 1 << std::endl, 0;
    }
    for (int i = 1; i < n - 1; i++) {
        if (ha.substr(0, i) != hb.substr(n - i, i) &&
            ha.substr(i, n - i) != hb.substr(0, n - i)) {
            return std::cout << 2 << std::endl, 0;
        }
    }
    std::cout << -1 << std::endl;
}
