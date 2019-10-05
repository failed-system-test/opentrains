#include <bits/stdc++.h>

const double PI = 4 * std::atan(1.0);
const int MAXN = 2000;

struct Point {
    double x, y;
    Point() : x(), y() {}
    Point(double x_, double y_) : x(x_), y(y_) {}

    friend Point operator+(const Point& a, const Point& b) {
        return Point(a.x + b.x, a.y + b.y);
    }

    static Point rot(double x) { return Point(std::cos(x), std::sin(x)); }
};

int n;

std::vector<int> edges[MAXN];
std::vector<int> childs[MAXN];
bool visited[MAXN];
int cnt[MAXN];
Point result[MAXN];

void dfs1(int u) {
    visited[u] = true;
    cnt[u] = 1;
    childs[u].clear();
    for (int v : edges[u]) {
        if (visited[v]) continue;
        dfs1(v);
        cnt[u] += cnt[v];
        childs[u].push_back(v);
    }
}

void dfs2(int u, const Point& p, double l, double r) {
    result[u] = p;
    if (childs[u].empty()) return;
    std::vector<double> a(childs[u].size() + 1);
    int c = 0;
    a[0] = l;
    double d = (r - l) / (cnt[u] - 1);
    for (int i = 0; i < int(childs[u].size()) - 1; ++i)
        c += cnt[childs[u][i]], a[i + 1] = l + c * d;
    a[childs[u].size()] = r;
    for (int i = 0; i < int(childs[u].size()); ++i) {
        int v = childs[u][i];
        dfs2(v, p + Point::rot(0.5 * (a[i] + a[i + 1])), a[i], a[i + 1]);
    }
}

int main() {
    std::scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        --u, --v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    dfs1(0);
    dfs2(0, Point(0, 0), 0, 2 * PI);

    for (int i = 0; i < n; ++i)
        std::printf("%.10f %.10f\n", result[i].x, result[i].y);
}
