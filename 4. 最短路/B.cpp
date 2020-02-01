#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    POJ 2253 Frogger

    基于 Dijkstra 模板，修改如下：
    1. 预处理；因为题目中只给了点的位置，所以读数据时仅读入点坐标，并将点标号（0~n-1），并之后计算每两点之间距离，添加至 Dijkstra 的类中；
    2. 边的权重 w 由 int 类型改为 float 类型，并注意输出 3 位小数；
    3. 核心：修改 dance() 过程中的“松弛条件”，将原来“新的间接距离”与“现有距离”的关系改为原路径中最大 jump range 与新的两段路径 d[u]、e.w 的 jump range 的比较

*/

int n;
const int maxn = 201;

struct Edge {
    int from, to;
    float w; // 紫书这里用了 dist 表示 w
    Edge(int u, int v, float w) : from(u), to(v), w(w) {}
};

struct Dij {
    int n, m; // 点数，边数
    vector<Edge> edges;
    vector<int>
        G[maxn]; // 以 G 存点，以 vector 存该点的边，以便 Dij 中的遍历更新
    bool done[maxn]; // 是否已找到最短路
    float d[maxn];   // s（起点）到各点距离
    int p[maxn];     // 最短路中结点 j 的以其为终点的弧编号

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            G[i].clear();
        }
        edges.clear();
    }

    void addEdge(int from, int to, float w) {
        edges.push_back(Edge(from, to, w));
        m = edges.size();
        G[from].push_back(m - 1);
    }

    struct HeapNode {
        float d;
        int u; // 距离，终点（我觉得紫书这里应该用 v，与前面保持一致）
        bool operator<(const HeapNode &rhs) const {
            return d > rhs.d; // 距离越远优先级越低（越晚弹出）
        }
    };

    void dij(int s) {
        // 以 s 为起点

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

                // 新的松弛条件：
                // d数组：到达点i的路径上最长的边
                if (e.w < d[e.to] && d[u] < d[e.to]) {
                    d[e.to] = max(e.w, d[u]);
                    Q.push(HeapNode{d[e.to], e.to});
                }
            }
        }
    }
};

int main() {
    Dij dij;
    int caseCnt = 1;
    while (cin >> n && n) {
        dij.init(n);
        pair<int, int> node[maxn];
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cin >> node[cnt].first >> node[cnt].second;
            cnt++;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                float dis = sqrt(pow(node[i].first - node[j].first, 2) +
                                 pow(node[i].second - node[j].second, 2));
                dij.addEdge(i, j, dis);
                dij.addEdge(j, i, dis);
            }
        }
        dij.dij(0);
        cout << "Scenario #" << caseCnt++ << endl;
        cout << "Frog Distance = ";
        cout << setiosflags(ios::fixed) << setprecision(3) << dij.d[1]
             << "\n\n";
    }

    return 0;
}
