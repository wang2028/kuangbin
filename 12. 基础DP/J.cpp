#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    FatMouse's Speed HDU - 1160
    刚开始还以为直接是一个递增（递减）子序列，后来发现可以先排序，再求...
*/

const int maxn = 1003;
int n = 0;
bool vis[maxn];
int d[maxn], nxt[maxn];

struct mouse {
    int w, v;
    int ind;
} mice[maxn];

int dp(int t) {
    if (vis[t])
        return d[t];
    vis[t] = true;
    for (int i = t + 1; i < n; ++i) {
        if (mice[i].w > mice[t].w && mice[i].v < mice[t].v) {
            int m = dp(i);
            if (m + 1 > d[t]) {
                d[t] = m + 1;
                nxt[t] = i;
            }
        }
    }
    return d[t];
}

bool cmp(struct mouse m1, struct mouse m2) { return m1.w < m2.w; }

int main() {
    int wei, vel;
    while (cin >> mice[n].w >> mice[n].v) {
        mice[n].ind = n;
        n++;
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        d[i] = 1;
    }
    sort(mice, mice + n, cmp);

    int maxStart, maxSum = 0;
    for (int i = 0; i < n; i++) {
        if (dp(i) > maxSum) {
            maxSum = d[i];
            maxStart = i;
        }
    }
    cout << maxSum << endl;
    for (int i = 0; i < maxSum; i++) {
        cout << mice[maxStart].ind + 1 << endl;
        maxStart = nxt[maxStart];
    }

    return 0;
}
