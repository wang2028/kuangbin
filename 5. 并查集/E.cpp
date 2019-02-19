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
    目测要爆栈...真爆的话换成 map 试试...map 可能会超时...还真得用向量并查集？
    TODO 未提交
*/

const int maxn = 50002, maxm = maxn * maxn;
int n = 0;
bool eat[maxn][maxn];
int fa[maxn];
int find(int i) { return fa[i] == i ? i : fa[i] = find(fa[i]); }

int main() {
    int k;
    scanf("%d%d", n, k);
    int type, x, y;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    int err = 0;
    int fax, fay;
    while (k--) {
        scanf("%d%d%d", type, x, y);
        if (x > n || y > n) {
            err++;
            continue;
        }
        if (type == 1) {
            if (eat[x][y] || eat[y][x]) {
                err++;
                continue;
            }
            fax = find(x);
            fay = find(y);
            if (fax != fay) {
                fa[fax] = fay;
            }
        } else {
            fax = find(x);
            fay = find(y);
            if (fax == fay) {
                err++;
                continue;
            }
            eat[x][y] = true;
        }
    }
    printf("%d\n", err);

    return 0;
}
