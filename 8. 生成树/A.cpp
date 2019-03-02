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
#define ll long long

/*
    A - The Unique MST POJ - 1679
    有点暴力...直接 kruscal，求出最小生成树的边以及最小 cost，
    然后依次删去一条最小生成树中的边（设为 INF 即可）后 kruscal，
    判断此时是否与最小 cost 相同。
    注意在删去某边前将上一次删去的边再次添加上（置为原值）
*/

const int maxn = 102, maxm = maxn * maxn / 2; // 最大点、边数
int n = 0, m = 0;                             // 点数、边数

int w[maxm]; // 每个边的权值
int u[maxm]; // 每个边的起点
int v[maxm]; // 每个边的终点
vector<int> ansEdge;

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

int kruscal() {
    // 返回最小生成树的权值
    // 最小生成树的边存在 ansEdge 中

    for (int i = 0; i < n; i++) {
        p[i] = i; // 初始化并查集，p[i] == i 时它自己就是根
    }
    for (int i = 0; i < m; i++) {
        r[i] = i; // 初始化边序号
    }

    int ans = 0; // 最终权值和
    int e, x, y;
    sort(r, r + m, cmp);
    for (int i = 0; i < m; i++) {
        e = r[i];
        x = findRoot(u[e]);
        y = findRoot(v[e]);
        if (x != y) {
            ansEdge.push_back(e); // 纳入最小生成树的边
            ans += w[e];
            p[x] = y; // 把根 y 作为根 x 的父结点，即把 x 集合并入 y
        }
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            cin >> u[i] >> v[i] >> w[i];
        }
        int curMin = kruscal();
        int origin;
        int i = 0;
        for (; i < n - 1; i++) {
            if (i > 0) {
                w[ansEdge[i - 1]] = origin;
            }
            origin = w[ansEdge[i]];
            w[ansEdge[i]] = INF;
            // 再次 kruscal 时记得初始化 p[]：
            memset(p, 0, sizeof(p));
            if (kruscal() == curMin) {
                cout << "Not Unique!" << endl;
                break;
            }
        }
        if (i == n - 1) {
            cout << curMin << endl;
        }

        // 再次 kruscal 时记得初始化 p[]：
        memset(p, 0, sizeof(p));
        ansEdge.clear();
    }

    return 0;
}
