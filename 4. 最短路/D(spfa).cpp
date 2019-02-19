#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    POJ 3268 Silver Cow Party
    spfa 算法，即 Bellman_Ford 算法
    模板同 Dijkstra，只将原 dij() 方法换成了 bf()
    625ms 4760kB
*/

const int maxn = 1005;
int n = 0;
int d[maxn][maxn];
int dis[maxn];

struct Edge {
    int from, to, w; // 紫书这里用了 dist 表示 w
    Edge(int u, int v, int w) : from(u), to(v), w(w) {}
};

struct Dij {
    int n, m; // 点数，边数
    vector<Edge> edges;
    vector<int>
        G[maxn]; // 以 G 存点，以 vector 存该点的边，以便 Dij 中的遍历更新
    bool done[maxn]; // 是否已找到最短路
    int d[maxn];     // s（起点）到各点距离
    int p[maxn];     // 最短路中结点 j 的以其为终点的弧编号

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
        bool operator<(const HeapNode &rhs) const {
            return d > rhs.d; // 距离越远优先级越低（越晚弹出）
        }
    };

    bool bf(int s) {
        // 带负权的求最短路
        // s 为起点，存储图的结构同 Dijkstra
        // 复杂度 nm

        queue<int> Q;
        int cnt[maxn]; // 记录某点迭代次数，当超过 n-1 次时，说明出现环
        bool inq[maxn]; // 该节点是否在队中
        memset(inq, 0, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            d[i] = INF;
        }
        d[s] = 0;
        inq[s] = true;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for (int i = 0; i < G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                if (d[u] < INF && d[e.to] > d[u] + e.w) {
                    d[e.to] = d[u] + e.w;
                    if (!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = true;
                        cnt[e.to]++;
                        if (cnt[e.to] > n) {
                            return false;
                            // 无解
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    Dij dij;
    int m, tar; // 路、终点
    cin >> n >> m >> tar;
    dij.init(n);
    tar--; // 统一从 0 开始
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        dij.addEdge(u - 1, v - 1, w);
    }
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++) {
        dij.bf(i);
        for (int j = 0; j < n; j++) {
            d[i][j] = dij.d[j];
        }
    }
    int maxtime = 0;
    for (int i = 0; i < n; i++) {
        maxtime = max(maxtime, d[i][tar] + d[tar][i]);
    }
    cout << maxtime << endl;

    return 0;
}
