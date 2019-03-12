#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

const int maxn = 505, maxm = 100005;
// 前向星存边：
struct Edge
{
    int to, w;
    int next; // 与改变同起点的下一条边
    bool type;
} edge[maxm];
int head[maxn];
int cnt = 0;
void add(int u, int v, int w, bool t)
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    edge[cnt].w = w;
    edge[cnt].type = t;
    head[u] = cnt++;
}

// 双端队列优化版的 spfa：
int n, m;
bool inq[maxn];
int d[maxn];
int ds[maxn];
int curSmallDis[maxn];
bool spfa(int start)
{
    for (int i = 0; i < n; i++)
    {
        // n个节点
        d[i] = INF;
        ds[i] = INF;
    }
    memset(curSmallDis, 0, sizeof(curSmallDis));
    memset(inq, 0, sizeof(inq));
    d[start] = 0;
    ds[start] = 0;
    inq[start] = true;
    deque<int> q; //双端队列
    q.push_front(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        inq[u] = false;

        //前向星遍历：
        for (int i = head[u]; ~i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (edge[i].type)
            {
                // 小路
                int s = ds[u] - curSmallDis[u] * curSmallDis[u] + (curSmallDis[u] + edge[i].w) * (curSmallDis[u] + edge[i].w);
                s = min(s, d[u] + edge[i].w * edge[i].w);
                if (s < d[v])
                {
                    ds[v] = s;
                    curSmallDis[v] = curSmallDis[u] + edge[i].w;
                    if (inq[v])
                        continue;
                    inq[v] = true;
                    if (!q.empty() && d[v] > d[q.front()])
                        q.push_back(v);
                    else
                        q.push_front(v);
                }
            }
            else
            {
                int b = d[u] + edge[i].w;
                if (b < d[v])
                {
                    d[v] = b;
                    if (inq[v])
                        continue;
                    inq[v] = true;
                    if (!q.empty() && d[v] > d[q.front()])
                        q.push_back(v);
                    else
                        q.push_front(v);
                }
            }
        }
    }
    return true;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        head[i] = -1;
    }
    int t, a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> t >> a >> b >> c;
        a--;
        b--;
        add(a, b, c, t);
    }
    spfa(0);
    cout << min(d[n - 1], ds[n - 1]) << endl;

    return 0;
}