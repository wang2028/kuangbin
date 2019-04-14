#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

/*
    双重循环找到每个点 i 之后的高度小于等于 i 点高度的点集合存入 G[i]，
    之后遍历每个点，每次从集合 G[i]
    中找到第一个元素（i之后最高的点）继续作为 攻击 i 点导弹的攻击点，以此类推
*/

const int maxn = 200003;
int n;

bool exist[maxn];
struct Node {
    int hei;
    int idx;
} node[maxn];
set<Node> G[maxn]; // 记录点 i 之后的高度小于等于 i 点高度的点，
bool operator<(Node n1, Node n2) {
    if (n1.hei != n2.hei) {
        return n1.hei > n2.hei;
    } else {
        return n1.idx < n2.idx;
    }
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> node[i].hei;
            node[i].idx = i;
            exist[i] = true;
        }
        for (int i = n - 2; i >= 0; i--) {
            G[i].clear();
            for (int j = i + 1; j < n; j++) {
                if (node[j].hei <= node[i].hei) {
                    G[i].insert(node[j]);
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (exist[i]) {
                exist[i] = false; // 该点被访问过后置为不存在
                cnt++;
                Node nxt = node[i];
                while (G[nxt.idx].size()) {
                    set<Node>::iterator it = G[nxt.idx].begin();
                    while (it != G[nxt.idx].end() && !exist[it->idx]) {
                        // while 判断条件中顺序不能颠倒，
                        // 因为若先判断 exist 的话，可能 it 此时已经等于 end()，
                        // 会访问不到 it->idx 报错
                        it++;
                    }
                    if (it == G[nxt.idx].end()) {
                        break;
                    }
                    nxt = *it;
                    exist[nxt.idx] = false;
                }
            }
        }
        cout << cnt << endl;
    }

    return 0;
}
