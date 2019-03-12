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
#define INF 0x3f3f3f3f

/*
    wrong anwser!
    TODO 咋都过不了，网上数据测试也没问题，不写了！！！
*/

const int maxbase = 520;
const int maxn = 2505, maxm = maxn * maxn; // 最大点、边数
int n = 0, m = 0;                          // 点数、边数

int w[maxm]; // 每个边的权值
int u[maxm]; // 每个边的起点
int v[maxm]; // 每个边的终点

int r[maxm]; // 用来对“边”间接排序的数组
int p[maxn]; // i 的父结点（基于并查集，用来查找其根结点）

bool cmp(const int i, const int j) {
    // 间接查找中的比较函数
    // 排的是 i,j 的序，但依据是 w[i],w[j]
    return w[i] < w[j];
}

int findRoot(int i) {
    // 并查集中查找点 i 的根
    if (p[i] == i)
        return i;
    else
        return p[i] = findRoot(p[i]);
    // 顺便直接将 i 的父结点更新为集合的根，以提高之后的找根效率
}

int kruscal() {
    // 返回最小生成树的权值
    // 最小生成树的边存在 ansEdge 中

    for (int i = 0; i < n; i++) {
        p[i] = i; // 初始化并查集，p[i] == i 时它自己就是根
    }
    for (int i = 0; i < m; i++) {
        r[i] = i; // 初始化边序号
    }

    int ans = 0; // 最终权值和
    int e, x, y;
    sort(r, r + m, cmp);
    for (int i = 0; i < m; i++) {
        e = r[i];
        x = findRoot(u[e]);
        y = findRoot(v[e]);
        if (x != y) {
            ans += w[e];
            p[x] = y; // 把根 y 作为根 x 的父结点，即把 x 集合并入 y
        }
    }
    return ans;
}

typedef struct node {
    int x, y;
    int step; // 到达该点的步数
} Node;
Node start;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int qipan[maxbase][maxbase];
vector<Node> aliens;
int edgeCnt = 0;
bool reached[maxbase][maxbase];

void bfs(Node start, int startNum) {
    memset(reached, 0, sizeof(reached));
    queue<Node> q;
    q.push(start);
    reached[start.x][start.y] = true;
    Node tempn;
    while (!q.empty()) {
        tempn = q.front();
        q.pop();
        Node next;
        for (int i = 0; i < 4; i++) {
            next.x = tempn.x + dir[i][0];
            next.y = tempn.y + dir[i][1];
            next.step = tempn.step + 1;
            if (qipan[next.x][next.y] != -1 && !reached[next.x][next.y]) {
                reached[next.x][next.y] = true;
                if (qipan[next.x][next.y] != -2) {
                    // 此时是用序号表示的外星人
                    u[edgeCnt] = startNum;
                    v[edgeCnt] = qipan[next.x][next.y];
                    w[edgeCnt] = next.step;
                    edgeCnt++;
                    // 不再推入队列，并同时以此开始遍历，
                    // 这样会使BFS几乎是从每个非空白点均进行一次，
                    // 来求每个点到其他任意点的最小距离，耗时较大，
                    // 但因为此时不再向队列推入该点，所以也会减少些计算，
                    q.push(next);
                } else {
                    q.push(next);
                }
            }
        }
    }
}

int main() {
    int T, row, col;
    char str[maxbase + 10];
    scanf("%d", &T);
    char tempc;
    while (T--) {
        memset(qipan, 0, sizeof(qipan));
        aliens.clear();
        scanf("%d%d", &col, &row);
        gets(str);
        int kruCnt = 1;
        for (int i = 0; i < row; i++) {
            gets(str);
            for (int j = 0; j < col; j++) {
                tempc = str[j];
                if (tempc == ' ') {
                    qipan[i][j] = -2;
                } else if (tempc == '#') {
                    qipan[i][j] = -1;
                } else if (tempc == 'A') {
                    qipan[i][j] = kruCnt++;
                    aliens.push_back({i, j, 0});
                } else if (tempc == 'S') {
                    qipan[i][j] = 0;
                    start.x = i;
                    start.y = j;
                }
            }
        }
        start.step = 0;
        // 先从起点 bfs 确定所有点之间的路径长度
        bfs(start, 0);
        for (int i = 0; i < aliens.size(); i++) {
            bfs(aliens[i], i + 1);
        }

        n = kruCnt;
        m = edgeCnt;
        cout << kruscal() << endl;
    }

    return 0;
}
