#include <bits/stdc++.h>
using namespace std;

vector<long long> prime = {437359931, 483577261, 490845269, 512059357,
                           534387017, 698987533, 764016151, 906097321,
                           914067307, 954169327};

using ll = long long;
ll pow(ll a, ll n, ll mod) {
    ll t = 1;
    for (; n; n >>= 1, (a *= a) %= mod)
        if (n & 1) (t *= a) %= mod;
    return t;
}

int main() {
    string n;
    cin >> n;
    bool flag = true;
    for (auto& p : prime) {
        long long x = 0;
        for (auto& ch : n) x = (x * 10 + ch - '0') % p;
        if (pow(x, (p - 1) / 2, p) != 1) flag = false;
    }
    if (flag)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
