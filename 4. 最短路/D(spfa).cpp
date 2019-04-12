#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    POJ 3268 Silver Cow Party
    172ms；0.9MB

    两次spfa。运用了转置的思想。
    所有牛的目标地点固定，因此从目标地点回家时可用一次 spfa 求出目标到各家的最短路 d1[i]，
    之后进行“矩阵转置”，即将“边”反转，之后，
    则，本应求从各家到目标地，又变成了求目标地到各家最短路 d2[i]，
    因此再一次 spfa 即可。
    而题目中要求从家到目标地与回家的路径之和最短，此时求所有牛中最大值，
    即求 d1[i]+d2[i] 的最大值即可。
*/

const int maxn = 1005, maxm = maxn * maxn;
// 前向星存边：
struct Edge {
    int to, w; // 边的原始数据
    int next;  // 与该边同起点的下一条边
} edge1[maxm], edge2[maxm];
int head1[maxn];
int head2[maxn];
int cnt1 = 0;
int cnt2 = 0;
void addEdge(int u, int v, int w) {
    edge1[cnt1].to = v;
    edge1[cnt1].next = head1[u];
    edge1[cnt1].w = w;
    head1[u] = cnt1++;
}
void addEdge2(int u, int v, int w) {
    edge2[cnt2].to = v;
    edge2[cnt2].next = head2[u];
    edge2[cnt2].w = w;
    head2[u] = cnt2++;
}

// 双端队列优化版的 spfa：
int n, m;
bool inq[maxn];
int inqCnt[maxn]; // 记录结点入队次数
int d1[maxn];
bool spfa1(int start) {
    for (int i = 0; i < n; i++) {
        // n个节点
        d1[i] = INF;
    }
    memset(inq, 0, sizeof(inq));
    memset(inqCnt, 0, sizeof(inqCnt));
    inqCnt[start] = 1;
    d1[start] = 0, inq[start] = true;
    deque<int> q; //双端队列
    q.push_front(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        inq[u] = false;

        //前向星遍历：
        for (int i = head1[u]; ~i; i = edge1[i].next) {
            int v = edge1[i].to;
            if (d1[v] > d1[u] + edge1[i].w) {
                d1[v] = d1[u] + edge1[i].w;
                if (inq[v])
                    continue;
                inq[v] = true;
                if (!q.empty() && d1[v] > d1[q.front()])
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

int d2[maxn];
bool spfa2(int start) {
    for (int i = 0; i < n; i++) {
        // n个节点
        d2[i] = INF;
    }
    memset(inq, 0, sizeof(inq));
    memset(inqCnt, 0, sizeof(inqCnt));
    inqCnt[start] = 1;
    d2[start] = 0, inq[start] = true;
    deque<int> q; //双端队列
    q.push_front(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        inq[u] = false;

        //前向星遍历：
        for (int i = head2[u]; ~i; i = edge2[i].next) {
            int v = edge2[i].to;
            if (d2[v] > d2[u] + edge2[i].w) {
                d2[v] = d2[u] + edge2[i].w;
                if (inq[v])
                    continue;
                inq[v] = true;
                if (!q.empty() && d2[v] > d2[q.front()])
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
    int tar; // 路、终点
    cin >> n >> m >> tar;
    for (int i = 0; i<n; i++) {
        head1[i] = -1;
        head2[i] = -1;
    }
    tar--; // 统一从 0 开始
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        addEdge(u - 1, v - 1, w);
        addEdge2(v - 1, u - 1, w);
    }

    // 每个点作起点，n 次 Dijkstra：
    memset(d1, 0, sizeof(d1));
    spfa1(tar);
    spfa2(tar);
    int maxtime = 0;

    for (int i = 0; i<n; i++) {
        maxtime = max(d1[i] + d2[i], maxtime);
    }

    cout << maxtime << endl;

    return 0;
}
