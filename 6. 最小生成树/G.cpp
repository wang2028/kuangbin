#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <queue>
#include <set>
#include <sstream>
#include <vector>

using namespace std;
#define INF 0x3f3f3f3f

/*
    G - Arctic Network POJ - 2349
    最短路模板，
    给出的卫星个数 s 可使 s-1 处相互连接，所以要生成树的 n-1 条边现在只用
    考虑 n-1-(s-1) 条边即可。
*/

// 因为是无向图，且kruscal的每条无向边只用考虑一次，所以 maxm 可以除以 2
const int maxn = 503, maxm = maxn * maxn / 2;

struct Node {
    int x, y;
} node[maxn];

int fa[maxn];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int sate, n, m;

struct Edge {
    int from, to;
    float w;
} edge[maxm];
bool cmp(Edge e1, Edge e2) { return e1.w < e2.w; }
float kruscal() {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
    sort(edge, edge + m, cmp);
    int need = n - 1 - (sate - 1);
    int pa, pb;
    int cnt = 0; // counter
    float ans = 0;
    while (need) {
        pa = find(edge[cnt].from);
        pb = find(edge[cnt].to);
        if (pa != pb) {
            fa[pa] = pb; // 别忘了更新
            ans = max(ans, edge[cnt].w);
            need--;
        }
        cnt++;
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> sate >> n;
        int x, y;
        for (int i = 0; i < n; i++) {
            cin >> node[i].x >> node[i].y;
        }
        m = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edge[m].from = i;
                edge[m].to = j;
                edge[m].w = sqrt(pow(node[i].x - node[j].x, 2) +
                                 pow(node[i].y - node[j].y, 2));
                m++;
            }
        }
        printf("%.2f\n", kruscal());
    }

    return 0;
}