#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000;
int cnt[maxn];
string d = "SWNE";

void work() {
    int res = 0;
    for (auto &v : d)
        if (cnt[v]) res++;
    if (res == 3) {
        for (auto &v : d) {
            if (!cnt[v]) {
                cout << v << endl;
            }
        }
        return;
    }
    if (res == 2) {
        if ((cnt['S'] && cnt['N']) || (cnt['W'] && cnt['E'])) {
            cout << "X" << endl;
            return;
        } else {
            for (auto &v : d) {
                if (!cnt[v]) {
                    cout << v;
                }
            }
            cout << endl;
            return;
        }
    }
    cout << "X" << endl;
    return;
}
int main() {
    string line;
    cin >> line;
    for (auto &v : line) cnt[v]++;
    work();
}
