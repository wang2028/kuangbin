# 最短路

> kuangbin 系列专题 4 最短路，题解见 [Github](https://github.com/Zen-w/kuangbin/tree/master/4.%20%E6%9C%80%E7%9F%AD%E8%B7%AF)，持续更新中

## Dijkstra

> 求可以存在环的最短路（不存在负权边）

详见：[图论 · 最短路 · Dijkstra](https://wangxw.cn/htmls/p-k-d-f.html#H3-3)

<br>

## Bellman_Ford

> 求可以存在负权边的最短路

与迪杰斯特拉不同的是原优先队列换成了普通队列，且不能对每次求得最短的点进行标记为已完成（仅需要对结点标记是否在队列中：inq），因为存在负权时，从起点开始直达的最短的点可能存在间接更短的点，所以不用确定某点是否已经“完成”，只需要持续迭代队列，若存在某点迭代次数 cnt[i] 超过 n 才无解，否则会直至队列为空，求得解。

以下为核心算法，使用时须将其替换入 [Dijkstra 模板](https://wangxw.cn/htmls/p-k-d-f.html#H5-6) （仅替换 dij() 方法）

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

## spfa（优化版）

在 bellman_ford 的基础上，一方面以前向星存边，另一方面采用双端队列进行优化（类似于优先队列，优先弹出距离较短的点以便于之后的更新）

```C++ {.lang-type-C++}
const int maxn = 105, maxm = 105;
// 前向星存边：
struct Edge {
    int to, w; // 边的原始数据
    int next; // 与该边同起点的下一条边
} edge[maxm];
int head[maxn];
int cnt = 0;
void add(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    edge[cnt].w = w;
    head[u] = cnt++;
}

// 双端队列优化版的 spfa：
int n, m;
bool inq[maxn];
int inqCnt[maxn]; // 记录结点入队次数
int d[maxn];
bool spfa(int start) {
    for (int i = 0; i < n; i++) {
        // n个节点
        d[i] = INF;
    }
    memset(inq, 0, sizeof(inq));
    memset(inqCnt, 0, sizeof(inqCnt));
    inqCnt[start] = 1;
    d[start] = 0, inq[start] = true;
    deque<int> q; //双端队列
    q.push_front(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        inq[u] = false;

        //前向星遍历：
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].to;
            if (d[v] > d[u] + edge[i].w) {
                d[v] = d[u] + edge[i].w;
                if (inq[v])
                    continue;
                inq[v] = true;
                if (!q.empty() && d[v] > d[q.front()])
                    q.push_back(v);
                else
                    q.push_front(v);
                if(++inqCnt[v]>n)
                    return false;
            }
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        head[i] = -1;
    }

    // 读边 (u,v) 后记得 u--;v--;
    // 无向图记得添加双向的边

    return 0; 
}
```

<br>

## Floyd

> 求任意两点间最短距离 d[i][j]

详见：[图论 · 最短路 · Floyd](https://wangxw.cn/htmls/p-k-d-f.html#H3-8)