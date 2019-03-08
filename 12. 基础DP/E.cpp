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
    Super Jumping! Jumping! Jumping! HDU - 1087
    动态规划，设 d[i] 为从第 i 个数开始的和值最大的递增序列，
    每次遍历 i 之后的所有数 j，若 j 大于 i，则取 d[i] 与 d[j]+i 的较大值，
    采用记忆化搜索
*/

const int maxn = 1005, maxm = 10005;
bool vis[maxn];
int d[maxn];
int origin[maxn];
int n;

int maxSum(int t) {
    if (vis[t]) {
        return d[t];
    }
    vis[t] = true;
    d[t] = origin[t];
    for (int i = t + 1; i < n; i++) {
        if (origin[i] > origin[t]) {
            d[t] = max(d[t], maxSum(i) + origin[t]);
        }
    }
    return d[t];
}

int main() {
    while (cin >> n && n) {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; i++) {
            cin >> origin[i];
        }

        // d[i]: 从 i 开始的最大递增序列和
        int ans = -1;
        for (int i = 0; i < n; i++) {
            ans = max(ans, maxSum(i));
        }
        cout << ans << endl;
    }

    return 0;
}
