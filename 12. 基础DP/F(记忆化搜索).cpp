#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

/*
    因为除了 d[0] 外 d[i] 均初始化为 INF，
    所以最终求出的 d[full-empty] 小于 INF 时一定是从 0 开始的，
    保证了“恰好装满”的要求。
*/

const int maxn = 505, maxm = 10005;
int d[maxm];
bool vis[maxm], suc;
int n, all;

struct Coin {
    int val, wei;
} coin[maxn];

int minVal(int t) {
    if (vis[t]) {
        return d[t];
    }
    vis[t] = true;
    d[t] = INF;
    for (int i = 0; i < n; i++) {
        if (t >= coin[i].wei) {
            d[t] = min(d[t], minVal(t - coin[i].wei) + coin[i].val);
        }
    }
    return d[t];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int emp, full;
        cin >> emp >> full;
        all = full - emp;
        int val, wei;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> coin[i].val >> coin[i].wei;
        }
        memset(vis, 0, sizeof(vis));
        memset(d, 0, sizeof(d));
        vis[0] = true;
        int ans = minVal(all);
        if (ans>=INF) {
            cout << "This is impossible." << endl;
        } else {
            cout << "The minimum amount of money in the piggy-bank is " << ans
                 << "." << endl;
        }
    }

    return 0;
}