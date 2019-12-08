#include <bits/stdc++.h>

const int MAXN = 110;

struct Pos { int x, y, z; };

int n, m, h;
char mat[2][MAXN][MAXN];
std::vector<int> pos[2][MAXN];

int main() {
    std::scanf("%d%d%d", &n, &m, &h);
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < n; ++j)
            std::scanf("%s", mat[i][j]);
    bool ok = true;
    for(int i = 0; i < n; ++i) {
        bool cnt[2] = {};
        for(int j = 0; j < m; ++j)
            if(mat[0][i][j] == '1') pos[0][i].push_back(j);
        for(int j = 0; j < h; ++j)
            if(mat[1][i][j] == '1') pos[1][i].push_back(j);
        if(pos[0][i].empty() != pos[1][i].empty()) { ok = false; break; }
    }
    if(!ok) std::puts("-1");
    else {
        std::vector<Pos> result[2];

        for(int i = 0; i < n; ++i)
            for(int j : pos[0][i])
                for(int k : pos[1][i])
                    result[0].push_back({i, j, k});
        for(int i = 0; i < n; ++i) {
            int a = 0, b = 0;
            int sa = pos[0][i].size(), sb = pos[1][i].size();
            while(sb - b > sa)
                result[1].push_back({i, pos[0][i][a], pos[1][i][b]}), ++b;
            while(sa - a > sb)
                result[1].push_back({i, pos[0][i][a], pos[1][i][b]}), ++a;
            while(a < sa)
                result[1].push_back({i, pos[0][i][a], pos[1][i][b]}), ++a, ++b;
        }

        for(auto&& r : result) {
            std::printf("%d\n", int(r.size()));
            for(auto&& p : r)
                std::printf("%d %d %d\n", p.x, p.y, p.z);
        }
    }
}
