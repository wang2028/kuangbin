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
    Constructing Roads POJ - 2421
    最小生成树（我用了 kruscal，详见README.md）
    读取完各村庄之间的距离后把已有道路的村庄之间距离设为 0 即可
*/

const int maxn = 101;
const int maxm = maxn * maxn;
int n, m;

int w[maxm]; // 每个边的权值
int u[maxm]; // 每个边的起点
int v[maxm]; // 每个边的终点

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
            ans += w[e];
            p[x] = y; // 把根 y 作为根 x 的父结点，即把 x 集合并入 y
        }
    }
    return ans;
}

int main() {
    int cnt = 0;
    int x, y;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            u[cnt] = i;
            v[cnt] = j;
            cin >> w[cnt];
            cnt++;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> x >> y;
        x--;
        y--;
        w[x * n + y] = 0;
    }
    m = cnt;
    cout << kruscal() << endl;
    ;

    return 0;
}
