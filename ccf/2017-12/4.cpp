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

/*
    Dijkstra，虽然100分，但是其实是不对的。。。有点问题。。。
*/

const ll maxn = 505, maxm = 100005;
ll n, m;

struct Edge
{
    ll from, to, w; // 紫书这里用了 dist 表示 w
    bool type;      // false：大道；true：小道
    Edge(ll u, ll v, ll w, bool t) : from(u), to(v), w(w), type(t) {}
};

struct Dij
{
    ll n, m; // 点数，边数
    vector<Edge> edges;
    vector<ll> G[maxn]; // 以 G 存点，以 vector 存该点的边，以便 Dij 中的遍历更新
    bool done[maxn];    // 是否已找到最短路
    ll d[maxn];         // s（起点）到各点距离
    ll p[maxn];         // 最短路中结点 j 的以其为终点的弧编号

    void init(ll n)
    {
        this->n = n;
        for (ll i = 0; i < n; i++)
        {
            G[i].clear();
        }
        edges.clear();
    }

    void addEdge(ll from, ll to, ll w, bool t)
    {
        edges.push_back(Edge(from, to, w, t));
        m = edges.size();
        G[from].push_back(m - 1);
    }

    struct HeapNode
    {
        ll d, u;        // 距离，终点（我觉得紫书这里应该用 v，与前面保持一致）
        ll curSmallDis; // 当前累计小道长度，在算新的长度时，d 先减去此值的平方，再加上新此值的平方
        bool operator<(const HeapNode &rhs) const
        {
            return d > rhs.d; // 距离越远优先级越低（越晚弹出）
        }
    };

    void dij(ll s)
    {
        // 以 s 为起点

        // typedef pair<ll, ll> pii // 定义二元组 (d[i],i) 来每次选 d 最小的边和终点
        // priority_queue<pii, vector<pii>, greater<pii> >q
        // 但不太直观，所以之后还是用结构体 HeapNode

        priority_queue<HeapNode> Q;
        memset(done, 0, sizeof(bool) * n);
        for (ll i = 0; i < n; i++)
        {
            d[i] = INF;
        }
        d[s] = 0;
        Q.push(HeapNode{0, s, 0}); // 这个定义涨姿势
        while (!Q.empty())
        {
            HeapNode x = Q.top();
            Q.pop();
            ll u = x.u;
            if (done[u])
                continue;
            done[u] = true;
            for (ll i = 0; i < G[u].size(); i++)
            {
                Edge &e = edges[G[u][i]];
                ll newW = x.d;
                ll small = x.curSmallDis;
                if (small)
                {
                    // 有小道的积累
                    if (e.type)
                    {
                        // 小道
                        newW -= small * small;
                        small += e.w;
                        newW += small * small;
                    }
                    else
                    {
                        small = 0;
                        newW += e.w;
                    }
                }
                else
                {
                    if (e.type)
                    {
                        newW += e.w * e.w;
                        small = e.w;
                    }
                    else
                    {
                        newW += e.w;
                        small = 0;
                    }
                }
                // 可能此时小道，被替换，但下一步仍是小道，反而高了？
                if (newW < d[e.to])
                {
                    d[e.to] = newW;
                    p[e.to] = G[u][i];
                    Q.push(HeapNode{d[e.to], e.to, small});
                    // 第一次遍历因为初始化为 INF，所以所有点都会入队
                }
            }
        }
    }
};
int main()
{
    Dij dij;
    cin >> n >> m;
    dij.init(n);
    ll t, a, b, c;
    for (ll i = 0; i < m; i++)
    {
        cin >> t >> a >> b >> c;
        a--;
        b--;
        dij.addEdge(a, b, c, t);
        dij.addEdge(b, a, c, t);
    }
    dij.dij(0);
    cout << dij.d[n - 1] << endl;

    return 0;
}
