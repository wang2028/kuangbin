# 最短路

> kuangbin 系列专题 4 最短路，题解见 [Github](https://github.com/Zen-w/kuangbin/tree/master/4.%20%E6%9C%80%E7%9F%AD%E8%B7%AF)，持续更新中

注意：
* 双向边开数组要注意题目给的范围再 __乘以 2__

## [Dijkstra](https://wangxw.cn/htmls/p-k-d-f.html#H3-3)

> 单源最短路径，即从固定一点出发到其他各点的最短路径，求可以存在环的最短路（不存在负权边）

1. 从起点开始，找到当前与起点距离 dis[u] 最短的点 u（第一次找到的便是起点本身），并标记 u 为“已完成的点”；
2. 从 u 出发，对以 u 为起点的每条边的终点 v 进行“松弛操作”，即：当 dis[u]+weight[u][v] < dis[v] 时，更新 dis[v]；
3. 返回步骤 1，在所有“未完成的点”中继续寻找 dis[u] 最短的点 u

```C++ {.lang-type-c++}
// 为与之后网络流风格一致，定义边：
struct Edge {
    int from, to, w; // 紫书这里用了 dist 表示 w
    Edge(int u, int v, int w) :from(u), to(v), w(w) {}
};

struct Dij {
    int n, m; // 点数，边数
    vector<Edge> edges;
    vector<int> G[maxn]; // 以 G 存点，以 vector 存该点的边，以便 Dij 中的遍历更新
    bool done[maxn]; // 是否已找到最短路
    int d[maxn]; // s（起点）到各点距离
    int p[maxn]; // 最短路中结点 j 的以其为终点的弧编号

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            G[i].clear();
        }
        edges.clear();
    }

    void addEdge(int from, int to, int w) {
        edges.push_back(Edge(from, to, w));
        m = edges.size();
        G[from].push_back(m - 1);
    }

    struct HeapNode {
        int d, u; // 距离，终点（我觉得紫书这里应该用 v，与前面保持一致）
        bool operator < (const HeapNode &rhs) const {
            return d > rhs.d; // 距离越远优先级越低（越晚弹出）
        }
    };

    void dij(int s) {
        // 以 s 为起点

        // typedef pair<int, int> pii // 定义二元组 (d[i],i) 来每次选 d 最小的边和终点
        // priority_queue<pii, vector<pii>, greater<pii> >q
        // 但不太直观，所以之后还是用结构体 HeapNode

        priority_queue<HeapNode> Q;
        memset(done, 0, sizeof(bool)*n);
        for (int i = 0; i < n; i++) {
            d[i] = INF;
        }
        d[s] = 0;
        Q.push(HeapNode{ 0, s }); // 这个定义涨姿势
        while (!Q.empty()) {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (done[u]) continue;
            done[u] = true;
            for (int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if (e.w + d[u] < d[e.to]) {
                    d[e.to] = e.w + d[u];
                    p[e.to] = G[u][i];
                    Q.push(HeapNode{ d[e.to], e.to });
                    // 第一次遍历因为初始化为 INF，所以所有点都会入队
                }
            }
        }
    }
};

int main() {
    // 测试：

    // 只需要录入边数和边的 u v w：
    Dij dij;
    int n, u, v, w;
    cin >> n;
    dij.init(n);
    for (int i = 0; i < dij.n; i++) {
        cin >> u >> v >> w;
        dij.addEdge(u, v, w);
        dij.addEdge(v, u, w); // 无向图每条边都是双向通行的
    }
    dij.dij(0);
    for (int i = 0; i < dij.n; i++) {
        cout << dij.d[i] << ends;
    }
    cout << endl;

    return 0;
}
```

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
void addEdge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    edge[cnt].w = w;
    head[u] = cnt++;
}

// 双端队列优化版的 spfa：
int n, m;
bool inq[maxn];
int inqCnt[maxn]; // 记录结点入队次数
int d[maxn]; // 到各点的最短路
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

## [Floyd](https://wangxw.cn/htmls/p-k-d-f.html#H3-8)

> 求任意两点间最短距离 d[i][j]

代码理解起来相对来说最“暴力”，因为 Floyd 求的是任意两点间的最短路，所以势必要有 n^3^ 的复杂度，所以直接三重循环（i：起点，j：终点，k：起点终点之间任一点）即可

### 任意两点间最短路

```c++ {.lang-type-c++}
// 感觉有点动态规划的意思...
void floyd() {
    // 初始化距离数组，应在读入数据时初始化吧...
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         d[i][j] = INF;
    //     }
    //     d[i][i] = 0;
    // }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INF && d[k][j] < INF) {
                    // 避免两个初始 INF 相加后的和超过 INF，所以判断一下
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
}
```

<br>

### 有向图的闭包传递（Transitive Closure）

即：判断任意两点间是否直接或间接连通，Floyd 的三重循环稍加更改即可实现

```c++ {.lang-type-c++}
void tc() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = false;
        }
        d[i][i] = true;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = d[i][j] || (d[i][k] && d[k][j]);
            }
        }
    }
}
```

* `d[i][j]==true` 时从 i 到 j 直接或间接连通

* `d[i][j]==d[j][i]==true` 时两点相互连通