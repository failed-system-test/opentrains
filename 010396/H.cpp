#include <bits/stdc++.h>

using i64 = long long;

const int MAXM = 101000;
const int MAXK = 101000;

int n, m, k, d;
int c[MAXM], a[MAXK];

int main() {
    std::scanf("%d%d%d%d", &n, &m, &k, &d);
    for (int i = 0; i < m; ++i) std::scanf("%d", &c[i]);
    a[0] = 1;
    for (int i = 1; i <= k; ++i) std::scanf("%d", &a[i]);
    a[k + 1] = n;

    if (n - 1 <= d)
        std::puts("0");
    else {
        std::sort(c, c + m);
        std::sort(a + 1, a + k + 1);

        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        int index = 1;
        while (index <= k && a[index] <= d + 1) pq.push(a[index]), ++index;
        for (; index <= k; ++index) {
            while (!pq.empty()) {
                int x = pq.top();
                pq.pop();
                if (a[index] - x <= d) {
                    pq.push(a[index]);
                    break;
                }
            }
            if (pq.empty()) break;
        }
        while (!pq.empty() && n - pq.top() > d) pq.pop();
        i64 result = 0;
        if (pq.empty()) {
            for (int i = 0; i <= k; ++i)
                if (a[i + 1] - a[i] > d) result += c[0];
            for (int i = 1; i < m; ++i) result += c[i];

        } else {
            int cnt = std::max(0, m - int(pq.size()));
            for (int i = 0; i < cnt; ++i) result += c[i];
        }
        std::printf("%lld\n", result);
    }
}