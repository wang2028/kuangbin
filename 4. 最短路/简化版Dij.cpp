#include <iostream>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define INF 0x3f3f3f3f;

const int maxn = 100;
struct Edge{
    int from, to, w;
};

int n, m;
vector<Edge> G[maxn];
bool done[maxn]; // 是否以求得点 i 的最短路
int dis[maxn]; // 从起点到点 i 的最短距离

struct HeapNode {
    int dis, to;
    bool operator<(const HeapNode &b) const { 
        return dis > b.dis; 
    }
};

void dij(int s){
    priority_queue<HeapNode> Q;
    memset(done, 0, sizeof(bool) * n);  // memory set
    for (int i = 0; i < n;i++){
        dis[i] = INF;
    }
    dis[s] = 0;
    Q.push(HeapNode{0, s});
    while(!Q.empty()){
        HeapNode x = Q.top(); // 取出距离最小的，这一步复杂度是 Logn，所以加快了
        Q.pop();
        int to = x.to;  // 取出 s'
        if(done[to]){
            continue;
        }
        done[to] = true;
        for (int i = 0; i < G[to].size();i++){
            Edge &e = G[to][i];   // G[i][j]:从点i出发的第j条边
            // 松弛：
            if(e.w + dis[to] < dis[e.to]){
                dis[e.to] = e.w + dis[to];
                Q.push(HeapNode{dis[e.to], e.to});
            }
        }
    }


}

int main() {
    cin >> n;
    int u, v, w; // 起点，终点，权值
    while(n--){
        cin >> u >> v >> w;
        G[u].push_back(Edge{u, v, w});
        G[v].push_back(Edge{v, u, w}); // 无向图
    }
    dij(0);

    // 现在，dis数组就是从0点开始到其他任一点的最短路径
    for (int i = 0;i<n;i++){
        cout << dis[i] << endl;
    }

    return 0;
}