#include <bits/stdc++.h>
using namespace std;

map<int, int> cnt;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, x; i < m; i++) {
        scanf("%d", &x);
        cnt[x]++;
    }
    int maxid = 0, maxcnt = 0;
    for (auto &p : cnt) {
        maxcnt = max(maxcnt, p.second);
        maxid = max(maxid, p.first);
    }
    int ans = 0;
    int sq = sqrt(n) + 1;
    for (int i = 1; i <= sq; i++) {
        if (n % i == 0) {
            int num = n / i;
            if (maxid <= i && maxcnt <= num) ans++;
            if (i != num && maxid <= num && maxcnt <= i) ans++;
        }
    }
    if (ans == 1)
        puts("YES");
    else
        puts("NO");
}
