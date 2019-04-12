#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    F - Wormholes POJ - 3259
    spfa，当入队次数 inqCnt[i]>n 时，出现负权圈，
    即此时可以完成穿越
*/

const int maxn = 503, maxm = 2503 * 2 + 203;

struct Edge {
    int to, w; // 边的原始数据
    int next;  // 与该边同起点的下一条边
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
int d[maxn];      // 到各点的最短路
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
                if (++inqCnt[v] > n)
                    return false;
            }
        }
    }
    return true;
}

int main() {
    int F;
    cin >> F;
    int w;
    int s, e, t;
    while (F--) {
        cin >> n >> m >> w;
        for (int i = 0; i < n; i++) {
            head[i] = -1;
        }
        cnt = 0;
        for (int i = 0; i < m; i++) {
            cin >> s >> e >> t;
            addEdge(s - 1, e - 1, t);
            addEdge(e - 1, s - 1, t);
        }
        for (int i = 0; i < w; i++) {
            cin >> s >> e >> t;
            addEdge(s - 1, e - 1, -t);
        }
        m += w;
        cout << (spfa(0) ? "NO" : "YES") << endl;
        memset(edge, 0, sizeof(edge));
    }

    return 0;
}
