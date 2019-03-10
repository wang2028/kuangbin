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
    Help Jimmy POJ - 1661
    本来是以横、纵坐标为转移条件，但是20000*40000也太大了，
    而且不容易判断某点是否在平台上，所以用 双层 map 来存平台，
    还是很复杂...
    参考了网上解法，以平台和左右端点为转移条件！
    dp[i][dir] 表示第 i 个平台（包括起点）的 dir（左或右）端点到地面的最短时间，
    先将平台按高度排序，之后从最高的平台（其实是起点）开始记忆化搜索即可。
    这样数据量会小很多，也会便于计算。
    （突然看到网上，可以用把平台端点作为结点，用最短路做。。。）
    （我还用间接排序优化了下，但是更耗时了...
    看来间接排序可能对元素超大的数组有用，一般还是别折腾了...所以下文还是正常的排序方法）
*/

const int maxn = 1005, maxm = 20005;
int d[maxn][2];
bool vis[maxn][2];
int n, x, y, maxDrop;

typedef struct {
    int l, r, h;
} Flat;
Flat flat[maxn];

int dp(int t, int dir) {
    // d[t][dir] 在平台 t 的 dir 端到地面最短时间
    if (vis[t][dir])
        return d[t][dir];
    vis[t][dir] = true;
    int i = t + 1;
    if (dir == 0) {
        for (; i <= n; i++) {
            if (flat[i].l <= flat[t].l && flat[i].r >= flat[t].l) {
                if (flat[t].h - flat[i].h <= maxDrop) {
                    d[t][0] = min(dp(i, 0) + flat[t].l - flat[i].l,
                                  dp(i, 1) + flat[i].r - flat[t].l) +
                              flat[t].h - flat[i].h;
                } else {
                    // 平台 t 左端点下方的平台已经会摔死了
                    d[t][0] = INF;
                }
                break;
            }
        }
    } else {
        for (; i <= n; i++) {
            if (flat[i].l <= flat[t].r && flat[i].r >= flat[t].r) {
                if (flat[t].h - flat[i].h <= maxDrop) {
                    d[t][1] = min(dp(i, 0) + flat[t].r - flat[i].l,
                                  dp(i, 1) + flat[i].r - flat[t].r) +
                              flat[t].h - flat[i].h;
                } else {
                    d[t][1] = INF;
                }
                break;
            }
        }
    }

    if (i == n + 1) {
        if (flat[t].h <= maxDrop) {
            d[t][dir] = flat[t].h;
        } else {
            // 会摔死
            d[t][dir] = INF;
        }
    }
    return d[t][dir];
}

bool cmp(Flat a, Flat b) { return a.h > b.h; }

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> x >> y >> maxDrop;
        for (int i = 0; i < n; i++) {
            cin >> flat[i].l >> flat[i].r >> flat[i].h;
        }
        flat[n].l = flat[n].r = x;
        flat[n].h = y;
        memset(vis, 0, sizeof(vis));
        // 将包括起点在内的共 n+1 个平台排序：
        sort(flat, flat + n + 1, cmp);
        cout << dp(0, 0) << endl;
    }

    return 0;
}
