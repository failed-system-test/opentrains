#include <bits/stdc++.h>

#define NO exit((puts("NO"), 0))

int t[26];
char s[1 << 20];

int main() {
    scanf("%s", s);
    int n = std::strlen(s) / 2;
    if (n <= 2) {
        std::sort(s, s + n * 2);
        do {
            std::string str(s);
            str = str + str.substr(0, n - 1);
            if ([](std::string str, int n) -> bool {
                std::set<std::string> dic;
                for (int i = 0; i < n * 2; i++) {
                    if(dic.count(str.substr(i, n))) return false;
                    dic.insert(str.substr(i, n));
                }
                return true;
            }(str, n)) {
                puts("YES");
                puts(s);
                exit(0);
            } 
        } while(std::next_permutation(s, s + n * 2));
        puts("NO");
        return 0;
    }
    for (int i = 0; s[i]; i++) t[s[i] - 'a']++;
    int mm = *std::max_element(t, t + 26);
    if (mm == n * 2) NO;
    if (mm == n * 2 - 1) NO;
    if (mm == n * 2 - 2) {
        for (int i = 0; i < 26; i++) {
            if (t[i] == 2) NO;
        }
    }
    puts("YES");
    int index = -1;
    for (int i = 0; i < 26; i++) {
        if (t[i] >= n) index = i;
    }
    if (~index) {
        for (int i = 0; i < n; i++) {
            std::putchar(index + 'a');
            --t[index];
        }
        for (int i = 0; i < 26; i++) {
            if (i != index && t[i]) {
                std::putchar(i + 'a');
                --t[i];
                break;
            }
        }
        while(t[index] && t[index]--) {
            std::putchar(index + 'a');
        }
        for (int i = 0; i < 26; i++) {
            while(t[i] && t[i]--) {
                std::putchar(i + 'a');
            }
        }
        std::puts("");
    } else {
        std::sort(s, s + n * 2);
        std::puts(s);
    }
     
}
