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
    The Accomodation of Students HDU - 2444
    题意好模糊啊...搜了网上博客的中文题意才看懂...
    1. 先 dfs 交叉染色判断是否可二分（受博客启发）
    2. 若可二分，则将每对认识的人分一个房间，求最多房间数（能二人匹配的数），匈牙利算法
*/

const int maxn = 203, maxm = 203;
int n, m;
vector<int> know[maxn];

// 交叉染色判断是否可二分：
int color[maxn];
bool vis[maxn];
bool dfs(int t, int cur) {
    for (int i = 0; i < know[t].size(); i++) {
        if (color[know[t][i]] == cur) {
            return false;
        } else if (color[know[t][i]] == 0) {
            color[know[t][i]] = 3 - cur;
            if (!dfs(know[t][i], 3 - cur))
                return false;
        }
    }
    return true;
}

// 匈牙利求二分匹配：
int match[maxm];
bool marked[maxm];
int canPair = 0;
bool find(int x) {
    for (int i = 0; i < know[x].size(); i++) {
        int v = know[x][i];
        if (!marked[v]) {
            marked[v] = true;
            if (match[v] == -1 || find(match[v])) {
                // 判断条件中：前者 -1
                // 表示还未匹配过；后者表示为原配对象找到了新的匹配者
                match[v] = x;
                match[x] = v;
                return true;
            }
        }
    }
    return false;
}
void solve() {
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; i++) {
        memset(marked, 0, sizeof(marked));
        if (match[i] != -1 || find(i))
            canPair++;
    }
}

int main() {
    while (cin >> n >> m) {
        memset(know, 0, sizeof(know));
        int a, b;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            a--;
            b--;
            know[a].push_back(b);
            know[b].push_back(a);
        }

        // 交叉染色判断是否可二分：
        memset(color, 0, sizeof(color));
        memset(vis, 0, sizeof(vis));
        if (!dfs(0, 1)) {
            cout << "No" << endl;
            continue;
        }

        canPair = 0;
        solve();
        cout << canPair / 2 << endl;
    }

    return 0;
}