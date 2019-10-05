#include <bits/stdc++.h>
using namespace std;

int getid(int a, int b) {
    if (a < b) return 0;
    if (a == b) return 1;
    if (a > b) return 2;
    assert(false);
    return 0;
}
char getcc(int x) {
    switch (x) {
        case 0:
            return '<';
        case 1:
            return '=';
        case 2:
            return '>';
        default:
            assert(false);
            return 0;
    }
}

int main() {
    string s;
    cin >> s;
    string t = s;
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    vector<int> a(s.length());
    for (int i = 0; i < s.length(); i++)
        a[i] = lower_bound(t.begin(), t.end(), s[i]) - t.begin();
    vector<int> perm(10);
    iota(perm.begin(), perm.end(), 0);
    unordered_map<long long, int> dic;
    do {
        long long h = 0;
        for (int i = 1; i < a.size(); i++)
            h = h * 3 + getid(perm[a[i - 1]], perm[a[i]]);
        dic[h]++;
    } while (next_permutation(perm.begin(), perm.end()));
    for (auto& t : dic) {
        if (t.second == 1) {
            long long x = t.first;
            std::vector<char> vec;
            for (int i = 1; i < int(s.length()); ++i, x /= 3)
                vec.push_back(getcc(x % 3));
            std::cout << s[0];
            for (int i = 1; i < int(s.length()); ++i)
                std::cout << ' ' << vec[s.length() - i - 1] << ' ' << s[i];
            return 0;
        }
    }
    cout << "Impossible" << endl;
}
