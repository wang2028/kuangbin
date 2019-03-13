# 连通图

## 有向图

### 强连通分量 SCC（Kosaraju）

先 dfs 求出图 G 的拓扑序存入 vector，之后对原图的转置 Gg 逆 vector 序 dfs 出每个 SCC。

```C++ {.lant-type-C++}
const int maxn = 203;
vector<int> G[maxn], Gg[maxn]; // 原图及转置
vector<int> S;                 // 存拓扑序的结点
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
    for(int i = 0 ;i<n;i++){
        dfs1(i);
    }
    sccCnt = 0;
    memset(sccNo, 0, sizeof(sccNo));
    for(int i = S.size()-1;i>=0;i--){
        if(!sccNo[S[i]]){
            sccCnt++;
            dfs2(S[i]);
        }
    }
}
```
