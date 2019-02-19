#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    POJ 3268 Silver Cow Party
    直接 n 次 Dijkstra 就好了...
    735ms 4756kB
*/

const int maxn = 1005;
int n = 0;
int d[maxn][maxn];

// 以下 Edge 和 Dij 直接为模板未改动，详见 README.md
struct Edge {
    int from, to, w;
    Edge(int u, int v, int w) : from(u), to(v), w(w) {}
};

struct Dij {
    int n, m;
    vector<Edge> edges;
    vector<int>
        G[maxn]; 
    bool done[maxn]; 
    int d[maxn];     
    int p[maxn];     

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
        int d, u;
        bool operator<(const HeapNode &rhs) const {
            return d > rhs.d;
        }
    };

    void dij(int s) {
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
                }
            }
        }
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

    // 每个点作起点，n 次 Dijkstra：
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++) {
        dij.dij(i);
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
