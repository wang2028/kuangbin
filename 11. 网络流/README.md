# 网络流

## 最大流

首先基于贪心，寻找所有流量 f(e) < c(e) 容量的边连接而成的由源点 s 至汇点 t 的路径（由 dfs 即可求得）。再在残余网络（f(e) < c(e) || f(e) > 0 的 e 对应的反向边 rev(e) 所组成的图）上找到由 s 至 t 的增广路，即可。可将上述两步合并至一个 dfs() 中。Ford-Fulkerson 算法如下：

```C++ {.lang-type-C++}
struct Edge {
    int to, cap, rev; // 终点，容量，反向边的序号
    int flow; // 流量，值为正数时为正向边，否则为反向边
};
vector<Edge> G[maxm];
bool vis[maxm];
void addEdge(int u, int v, int c) {
    G[u].push_back({v, c, (int)G[v].size(), 0});
    G[v].push_back({u, 0, (int)G[u].size() - 1, 0});
}
int dfs(int u, int v, int flow) {
    if (u == v)
        return flow;
    vis[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        Edge &e = G[u][i];
        if (!vis[e.to] && e.cap > 0) {
            // 此处判断 !vis[e.to]，若 e 的终点之前访问过就不再访问，
            // 但不会造成漏遍历的情况，因为总控函数 maxFlow 会一直遍历，
            // 直到无路可走
            int f = dfs(e.to, v, min(flow, e.cap));
            if (f > 0) {
                e.cap -= f;
                e.flow += f;
                G[e.to][e.rev].cap += f;
                G[e.to][e.rev].flow -= f;
                return f; // 只找一条 s->t 而不是搜索全部
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
        } else {
            flow += f;
        }
    }
}
```

### Dinic

// https://www.cnblogs.com/SYCstudio/p/7260613.html

与上文算法改进之处在于增加（对可到达点的）“分层”（bfs 实现），“层次”即与源点 s 的最短距离，通过分层，每次 dfs 只能从第 i 层增广到第 i+1 层，而不能在同层或其他情况下增广，限制了了每次分层后 dfs 的次数。当“路都满了”时，也就是无法继续增广时，分层也就无法到达汇点 t，结束。

```C++ {.lang-type-C++}
struct Edge {
    int to, cap, rev; // 终点，容量，反向边的序号
};
vector<Edge> G[maxn]; // 存图
int level[maxn];      // 每个点的层次
int iter[maxn];       // 对点 i 遍历到的当前弧

void addEdge(int u, int v, int c) {
    G[u].push_back({v, c, G[v].size()});
    G[v].push_back({u, 0, G[u].size() - 1});
}

void bfs(int s) {
    // 计算层次
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < G[v].size(); i++) {
            Edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int u, int v, int flow) {
    // 寻找增广路
    if (u == v)
        return flow;
    for (int &i = iter[u]; i < G[u].size(); i++) {
        Edge &e = G[u][i];
        if (e.cap > 0 && level[u] < level[e.to]) {
            int d = dfs(e.to, v, min(flow, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0; // 没找到
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s); // 先确定层次
        if (level[t] < 0) {
            // 分层已经无法到达 t，说明已经无法增广（路都满了，也就是 s-t 割为 0 了）
            return flow;
        }
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
}
```

## 最小割

最小割 = 最大流

## 最小费用最大流

