# 网络流

## 最大流

首先基于贪心，寻找所有流量 f(e) < c(e) 容量的边连接而成的由源点 s 至汇点 t 的路径（由 dfs 即可求得）。再在残余网络（f(e) < c(e) || f(e) > 0 的 e 对应的反向边 rev(e) 所组成的图）上找到由 s 至 t 的增广路，即可。可将上述两步合并至一个 dfs() 中。Ford-Fulkerson 算法如下：

```C++ {.lang-type-C++}

typedef struct edge {
    int to, cap, rev; // 终点，容量，反向边的序号
    struct edge(int t, c, r) : to(t), cap(c), rev(r) {}
} Edge;

vector<int> G[maxn];
bool vis[maxn];

void addEdge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, G[v].size()));
    G[v].push_back(Edge(u, 0, G[u].size() - 1));
}

int dfs(int u, int v, int flow) {
    if (u == v)
        return;
    vis[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        Edge &e = G[u][i];
        if (!vis[e.to] && e.cap > 0) {
            // 此处判断 !vis[e.to]，若 e 的终点之前访问过便不访问，
            // 但不会造成漏遍历的情况，因为总控函数 maxFlow 会一直遍历，
            // 直到无路可走
            int f = dfs(e.to, v, min(flow, e.cap));
            if (f > 0) {
                e.cap -= f;
                G[e.to][e.rev].cap += f;
                return d; // 只找一条 s->t 而不是搜索全部
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (true) {
        memset(vis, 0, sizeof(vis));
        int f = dfs(s, t, INF);
        if (f == 0) {
            return flow;
        } 
        else {
            flow += f;
        }
    }
}
```