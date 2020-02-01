# 最小生成树

根据 MST 性质，主要有 Prim（见 专题8.生成树 README.md）和 Kruscal 两类算法，在此专题中，个人倾向 Kruscal（Kruscal更适合于稀疏图）。

本质：贪心

## [Kruscal](https://wangxw.cn/htmls/p-k-d-f.html#H3-2)


除 MST 性质外，Kruscal 的实现主要还依靠两思想：
* 并查集：见 专题5.并查集 中 README.md
* 间接排序：即仍将数据存储在固定的数组中，仅将其序号单独存放在另一数组，进行排序，因为所需排序的数据量变小很多，效率实测也会提升（适用于元素结构很大的数组，一般结构体的数组可以不用）

算法：
* 对边权值排序（采用间接排序）
* 每次挑选权值 w 最小的边 e
* 用并查集判断 e 的两端点是否在同一连通分量，若不在，则该边为最终生成树的边，且将该边两端点并入同一连通分量（并查集）
* 时间复杂度：n^2^

```C++ {.lang-type-c++}
// Minimal Spanning Tree - Kruscal
const int maxn = 100, maxm = maxn * maxn; // 最大点、边数
int n = 0, m = 0; // 点数、边数

int w[maxm]; // 每个边的权值
int u[maxm]; // 每个边的起点
int v[maxm]; // 每个边的终点
vector<int> ansEdge; // answer edge

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
    // 使用示例：
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
    }
    cout << kruscal() << endl;
    // 如多组测试数据，需要初始化 p[]：memset(p, 0, sizeof(p));
    return 0;
}
```

<br>

## Prim

见“8. 生成树”部分