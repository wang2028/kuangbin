#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    G - MPI Maelstrom POJ - 1502
    直接求起点到各点的最短路（手写的spfa），
    然后遍历一遍找其中最大的值即可，因为消息并发发送。
    混合读入数值和字符'x'写了好大会儿...最后
    终于想起来用 string 读入，然后用 stringstream 转换就行了...
*/

const int maxn = 103, maxm = maxn * maxn;

struct Edge {
    int to, w;
    int next;
} edge[maxm];
int head[maxn], cnt = 0;
void addEdge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}
int n;
int d[maxn];
bool spfa(int s) {
    for (int i = 0; i < n; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    bool inq[maxn];
    memset(inq, 0, sizeof(inq));
    deque<int> q;
    q.push_back(s);
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        inq[u] = false;
        for (int i = head[u]; ~i; i = edge[i].next) {
            Edge &e = edge[i];
            if (e.w + d[u] < d[e.to]) {
                d[e.to] = e.w + d[u];
                if (!q.empty() && d[e.to] < d[q.front()]) {
                    q.push_front(e.to);
                } else {
                    q.push_back(e.to);
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    string w;
    int cost;
    stringstream ss;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // 从 i 到 j 费用为 w
            cin >> w;
            if (w[0] == 'x') {
                continue;
            }
            ss.clear();
            ss << w;
            ss >> cost;
            addEdge(i, j, cost);
            addEdge(j, i, cost);
        }
    }
    spfa(0);
    int m = 0;
    for (int i = 1; i < n; i++) {
        m = max(d[i], m);
    }
    cout << m << endl;

    return 0;
}
