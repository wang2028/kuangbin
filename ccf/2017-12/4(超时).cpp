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

// 暴力回溯

const int maxn = 505, maxm = 100005;
int n, m;

typedef struct edge
{
    int w;
    bool t;
    edge()
    {
        w = -1;
    }
} Edge;
Edge edge[maxn][maxn];

int cur = 0, curMin = INF;
int small = 0;
bool vis[maxn];
void back(int t)
{
    if (t == n - 1)
    {
        curMin = min(cur, curMin);
        return;
    }
    if (cur >= curMin)
    {
        return;
    }
    vis[t] = true;
    for (int i = 0; i < n; i++)
    {
        if (edge[t][i].w != -1 && !vis[i])
        {
            if (edge[t][i].t)
            {
                // 小道
                if (small)
                {
                    cur -= small * small;
                    small += edge[t][i].w;
                    cur += small * small;
                    back(i);
                    cur -= small * small;
                    small -= edge[t][i].w;
                    cur += small * small;
                }
                else
                {
                    small += edge[t][i].w;
                    cur += small * small;
                    back(i);
                    cur -= small * small;
                    small = 0;
                }
            }
            else
            {
                int tempi = small;
                small = 0;
                cur += edge[t][i].w;
                back(i);
                small = tempi;
                cur -= edge[t][i].w;
            }
        }
    }
    vis[t] = false;
}

int main()
{
    cin >> n >> m;
    int t, a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> t >> a >> b >> c;
        a--;
        b--;
        edge[a][b].w = c;
        edge[a][b].t = t;
        edge[b][a].w = c;
        edge[b][a].t = t;
    }
    memset(vis, 0, sizeof(vis));
    back(0);
    cout << curMin << endl;

    return 0;
}
