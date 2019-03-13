#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;

/*
    Network UVA - 315
    应该用 tarjan 模板的，但我直接暴力，每次删一个点后 dfs 查连通分量数目，
    也过了...看来测试数据很小...
*/

const int maxn = 103;

vector<int> G[maxn];
vector<int> Gg[maxn];
int curDel;
bool vis[maxn];

void dfs(int t) {
    if (vis[t])
        return;
    vis[t] = true;
    for (int i = 0; i < G[t].size(); i++) {
        if (G[t][i] != curDel) {
            dfs(G[t][i]);
        }
    }
}

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        int u, v;
        char c;
        while (scanf("%d", &u) && u) {
            u--;
            do {
                scanf("%d%c", &v, &c);
                v--;
                G[u].push_back(v);
                G[v].push_back(u);
            } while (c != '\n');
        }

        int originScc = 0;
        curDel = -1;
        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < n; j++) {
            if (!vis[j]) {
                originScc++;
                dfs(j);
            }
        }
        int critical = 0;
        for (int i = 0; i < n; i++) {
            memset(vis, 0, sizeof(vis));
            curDel = i;
            int scc = 0;
            for (int j = 0; j < n; j++) {
                if (!vis[j] && j != i) {
                    scc++;
                    dfs(j);
                }
            }
            if (scc > originScc) {
                critical++;
            }
        }
        cout << critical << endl;

        for (int i = 0; i < n; i++) {
            G[i].clear();
        }
    }

    return 0;
}