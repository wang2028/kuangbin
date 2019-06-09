# 生成树

相比最小生成树，该专题对生成树进行扩展，首先给出最小生成树的 Prim 模板：

## Prim

> 在求解最小生成树中，Prim 更适合于稠密图

```C++ {.lang-type-c++}
const int INF = 0x3f3f3f;
const int maxn = 105;
int n; // 点数
bool vis[maxn];
int cost[maxn][maxn]; // 路径权值（花费）矩阵
int lowcost[maxn];    // prim 的辅助矩阵
int prim() {
    // 暂以点 0 为起点
    int ans = 0;
    memset(vis, 0, sizeof(vis));
    vis[0] = true;
    for (int i = 1; i < n; i++)
        lowcost[i] = cost[0][i];
    for (int i = 1; i < n; i++) {
        // 循环 n-1 次
        // 首先找出当前最短路径，及其端点：
        int mincost = INF;
        int p = -1;
        for (int j = 1; j < n; j++) {
            if (lowcost[j] < mincost && !vis[j]) {
                mincost = lowcost[j];
                p = j;
            }
        }
        if (mincost == INF)
            return -1; // 原图不连通
        ans += mincost;
        vis[p] = true;
        // 更新 lowcost：
        for (int j = 1; j < n; j++) {
            if (cost[p][j] < lowcost[j] && !vis[j]) {
                lowcost[j] = cost[p][j];
            }
        }
    }
    return ans;
}
```

## 次小生成树

基于 Prim 算法求出最小生成树 T 后，将不在 T 上的一条边 E 加入 T，此时必会形成环，用 E 替换掉环上除 E 外的（最大权值的）边 E'，即获得次小生成树。

其中求 E' 的方法为在 Prim 的过程中，记录点 i 到 j 路径上权值最大的边（算法中这个地方有点DP的意思）。

```C++ {.lang-type-C++}
const int INF = 0x3f3f3f;
const int maxn = 105;
int n;
bool vis[maxn];
int cost[maxn][maxn]; // 路径权值（花费）矩阵
int lowcost[maxn];    // prim 的辅助矩阵
int fa[maxn]; // 记录点 i 在最小生成树中的父结点（以 0 为根结点时）
int Max[maxn][maxn]; // 记录最小生成树中点 i 到 j 的路径上权值最大的边
int used[maxn][maxn]; // 记录边 (i,j) 是否在最小生成树中
int prim() {
    // 暂以点 0 为起点
    int ans = 0;
    // 注意以下需要初始化：
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
        int mincost = INF;
        int p = -1;
        for (int j = 1; j < n; j++) {
            if (lowcost[j] < mincost && !vis[j]) {
                mincost = lowcost[j];
                p = j;
            }
        }
        if (mincost == INF)
            return -1; // 原图不连通
        ans += mincost;
        vis[p] = true;
        used[p][fa[p]] = used[fa[p]][p] = true; // 计入最小生成树的边中
        for (int j = 0; j < n; j++) {
            // 更新 Max：
            if(vis[j] && j!=p){
                Max[p][j] = Max[j][p] = max(Max[j][fa[p]], lowcost[p]);
                // 此处 lowcost[p]==mincost 吧？
            }
            // 更新 lowcost：
            if (cost[p][j] < lowcost[j] && !vis[j]) {
                lowcost[j] = cost[p][j];
            }
        }
    }
    return ans;
}
// 之后再遍历 used[i][j] 中值为 false 的边，用其值替换 Max[i][j] 即可。
```

## 最小树形图

即有向图的最小生成树。