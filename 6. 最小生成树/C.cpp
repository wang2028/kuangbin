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
    Building a Space Station POJ - 2031
    最小生成树（我用了 kruscal，详见README.md）
    预处理一下即可
*/

const int maxn = 101;
const int maxm = maxn * maxn;
int n, m;

double w[maxm]; // 每个边的权值
int u[maxm];    // 每个边的起点
int v[maxm];    // 每个边的终点

int r[maxm]; // 用来对“边”间接排序的数组
int p[maxn]; // i 的父结点（基于并查集，用来查找其根结点）

bool cmp(const int i, const int j) {
    // 间接查找中的比较函数
    // 排的是 i,j 的序，但依据是 w[i],w[j]
    return w[i] < w[j];
}

int findRoot(int i) {
    // 并查集中查找点 i 的根
    if (p[i] == i)
        return i;
    else
        return p[i] = findRoot(p[i]);
    // 顺便直接将 i 的父结点更新为集合的根，以提高之后的找根效率
}

double kruscal() {
    // 返回最小生成树的权值
    // 最小生成树的边存在 ansEdge 中

    for (int i = 0; i < n; i++) {
        p[i] = i; // 初始化并查集，p[i] == i 时它自己就是根
    }
    for (int i = 0; i < m; i++) {
        r[i] = i; // 初始化边序号
    }

    double ans = 0; // 最终权值和
    int e, x, y;
    sort(r, r + m, cmp);
    for (int i = 0; i < m; i++) {
        e = r[i];
        x = findRoot(u[e]);
        y = findRoot(v[e]);
        if (x != y) {
            ans += w[e];
            p[x] = y; // 把根 y 作为根 x 的父结点，即把 x 集合并入 y
        }
    }
    return ans;
}

typedef struct {
    double x, y, z, r;
} Node;

int main() {
    int cnt;
    double x, y, z, radius;
    while (cin >> n && n) {
        Node nodes[maxn];
        cnt = 0;
        for (int i = 0; i < n; i++) {
            cin >> nodes[i].x >> nodes[i].y >> nodes[i].z >> nodes[i].r;
        }
        double dis2, radiusSum; // 球心距离的平方
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }

                u[cnt] = i;
                v[cnt] = j;
                dis2 = pow(nodes[i].x - nodes[j].x, 2) +
                       pow(nodes[i].y - nodes[j].y, 2) +
                       pow(nodes[i].z - nodes[j].z, 2);
                radiusSum = nodes[i].r + nodes[j].r;
                if (dis2 <= radiusSum * radiusSum) {
                    w[cnt] = 0;
                } else {
                    w[cnt] = sqrt(dis2) - radiusSum;
                }
                cnt++;
            }
        }
        m = cnt;
        printf("%.3f\n", kruscal());
    }

    return 0;
}
