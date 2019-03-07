#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    B - Qin Shi Huang's National Road System HDU - 4081
    Prim 求最小生成树 T 后，遍历每条边 E，
    若 E 在 T 中，直接求比例 A/B，否则将 E 加入 T，并替换出现的环中最大权值的边，
    即得次小生成树，求 A/B。（求法详见 README.md）
    注意：Prim 需要初始化（重置）一些数组及变量，否则多组测试数据时会产生影响。
*/

const int maxn = 1005;
int n;
bool vis[maxn];
double cost[maxn][maxn]; // 路径权值（花费）矩阵
double lowcost[maxn];    // prim 的辅助矩阵
int fa[maxn]; // 记录点 i 在最小生成树中的父结点（以 0 为根结点时）
double Max[maxn][maxn]; // 记录最小生成树中点 i 到 j 的路径上权值最大的边
int used[maxn][maxn]; // 记录边 (i,j) 是否咋最小生成树中
double prim() {
    // 暂以点 0 为起点
    double ans = 0;
    memset(vis, 0, sizeof(vis));
    memset(Max, 0, sizeof(Max));
    memset(used, 0, sizeof(used));
    vis[0] = true;
    fa[0] = -1;
    lowcost[0] = 0;
    for (int i = 1; i < n; i++) {
        lowcost[i] = cost[0][i];
        fa[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        // 循环 n-1 次
        // 首先找出当前最短路径，及其端点：
        double mincost = INF;
        int p = -1;
        for (int j = 1; j < n; j++) {
            if (lowcost[j] < mincost && !vis[j]) {
                mincost = lowcost[j];
                p = j;
            }
        }
        ans += mincost;
        vis[p] = true;
        used[p][fa[p]] = used[fa[p]][p] = true; // 计入最小生成树的边中
        for (int j = 0; j < n; j++) {
            // 更新 Max：
            if (vis[j] && j != p) {
                Max[p][j] = Max[j][p] = max(Max[j][fa[p]], lowcost[p]);
                // 此处 lowcost[p]==mincost 吧？
            }
            // 更新 lowcost：
            if (cost[p][j] < lowcost[j] && !vis[j]) {
                lowcost[j] = cost[p][j];
                fa[j] = p;
            }
        }
    }
    return ans;
}
// 之后再遍历 used[i][j] 中值为 false 的边，用其值替换 Max[i][j] 即可。
typedef struct {
    int x, y;
    int people;
} City;

int main() {
    int T;
    cin >> T;
    City cities[maxn];
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> cities[i].x >> cities[i].y >> cities[i].people;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    cost[i][j] = sqrt(pow(cities[i].x - cities[j].x, 2) +
                                      pow(cities[i].y - cities[j].y, 2));
                }
            }
        }
        double ans = prim();
        double r = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if (used[i][j]) {
                        r = max(r, (cities[i].people + cities[j].people) /
                                       (ans - cost[i][j]));
                    } else {
                        r = max(r, (cities[i].people + cities[j].people) /
                                       (ans - Max[i][j]));
                    }
                }
            }
        }
        printf("%.2f\n", r);
    }

    return 0;
}
