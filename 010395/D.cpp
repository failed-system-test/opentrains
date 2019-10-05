#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
char s[maxn];

int main() {
    scanf("%s", s);
    int n = strlen(s);
    if (n == 1)
        printf("%c\n", s[0]);
    else {
        int num = s[0] - '0';

        bool flag = true;
        for (int j = 1; j < n && num > 1; j++) {
            int x = s[j] - '0';
            if (x == 9 && flag) continue;
            if (num <= x || x == 0) {
                if (flag) num -= 1;
                flag = false;
            } else
                num = x;
            if (num == x) flag = true;
        }
        printf("%d\n", num);
    }
}
