#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;

/*
    Fire Net HDU - 1045
    直接暴力也能过
*/

const int maxn = 4;
int n;
int city[maxn][maxn];

bool can(int x, int y) {
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (i == x && !ok) {
            break;
        }
        if (city[i][y] == 2) {
            ok = false;
        } else if (city[i][y] == 1) {
            ok = true;
        }
    }
    if (!ok)
        return false;
    ok = true;
    for (int i = 0; i < n; i++) {
        if (i == y && !ok) {
            break;
        }
        if (city[x][i] == 2) {
            ok = false;
        } else if (city[x][i] == 1) {
            ok = true;
        }
    }
    return ok;
}

int cur, maxHouse;
void dfs(int t) {
    if (t >= n * n) {
        maxHouse = max(maxHouse, cur);
        return;
    }
    int x = t / n, y = t % n;

    dfs(t + 1);
    if (city[x][y] == 1) {
        return;
    }
    if (can(x, y)) {
        cur++;
        city[x][y] = 2;
        dfs(t + 1);
        city[x][y] = 0;
        cur--;
    }
}

int main() {
    while (cin >> n && n) {
        memset(city, -1, sizeof(city));
        char c;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> c;
                if (c == '.')
                    city[i][j] = 0;
                else if (c == 'X')
                    city[i][j] = 1;
                else
                    city[i][j] = 2;
            }
        }
        cur = 0;
        maxHouse = -1;
        dfs(0);
        cout << maxHouse << endl;
    }

    return 0;
}