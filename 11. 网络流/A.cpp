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
typedef long long ll;
typedef unsigned long long ull;

/*
    ACM Computer Factory POJ - 3436
    用了《挑战》上的最大流模板，将一个“机器 i”拆为“输入点 i”和“输出点 i+mac”，
    这两点之间用一条容量为机器处理量的边连接，
    再遍历所有机器，若某机器 i 的输出能够和某机器 j 的输入相同或匹配，
    则连接一条容量为 INF 的边。
*/

const int maxn = 106, maxp = 11, maxm = 7e4 + 7;
int part, mac;

typedef struct {
    ll from, to;
    int w;
} Mac;
Mac macs[maxn];

typedef struct edge {
    int to, cap, rev; // 终点，容量，反向边的序号
    int flow;
} Edge;
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
            // 此处判断 !vis[e.to]，若 e 的终点之前访问过便不访问，
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

bool match(ll a, ll b) {
    // 判断两个状态是否相同，如从 010 到 012 判为相同状态
    for (int i = 0; i < part; i++) {
        if (a % 10 == 2 || b % 10 == 2 || a % 10 == b % 10) {
            a /= 10;
            b /= 10;
        } else {
            return false;
        }
    }
    return true;
}
int main() {
    while (cin >> part >> mac) {
        for (int i = 0; i < maxm; i++) {
            G[i].clear();
        }

        for (int i = 0; i < mac; i++) {
            ll from = 0, to = 0, t;
            cin >> macs[i].w;
            for (int j = 0; j < part; j++) {
                cin >> t;
                from = from * 10 + t;
            }
            macs[i].from = from;

            for (int j = 0; j < part; j++) {
                cin >> t;
                to = to * 10 + t;
            }
            macs[i].to = to;
        }
        int start = 2 * mac;
        int end = start + 1;
        int end1 = 0;
        for (int i = 0; i < part; i++) {
            end1 = end1 * 10 + 1;
        }
        for (int i = 0; i < mac; i++) {
            if (match(0, macs[i].from)) {
                addEdge(start, i, INF);
            }
            if (match(end1, macs[i].to)) {
                addEdge(i + mac, end, INF);
            }
            addEdge(i, i + mac, macs[i].w);
            for (int j = 0; j < mac; j++) {
                if (i != j) {
                    if (match(macs[i].to, macs[j].from)) {
                        addEdge(i + mac, j, INF);
                    }
                }
            }
        }
        cout << maxFlow(start, end) << " ";
        int ans = 0;
        vector<int> ans1, ans2, ans3;
        for (int i = mac; i < 2 * mac; i++) {
            if (G[i].size()) {
                for (int j = 0; j < G[i].size(); j++) {
                    if (G[i][j].flow > 0 && G[i][j].to != end) {
                        ans++;
                        ans1.push_back(i - mac + 1);
                        ans2.push_back(G[i][j].to + 1);
                        ans3.push_back(G[i][j].flow);
                    }
                }
            }
        }
        cout << ans << endl;
        for (int i = 0; i < ans1.size(); i++) {
            cout << ans1[i] << " " << ans2[i] << " " << ans3[i] << endl;
        }
    }

    return 0;
}

/*
3 4
15  0 0 0  0 1 0
10  0 0 0  0 1 1
30  0 1 2  1 1 1
3   0 2 1  1 1 1
3 5
5   0 0 0  0 1 0
100 0 1 0  1 0 1
3   0 1 0  1 1 0
1   1 0 1  1 1 0
300 1 1 2  1 1 1
2 2
100  0 0  1 0
200  0 1  1 1
*/