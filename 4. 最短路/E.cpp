#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    E - Currency Exchange POJ - 1860
    TODO 未提交
*/

const int maxn = 102;
int kind, point, originKind;
double originNum;
double rc[maxn * maxn][2];

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
    double d[maxn];  // s（起点）到各点距离

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
            d[i] = 0;
        }
        d[s] = originNum;
        inq[s] = true;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for (int i = 0; i < G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                if (d[u] < INF && d[e.to] < (d[u] - rc[e.w][1]) * rc[e.w][0]) {
                    d[e.to] = (d[u] - rc[e.w][1]) * rc[e.w][0];
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
    cin >> kind >> point >> originKind >> originNum;
    dij.init(kind);
    originKind--;
    int kinda, kindb;
    double rab, rba, cab, cba;
    int rcCnt = 0;
    for (int p = 0; p < point; p++) {
        cin >> kinda >> kindb >> rab >> cab >> rba >> cba;
        rc[rcCnt][0] = rab;
        rc[rcCnt][1] = cab;
        dij.addEdge(kinda - 1, kindb - 1, rcCnt);
        rcCnt++;
        rc[rcCnt][0] = rba;
        rc[rcCnt][1] = cba;
        dij.addEdge(kindb - 1, kinda - 1, rcCnt);
    }
    dij.bf(originKind);
    // cout << dij.d[originKind] << endl;
    if (dij.d[originKind] > originNum) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
