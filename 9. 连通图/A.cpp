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
    Network of Schools POJ - 1236
    强连通图（scc），用了 kosaraju 算法（不造为啥网上都是 tarjan算法）
*/

const int maxn = 103;

vector<int> G[maxn];
vector<int> Gg[maxn];
int n;
vector<int> S; // 存拓扑序的结点
bool vis[maxn];
int sccNo[maxn]; // 每个点所属SCC编号，从 1 开始
int sccCnt;

void dfs1(int u) {
    // 求拓扑序的 vector
    if (vis[u])
        return;
    vis[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        dfs1(G[u][i]);
    }
    S.push_back(u);
}

void dfs2(int u) {
    if (sccNo[u])
        return;
    sccNo[u] = sccCnt; // 将当前SCC编号赋给当前结点
    for (int i = 0; i < Gg[u].size(); i++) {
        dfs2(Gg[u][i]);
    }
}

void scc() {
    S.clear();
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        dfs1(i);
    }
    sccCnt = 0;
    memset(sccNo, 0, sizeof(sccNo));
    for (int i = S.size() - 1; i >= 0; i--) {
        if (!sccNo[S[i]]) {
            sccCnt++;
            dfs2(S[i]);
        }
    }
}

int main() {
    cin >> n;
    int t;
    for (int i = 0; i < n; i++) {
        while (cin >> t && t) {
            t--;
            G[i].push_back(t);
            Gg[t].push_back(i);
        }
    }

    scc();
    if (sccCnt == 1) {
        cout << "1\n0" << endl;
        return 0;
    }
    int ans = 0;
    int in[maxn] = {0}, out[maxn] = {0};
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            if (sccNo[i] != sccNo[G[i][j]]) {
                out[sccNo[i]]++;
                in[sccNo[G[i][j]]]++;
            }
        }
    }
    for (int i = 1; i <= sccCnt; i++) {
        if (!in[i]) {
            ans++;
        }
    }
    cout << ans << endl;

    int nonIn = 0, nonOut = 0;
    for (int i = 1; i <= sccCnt; i++) {
        if (!out[i])
            nonOut++;
        if (!in[i])
            nonIn++;
    }

    cout << max(nonIn, nonOut) << endl;

    return 0;
}