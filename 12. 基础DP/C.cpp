#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 9999
#define ll long long

/*
    C - Monkey and Banana HDU - 1069
    由紫书 DAG 型 DP 可扩展得知，将每一个立方体的三个面取任一面作底面，
    每一个底面作一个节点 i，该节点有 长len 宽wid 高hei 三个属性，
    遍历找到长宽均小于 i 的对应属性值的节点 j，作单向边 i->j，表示 i 上可以放 j，
    由 DP 的记忆化递归搜索可得每一个节点开始最多的高度 d[i]，
    遍历 d[i] 找到最大高度即为所求
*/

const int maxn = 31 * 3, maxm = 10005;
int d[maxn], maxValue;
bool vis[maxn];
vector<int> G[maxn];

struct node {
    int len, wid;
    int hei;
} nodes[maxn];

int maxHei(int t) {
    if (vis[t]) {
        return d[t];
    }
    vis[t] = true;
    d[t] = nodes[t].hei;
    for (int i = 0; i < G[t].size(); i++) {
        d[t] = max(d[t], nodes[t].hei + maxHei(G[t][i]));
    }
    return d[t];
}

int main() {
    int n, Case = 1;
    while (cin >> n && n) {
        int dim[3];
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int i = 0; i < 3; i++) {
                cin >> dim[i];
            }
            sort(dim, dim + 3);
            nodes[cnt].len = dim[1];
            nodes[cnt].wid = dim[0];
            nodes[cnt].hei = dim[2];
            cnt++;
            nodes[cnt].len = dim[2];
            nodes[cnt].wid = dim[1];
            nodes[cnt].hei = dim[0];
            cnt++;
            nodes[cnt].len = dim[2];
            nodes[cnt].wid = dim[0];
            nodes[cnt].hei = dim[1];
            cnt++;
        }
        for (int i = 0; i < maxn; i++) {
            G[i].clear();
        }
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < cnt; j++) {
                if (i != j) {
                    if (nodes[i].len < nodes[j].len &&
                        nodes[i].wid < nodes[j].wid) {
                        G[j].push_back(i);
                    }
                }
            }
        }
        memset(vis, 0, sizeof(vis));
        memset(d, 0, sizeof(d));
        maxValue = 0;
        for (int i = 0; i < cnt; i++) {
            maxValue = max(maxValue, maxHei(i));
        }
        cout << "Case " << (Case++) << ": maximum height = " << maxValue
             << endl;
    }

    return 0;
}
