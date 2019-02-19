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
#define INF 0x3f3f3f3f

/*
    A - Wireless Network POJ - 2236
    并查集
    TODO 未提交
*/

const int maxn = 1002;
int n = 0, maxd; // 点数、边数
int fa[maxn]; // 存每个点的父结点，基于该数组，通过并查集查找根结点（代表元）

typedef struct {
    int x, y;
    bool run; // 该电脑是好是坏
} Node;

int find(int i) {
    // 带路径压缩“fa[i] = find(fa[i])”的查找
    return fa[i] == i ? i : fa[i] = find(fa[i]);
}

int main() {
    cin >> n >> maxd;

    Node nodes[maxn];
    double d;
    for (int i = 0; i < n; i++) {
        cin >> nodes[i].x >> nodes[i].y;
        nodes[i].run = false;

        fa[i] = i; // 初始化
    }

    char op;         // 临时变量
    int node, node1; // 临时变量
    int fai, faj;    // 临时变量
    while (cin >> op) {
        if (op == 'O') {
            cin >> node;
            node--;
            nodes[node].run = true;
            for (int j = 0; j < n && nodes[j].run; j++) {
                d = sqrt(pow(nodes[node].x - nodes[j].x, 2) +
                         pow(nodes[node].y - nodes[j].y, 2));
                if (ceil(d) <= maxd) {
                    fai = find(node);
                    faj = find(j);
                    if (fai != faj) {
                        fa[fai] = faj;
                    }
                }
            }
        } else {
            cin >> node >> node1;
            node--;
            node1--;
            if (find(node) == find(node1)) {
                cout << "SUCCESS" << endl;
            } else {
                cout << "FAIL" << endl;
            }
        }
    }

    return 0;
}
