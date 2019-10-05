#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 6;
char s[maxn], t1[maxn], t2[maxn];

struct KMP {
    int nxt[maxn];
    void initkmp(char x[], int m) {
        int i = 0, j = nxt[0] = -1;
        while (i < m) {
            while (j != -1 && x[i] != x[j]) j = nxt[j];
            nxt[++i] = ++j;
        }
    }
    vector<int> kmp(char x[], int m, char y[], int n) {
        int i, j;
        i = j = 0;
        vector<int> ret;
        initkmp(x, m);
        while (i < n) {
            while (j != -1 && y[i] != x[j]) j = nxt[j];
            i++, j++;
            if (j >= m) {
                ret.push_back(i);
                j = nxt[j];
            }
        }
        return ret;
    }
} kmp;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        scanf("%s", t1);
        scanf("%s", t2);
        int sn = strlen(s);
        int t1n = strlen(t1);
        int t2n = strlen(t2);
        vector<int> v1 = kmp.kmp(t1, t1n, s, sn);
        vector<int> v2 = kmp.kmp(t2, t2n, s, sn);
        if (v1.empty() || v2.empty()) {
            puts("NO");
            continue;
        }

        if (*v1.begin() + t2n <= *v2.rbegin() ||
            *v2.begin() + t1n <= *v1.rbegin())
            puts("YES");
        else
            puts("NO");
    }
}
