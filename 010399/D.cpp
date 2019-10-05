#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 36;

i64 POW3[MAXN + 1];

struct Pos {
    int layer;
    i64 offset;

    Pos() : layer(0), offset(0) {}
    Pos(int layer_, i64 offset_) : layer(layer_), offset(offset_) {}

    Pos step(char op) const {
        switch (op) {
            case 's':
                return Pos(layer, (offset + 1) % POW3[layer]);
            case 'a':
                return Pos(layer, (offset + POW3[layer] - 1) % POW3[layer]);
            case 'c':
                return Pos(layer + 1, offset * 3);
            case 'g':
                assert(layer > 0);
                assert(offset % 3 == 0);
                return Pos(layer - 1, offset / 3);
            default:
                assert(false);
                return Pos();
        }
    }
};

Pos read() {
    char buffer[100];
    std::scanf("%s", buffer);
    int len = std::strlen(buffer);
    Pos p;
    for (int i = 0; i < len; ++i) p = p.step(buffer[i]);
    return p;
}

std::string rev(const std::string& str) {
    std::string result;
    result.reserve(str.length());
    for (int i = int(str.length()) - 1; i >= 0; --i) {
        switch (str[i]) {
            case 's':
                result.push_back('a');
                break;
            case 'a':
                result.push_back('s');
                break;
            case 'c':
                result.push_back('g');
                break;
            case 'g':
                result.push_back('c');
                break;
            default:
                assert(false);
                return "";
        }
    }
    return result;
}

void bfs(const Pos& p,
         std::unordered_map<int, std::unordered_map<i64, std::string> >& mp) {
    mp.clear();
    mp[p.layer][p.offset] = "";
    std::queue<Pos> q;
    q.push(p);
    do {
        Pos u = q.front();
        q.pop();
        if (u.layer == 0) continue;
        std::string s0 = mp[u.layer][u.offset];
        if (u.offset % 3) {
            int d1 = u.offset % 3, d2 = 3 - d1;
            Pos v1(u.layer - 1, u.offset / 3);
            if (!mp[v1.layer].count(v1.offset) ||
                s0.length() + d1 + 1 < mp[v1.layer][v1.offset].length()) {
                mp[v1.layer][v1.offset] = s0 + std::string(d1, 'a') + 'g';
                q.push(v1);
            }
            Pos v2(u.layer - 1, (u.offset / 3 + 1) % POW3[u.layer - 1]);
            if (!mp[v2.layer].count(v2.offset) ||
                s0.length() + d2 + 1 < mp[v2.layer][v2.offset].length()) {
                mp[v2.layer][v2.offset] = s0 + std::string(d2, 's') + 'g';
                q.push(v2);
            }

        } else {
            Pos v(u.layer - 1, u.offset / 3);
            if (!mp[v.layer].count(v.offset) ||
                s0.length() + 1 < mp[v.layer][v.offset].length()) {
                mp[v.layer][v.offset] = s0 + 'g';
                q.push(v);
            }
        }

    } while (!q.empty());
}

int main() {
    POW3[0] = 1;
    for (int i = 1; i <= MAXN; ++i) POW3[i] = POW3[i - 1] * 3;

    Pos s = read();
    Pos t = read();

    std::unordered_map<int, std::unordered_map<i64, std::string> > mp[2];
    bfs(s, mp[0]);
    bfs(t, mp[1]);

    for (Pos ss = s.step('c'); ss.layer <= std::max(s.layer, t.layer);
         ss = ss.step('c'))
        mp[0][ss.layer][ss.offset] = std::string(ss.layer - s.layer, 'c');
    for (Pos tt = t.step('c'); tt.layer <= std::max(s.layer, t.layer);
         tt = tt.step('c'))
        mp[1][tt.layer][tt.offset] = std::string(tt.layer - t.layer, 'c');

    std::string result;
    bool ok = false;
    for (int i = 0; i <= std::max(s.layer, t.layer); ++i) {
        for (auto&& a : mp[0][i]) {
            for (auto&& b : mp[1][i]) {
                i64 d1 = (b.first - a.first + POW3[i]) % POW3[i],
                    d2 = (POW3[i] - d1) % POW3[i];
                if (d1 <= d2) {
                    if (!ok || a.second.length() + b.second.length() + d1 <
                                   result.length())
                        result =
                            a.second + std::string(d1, 's') + rev(b.second),
                        ok = true;

                } else {
                    if (!ok || a.second.length() + b.second.length() + d2 <
                                   result.length())
                        result =
                            a.second + std::string(d2, 'a') + rev(b.second),
                        ok = true;
                }
            }
        }
    }

    std::puts(result.c_str());
}
