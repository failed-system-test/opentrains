#include <bits/stdc++.h>

using i64 = long long;

const std::string dir = "LRDU";
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

inline int getdir(char c) { return dir.find(c); }
std::set<std::pair<int, int>> ans;
std::unordered_map<i64, int> mmm;

i64 getID(int x, int y) {
    x += 1000000000;
    y += 1000000000;
    return i64(1000000000) * x + y;
}

int main() {
    std::string s;
    std::cin >> s;
    int step = 1;
    int x = 0, y = 0;
    mmm.clear();
    ++mmm[getID(0, 0)];
    int lastd = -1;
    for (auto& ch : s) {
        int d = getdir(ch);
        int nx = x + dx[d] * step;
        int ny = y + dy[d] * step;
        for (int i = 1; i <= step; ++i)
            ++mmm[getID(x + dx[d] * i, y + dy[d] * i)];
        ans.emplace(x + dx[d] * (step + 1), y + dy[d] * (step + 1));
        if ((lastd ^ d) != 1) step *= 2;
        lastd = d;
        x = nx, y = ny;
    }
    if (mmm[getID(x, y)] > 1)
        std::puts("impossible");
    else {
        int offsetx = -x, offsety = -y;
        std::printf("%d %d\n", offsetx, offsety);
        std::printf("%d\n", int(ans.size()));
        for (auto&& p : ans)
            std::printf("%d %d\n", p.first + offsetx, p.second + offsety);
    }
}
