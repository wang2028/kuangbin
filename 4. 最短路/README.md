# 最短路

## Dijkstra

> 求可以存在环的最短路（不存在负权边）

详见：[图论 · 最短路 · Dijkstra](https://wangxw.cn/htmls/p-k-d-f.html#H3-3)

<br>

## Bellman_Ford

> 求可以存在负权边的最短路

与迪杰斯特拉不同的是原优先队列换成了普通队列，且不能对每次求得最短的点进行标记，因为存在负权时，从起点开始直达的最短的点可能存在间接更短的点，所以不用确定某点是否已经“完成”，只需要持续迭代队列，若存在某点迭代次数超过 n 才无解，否则会直至队列为空，求得解。

以下为核心算法，使用时须将其替换入 [Dijkstra 模板](https://wangxw.cn/htmls/p-k-d-f.html#H5-6) （替换 dij() 方法）

```c++ {.lang-type-c++}
int fa[n];
bool bellman_ford(int s){
    // 带负权的求最短路
    // s 为起点，存储图的结构同 Dijkstra
    // 复杂度 nm

    queue<int> Q;
    int cnt[n]; // 记录某点迭代次数，当超过 n-1 次时，说明出现环
    bool inq[n]; // 该节点是否在队中
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0;i<n;i++){
        d[i] = INF;
    }
    d[s] = 0;
    inq[s] = true;
    Q.push(s);

    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        inq[u] = false;
        for(int i = 0;i<G[u].size();i++){
            Edge& e = edges[G[u][i]];
            if(d[u]<INF && d[e.to]>d[u]+e.w){
                d[e.to] = d[u] + e.w;
                fa[e.to] = G[u][i];
                if(!inq[e.to]) {
                    Q.push(e.to);
                    inq[e.to] = true;
                    cnt[e.to]++;
                    if(cnt[e.to]>n){
                        return false;
                        // 无解
                    }
                }
            }
        }
    }
    return true;
}
```

<br>

## Floyd

> 求任意两点间最短距离 d[i][j]

详见：[图论 · 最短路 · Floyd](https://wangxw.cn/htmls/p-k-d-f.html#H3-8)