#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
typedef long long ll;

using namespace std;
const int INF = 0x3f3f3f3f;

/*
    B - Dining POJ - 3281

    因为有三个约束：
        1. 每份食物（或饮料）仅能给一头牛吃，所以其入边（或出边）的容量是 1
        2. 每头牛只能吃一份，所以牛的入边或出边容量也是 1
        3. 要求解食物和饮料同时满足的最大个数，所以食物和饮料要有联系

    建图：源点 -1- 食物 -1- 牛 -1- 牛 -1- 饮料 -1- 汇点，
    -1- 表示容量为 1 的边；将“牛”拆点以保证不连接源点和汇点的中间点的牛仅能吃一份
        
    思路：添加源点及汇点，建如上的图，跑最大流
        （没用 dinic，用了 Ford-Fulkerson）

    对所有的点编码（food 为食物种类，dri 为饮料数量，cow 为牛数量）：
        食物：0~food-1
        饮料：food~food+dri-1
        牛：food+dri~food+dri+cow-1、food+dri+cow~food+dri+cow*2-1
        源点：food+dri+cow*2
        汇点：food+dri+cow*2+1
*/

const int maxn = 410, maxm = 22000;

typedef struct edge {
    int to, cap, rev; // 终点，容量，反向边的序号
    int flow; // 流量，值为正数时为正向边，否则为反向边
} Edge;
vector<Edge> G[maxn];
bool vis[maxn];
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
            // 此处判断 !vis[e.to]，若 e 的终点之前访问过就不再访问，
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
int cow, food, dri;

int main() {
    cin >> cow >> food >> dri;
    int f, d, t;
    for (int i = 0; i < cow; i++) {
        cin >> f >> d;
        for (int j = 0; j < f; j++) {
            cin >> t;
            t--;
            addEdge(t, food + dri + i, 1);
        }
        addEdge(food + dri + i, food + dri + cow + i, 1);
        for (int j = 0; j < d; j++) {
            cin >> t;
            t--;
            addEdge(food + dri + cow + i, food + t, 1);
        }
    }
    for (int i = 0; i < food; i++) {
        addEdge(food + cow * 2 + dri, i, 1);
    }
    for (int i = 0; i < dri; i++) {
        addEdge(food + i, food + cow * 2 + dri + 1, 1);
    }
    cout << maxFlow(food + cow * 2 + dri, food + cow * 2 + dri + 1) << endl;

    return 0;
}