#include <bits/stdc++.h>

const int MAXN = 10100;

int n;
char str[MAXN];
int next[MAXN][3];

int calc(int len, int* arr) {
    int index = 0;
    for (int i = 0;; ++i) {
        for (int j = 0; j < len; ++j) {
            index = next[index][arr[j]] + 1;
            if (!index) return i * i * len;
        }
    }
}

int main() {
    std::scanf("%d%s", &n, str);

    for (int i = 0; i < 3; ++i) next[n][i] = -1;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < 3; ++j) next[i][j] = next[i + 1][j];
        next[i][str[i] - 'a'] = i;
    }

    int result = 0;
    for (int i = 1; i <= 8; ++i) {
        int arr[9] = {};
        while (true) {
            result = std::max(result, calc(i, arr));

            ++arr[0];
            for (int j = 0; j < i; ++j) {
                if (arr[j] < 3) break;
                arr[j] = 0;
                ++arr[j + 1];
            }
            if (arr[i]) break;
        }
    }

    std::printf("%d\n", result);
}
