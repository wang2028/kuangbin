#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
#define INF 0x3f3f3f3f

/*
    QS Network ZOJ - 1586 最小生成树
    直接使用 Kruscal 模板，将边权重加上两端点的“适配器”价格即可
*/

const int maxm = 1005;            // 最大点数
const int maxn = maxm * maxm / 2; // 最大边数取最大点数的平方除以2
int adapterPrice[maxm];
int n, m;

int w[maxn]; // 每个边的权值
int u[maxn]; // 每个边的起点
int v[maxn]; // 每个边的终点
int r[maxn]; // 用来对“边”间接排序的数组
int p[maxm]; // i 的父结点（基于并查集，用来查找其根结点）

static bool cmp(const int i, const int j) {
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
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        m = n * n;
        memset(w, 0, sizeof(w));
        memset(u, 0, sizeof(u));
        memset(v, 0, sizeof(v));
        memset(adapterPrice, 0, sizeof(adapterPrice));
        for (int i = 0; i < n; i++) {
            cin >> adapterPrice[i];
        }
        int cnt = 0, price;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> price;
                if (i == j || i < j) {
                    // 只读下三角
                    continue;
                }
                w[cnt] = price + adapterPrice[i] + adapterPrice[j];
                u[cnt] = i;
                v[cnt] = j;
                cnt++;
            }
        }
        cout << kruscal() << endl;
    }

    return 0;
}
