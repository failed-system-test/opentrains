#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string a, b;
    cin >> a >> b;
    int cnta = 0, cntb = 0;
    for (int i = 0; i < 6; i++) {
        if (a[i] > b[i])
            cnta++;
        else if (a[i] < b[i])
            cntb++;
    }
    cout << cntb << '\n' << cnta << endl;
}
