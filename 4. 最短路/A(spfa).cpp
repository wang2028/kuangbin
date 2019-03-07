#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

const int maxn = 1001, maxm = maxn * maxn / 2;

// 前向星存边：
struct Edge {
    int to, w;
    int next; // 与改变同起点的下一条边
} edge[maxm];
int head[maxn];
int cnt = 0;
void add(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    edge[cnt].w = w;
    head[u] = cnt++;
}

// 双端队列优化版的 spfa：
int n, m;
bool inq[maxn];
int inqCnt[maxn]; // 记录结点入队次数
int d[maxn];
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
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        u--;
        v--;
        add(u, v, w);
        add(v, u, w);
    }
    spfa(0);
    cout << d[n - 1] << endl;

    return 0;
}
