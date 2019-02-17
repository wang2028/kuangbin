#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

int fa[n];
bool bellman_ford(int s){
    // 带负权的求最短路
    // s 为起点，存储图的结构同 Dijkstra
    // 复杂度 nm

    queue<int> Q;
    int cnt[n]; // 记录某点迭代次数，当超过 n-1 次时，说明出现环
    bool inq[n]; // 该节点是否在队中
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0;i<n;i++){
        dis[i] = INF;
    }
    dis[s] = 0;
    inq[s] = true;
    Q.push(s);

    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        inq[u] = false;
        for(int i = 0;i<G[u].size();i++){
            Edge& e = edges[G[u][i]];
            if(d[u]<INF && d[e.to]>d[u]+e.w){
                d[e.to] = d[u] + e.w;
                fa[e.to] = G[u][i];
                if(!inq[e.to]) {
                    Q.push(e.to);
                    inq[e.to] = true;
                    cnt[e.to]++;
                    if(cnt[e.to]>n){
                        return false;
                        // 无解
                    }
                }
            }
        }
    }
    return true;
}

int main() {
 

    return 0;
}