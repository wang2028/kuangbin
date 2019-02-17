#include <algorithm>
#include <cmath>
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
    POJ - 2387 Til the Cows Come Home
    
    直接套模板即可，详见该目录下 README.md 中关于 Dijkstra 部分
*/

int trail, n;
const int maxn = 1001;

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

    void dij(int s) {
        // 以 s 为起点

        // typedef pair<int, int> pii // 定义二元组 (d[i],i) 来每次选 d
        // 最小的边和终点 priority_queue<pii, vector<pii>, greater<pii> >q
        // 但不太直观，所以之后还是用结构体 HeapNode

        priority_queue<HeapNode> Q;
        memset(done, 0, sizeof(bool) * n);
        for (int i = 0; i < n; i++) {
            d[i] = INF;
        }
        d[s] = 0;
        Q.push(HeapNode{0, s}); // 这个定义涨姿势
        while (!Q.empty()) {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (done[u])
                continue;
            done[u] = true;
            for (int i = 0; i < G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                if (e.w + d[u] < d[e.to]) {
                    d[e.to] = e.w + d[u];
                    p[e.to] = G[u][i];
                    Q.push(HeapNode{d[e.to], e.to});
                    // 第一次遍历因为初始化为 INF，所以所有点都会入队
                }
            }
        }
    }
};

int main() {
    Dij dij;
    cin >> trail >> n;
    dij.init(n);

    int u, v, w;
    for (int t = 0; t < trail; t++) {
        cin >> u >> v >> w;
        dij.addEdge(u - 1, v - 1, w);
        dij.addEdge(v - 1, u - 1, w); // 无向图每条边都是双向通行的
    }

    dij.dij(0);
    cout << dij.d[n - 1] << endl;

    return 0;
}
