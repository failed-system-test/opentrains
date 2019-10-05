#include <bits/stdc++.h>

const int MAXN = 20000;

int POW3[9];

char buffer[100];
void read() { std::fgets(buffer, sizeof(buffer), stdin); }
void write(int id) {
    std::printf("%d %d\n", id % 3 + 1, id / 3 + 1);
    std::fflush(stdout);
}

int getID(int x, int y) { return (y - 1) * 3 + (x - 1); }

int me;

int arr[9];
int value;

int dp[MAXN], next[MAXN];
bool visited[MAXN];

int check() {
    static const int id[8][3] = {
        {getID(1, 1), getID(2, 1), getID(3, 1)},
        {getID(1, 2), getID(2, 2), getID(3, 2)},
        {getID(1, 3), getID(2, 3), getID(3, 3)},
        {getID(1, 1), getID(1, 2), getID(1, 3)},
        {getID(2, 1), getID(2, 2), getID(2, 3)},
        {getID(3, 1), getID(3, 2), getID(3, 3)},
        {getID(1, 1), getID(2, 2), getID(3, 3)},
        {getID(1, 3), getID(2, 2), getID(3, 1)},
    };
    for (int i = 0; i < 8; ++i) {
        if (arr[id[i][0]] && arr[id[i][0]] == arr[id[i][1]] &&
            arr[id[i][0]] == arr[id[i][2]])
            return arr[id[i][0]];
    }
    return 0;
}

void dfs(int cur = 1, int v = 0, int depth = 0) {
    if (visited[v]) return;
    visited[v] = true;
    if (int c = check()) {
        dp[v] = c;
        next[v] = -1;
        return;
    }
    if (depth == 9) {
        dp[v] = 0;
        next[v] = -1;
        return;
    }
    std::vector<int> vec[3];
    for (int i = 0; i < 9; ++i) {
        if (arr[i]) continue;
        arr[i] = cur;
        int nv = v + POW3[i] * cur;
        dfs(3 - cur, nv, depth + 1);
        arr[i] = 0;
        vec[dp[nv]].push_back(i);
    }
    if (!vec[cur].empty())
        dp[v] = cur, next[v] = vec[cur][0];
    else if (!vec[0].empty())
        dp[v] = 0, next[v] = vec[0][0];
    else
        dp[v] = 3 - cur, next[v] = vec[3 - cur][0];
}

int main() {
    POW3[0] = 1;
    for (int i = 1; i < 9; ++i) POW3[i] = POW3[i - 1] * 3;

    read();
    me = (buffer[0] == 'O') + 1;

    dfs();

    int cur = 1;
    int cnt = 0;
    while (cnt < 9 && next[value] >= 0) {
        int id;
        if (cur == me) {
            id = next[value];
            write(id);

        } else {
            read();
            int x, y;
            if (std::sscanf(buffer, "%d%d", &x, &y) != 2) break;
            id = getID(x, y);
        }
        arr[id] = cur;
        value += cur * POW3[id];
        cur = 3 - cur;
        ++cnt;
    }
}
