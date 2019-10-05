#include <bits/stdc++.h>
using i64 = long long;

i64 a, b;

int main() {
    std::scanf("%lld%lld", &a, &b);
    --a, --b;
    i64 r = a + b + 1;
    i64 base = (r * r - r) / 2 + 1;
    i64 result = 0;
    if (r & 1)
        result = base + b;
    else
        result = base + a;
    std::printf("%lld\n", result);
}
