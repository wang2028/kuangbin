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


// TODO 未过？？？  I - 最少拦截系统 HDU - 1257


const int maxn = 200003, maxm = 100005;

int n;
bool vis[maxn];
int d[maxn], nxt[maxn];
int hei[maxn]; // 原始读入数据
int maxDes(int t) {
    // 从 t 开始的最长递减子序列长度
    if (vis[t]) {
        return d[t];
    }
    vis[t] = true;
    for (int i = t + 1; i < n; i++) {
        if (hei[i] < hei[t]) {
            int m = maxDes(i);
            if (m + 1 > d[t]) {
                d[t] = m + 1;
                nxt[t] = i;
            }
        }
    }
    return d[t]; // 一定要记得返回啊！！！
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> hei[i];
        }
        int ans = 0;
        while (n > 0) {
            ans++;
            memset(vis, 0, sizeof(vis));
            memset(nxt, 0, sizeof(nxt));
            for (int i = 0; i < n; i++) {
                d[i] = 1;
            }
            maxDes(0);
            int maxLen = 0, maxStart;
            for (int i = 0; i < n; i++) {
                if (maxLen < d[i]) {
                    maxLen = d[i];
                    maxStart = i;
                }
            }
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (i != maxStart) {
                    hei[cnt++] = hei[i];
                } else {
                    maxStart = nxt[maxStart];
                }
            }
            n = cnt;
        }
        cout << ans << endl;
    }

    return 0;
}
