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
    282ms；7.8MB
    
    spfa 改一下松弛条件，cin 换成 scanf，
    一直 WA，原来是因为全局变量 n、m 被我又设的 main 里的同名的局部变量覆盖了，
    导致全局 n、m 一直为 0！
*/

const int maxn = 1003, maxm = maxn * maxn;
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
int d[maxn];
bool spfa(int start) {
    for (int i = 0; i < n; i++) {
        // n个节点
        d[i] = 0;
    }
    memset(inq, 0, sizeof(inq));
    memset(inqCnt, 0, sizeof(inqCnt));
    inqCnt[start] = 1;
    d[start] = INF, inq[start] = true;
    deque<int> q; //双端队列
    q.push_front(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        inq[u] = false;

        //前向星遍历：
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].to;
            if (d[v] < min(d[u], edge[i].w)) {
                d[v] = min(d[u], edge[i].w);
                if (inq[v])
                    continue;
                inq[v] = true;
                if (!q.empty() && d[v] < d[q.front()])
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
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            head[i] = -1;
        }

        int u, v, w;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            u--;
            v--;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        spfa(0);
        printf("Scenario #%d:\n", t);
        printf("%d\n\n", d[n - 1]);
    }

    return 0;
}