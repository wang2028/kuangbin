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
    尝试了简单的位图+记忆化搜索的解法，但 n 上限有点大，不便于实现，
    因此该方法搁置，转用正常的强连通分量SCC的方法（见 A.cpp）
*/

const int maxn = 103;

vector<int> G[maxn];
vector<int> G1[maxn];
int bitmap[maxn];
bool vis[maxn];
int n;

void findReach(int t, int start) {
    if (vis[t]) {
        bitmap[start] |= bitmap[t];
        return;
    }
    vis[t] = true;
    bitmap[start] |= (1 << t);
    for (int i = 0; i < G[t].size(); i++) {
        findReach(G[t][i], start);
    }
}

int main() {
    cin >> n;
    int t;
    for (int i = 0; i < n; i++) {
        while (cin >> t && t) {
            t--;
            G[i].push_back(t);
            G1[t].push_back(i);
        }
    }

    // 从每个点深搜一遍，将能到达的点记录在位图 map[i] 中
    // 之后再状态遍历一遍，合并（或运算） map[i,j,...] 后若全 1，则可行
    memset(vis, 0, sizeof(vis));
    memset(bitmap, 0, sizeof(bitmap));
    for (int i = 0; i < n; i++) {
        findReach(i, i);
    }

    // 状态遍历：
    int ans, minCopy = INF, num;
    for (int s = 0; s < (1 << n); s++) {
        ans = 0;
        num = 0;
        for (int i = 0; i < n; i++) {
            if (s & (1 << i)) {
                ans |= bitmap[i];
                num++;
            }
        }
        if (ans == (1 << n) - 1) {
            minCopy = min(minCopy, num);
        }
    }
    cout << minCopy << endl;

    int nonIn = 0, nonOut = 0;
    for (int i = 0; i < n; i++) {
        if (!G[i].size())
            nonOut++;
        if (!G1[i].size())
            nonIn++;
    }
    cout << max(nonIn, nonOut) << endl;

    return 0;
}