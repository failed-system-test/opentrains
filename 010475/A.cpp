#include <bits/stdc++.h>

const int MAXN = 1000;

int n, m;
char arr[MAXN][MAXN];

void no() {

    std::puts("-1");
    std::exit(0);

}

int main() {

    std::scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i)
        std::scanf("%s", arr[i]);

    int result = 0;
    if((n & 1) && (m & 1))
        if(arr[n / 2][m / 2] != '8') no();
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            
            if(i == n - i - 1 && j == m - j - 1) continue;
            char a = arr[i][j], b = arr[n - i - 1][m - j - 1];
            if(a == '6' && b == '6') ++result;
            else if(a == '6' && b == '9');
            else if(a == '7' && b == '7') ++result;
            else if(a == '8' && b == '8');
            else if(a == '9' && b == '6');
            else if(a == '9' && b == '9') ++result;
            else no();

        }
    result /= 2;
    std::printf("%d\n", result);

}
