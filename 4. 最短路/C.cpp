#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
typedef long long ll;

using namespace std;
const int INF = 0x3f3f3f3f;

/*
    C - Heavy Transportation POJ - 1797
    922ms；3MB
    
    dijkstra 改一下松弛条件，cin 换成 scanf 就能过...
*/

const int maxn = 1003;
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
        int d, u; // 可承受容量，终点
        bool operator<(const HeapNode &rhs) const {
            return d < rhs.d; // 容量越小优先级越低（越晚弹出）
        }
    };

    void dij(int s) {
        // 以 s 为起点

        // typedef pair<int, int> pii // 定义二元组 (d[i],i) 来每次选 d
        // 最小的边和终点 priority_queue<pii, vector<pii>, greater<pii> >q
        // 但不太直观，所以之后还是用结构体 HeapNode

        priority_queue<HeapNode> Q;
        memset(done, 0, sizeof(bool) * n);

        // 初始化与模板不太一样：
        for (int i = 0; i < n; i++) {
            d[i] = 0;
        }
        d[s] = INF;
        Q.push(HeapNode{INF, s}); // 这个定义涨姿势

        while (!Q.empty()) {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (done[u])
                continue;
            done[u] = true;
            for (int i = 0; i < G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                // 松弛条件改为：
                if (min(e.w, d[u]) > d[e.to]) {
                    d[e.to] = min(e.w, d[u]);
                    p[e.to] = G[u][i];
                    Q.push(HeapNode{d[e.to], e.to});
                }
            }
        }
    }
};

int main() {
    int T;

    scanf("%d", &T);
    int n, m;
    for (int t = 1; t <= T; t++) {
        scanf("%d%d", &n, &m);

        Dij dij;
        dij.init(n);

        int u, v, w;
        for (int i = 0; i < m; i++) {

            scanf("%d%d%d", &u, &v, &w);
            u--;
            v--;
            dij.addEdge(u, v, w);
            dij.addEdge(v, u, w);
        }
        dij.dij(0);
        printf("Scenario #%d:\n", t);
        printf("%d\n\n", dij.d[n - 1]);
    }

    return 0;
}