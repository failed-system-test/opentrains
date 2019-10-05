#include <bits/stdc++.h>

const int MAXN = 1000;

int n, m, k;
char mat[MAXN][MAXN];

void no() {
    std::puts("NO");
    std::exit(0);
}

int main() {
    std::scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i) std::scanf("%s", mat[i]);

    int sum1 = 0;
    std::vector<int> vec1 = {0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) sum1 += mat[i][j] == '1';
        int next = int(vec1.size()) * k;
        if (sum1 > next)
            no();
        else if (sum1 == next)
            vec1.push_back(i + 1);
    }
    int sum2 = 0;
    std::vector<int> vec2 = {0};
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) sum2 += mat[j][i] == '1';
        int next = int(vec2.size()) * k;
        if (sum2 > next)
            no();
        else if (sum2 == next)
            vec2.push_back(i + 1);
    }

    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) {
            int s = 0;
            for (int x = vec1[i]; x < vec1[i + 1]; ++x)
                for (int y = vec2[j]; y < vec2[j + 1]; ++y)
                    s += mat[x][y] == '1';
            if (s != 1) no();
        }

    std::puts("YES");
    for (int i = 1; i < k; ++i) std::printf("%d%c", vec1[i], " \n"[i == k - 1]);
    for (int i = 1; i < k; ++i) std::printf("%d%c", vec2[i], " \n"[i == k - 1]);
}
