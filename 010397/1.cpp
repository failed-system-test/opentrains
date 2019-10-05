#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5;

int mat[MAXN][MAXN];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        vector<int> x(4), y(4);
        for (int j = 0; j < 4; ++j) std::scanf("%d%d", &x[j], &y[j]);
        ++x[1], ++y[1], ++x[3], ++y[3];
        vector<int> xx = x, yy = y;
        std::sort(xx.begin(), xx.end());
        xx.resize(std::unique(xx.begin(), xx.end()) - xx.begin());
        std::sort(yy.begin(), yy.end());
        yy.resize(std::unique(yy.begin(), yy.end()) - yy.begin());
        for (int j = 0; j < 4; ++j) {
            x[j] = std::lower_bound(xx.begin(), xx.end(), x[j]) - xx.begin();
            y[j] = std::lower_bound(yy.begin(), yy.end(), y[j]) - yy.begin();
        }
        for (int a = 0; a < MAXN; ++a)
            for (int b = 0; b < MAXN; ++b) mat[a][b] = 0;
        for (int j = 0; j < 2; ++j) {
            for (int a = x[j * 2]; a < x[j * 2 + 1]; ++a)
                for (int b = y[j * 2]; b < y[j * 2 + 1]; ++b)
                    mat[a][b] |= 1 << j;
        }
        int count[4] = {};
        for (int a = 0; a < MAXN; ++a)
            for (int b = 0; b < MAXN; ++b) ++count[mat[a][b]];
        if (!count[1])
            std::puts("A in B");
        else if (!count[2])
            std::puts("B in A");
        else if (!count[3])
            std::puts("Separate");
        else
            std::puts("Intersect");
    }
}