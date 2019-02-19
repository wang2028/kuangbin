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
    E - 食物链 POJ - 1182
    本来我觉得直接最简单的并查集配合判断就出来了，WA+TLE
    本来我以为这道题的扩展并查集中向量可正可负，
    最后还是按照网上的方法，，，真香（注意 %3）
    不过还是怀疑，A 吃 C，B 吃 C，那么 B 和 A 就是同类吗？
    TODO 仍然需要理解
*/

const int maxn = 50009;
int n = 0, k;
int offset[maxn];
int fa[maxn];
int find(int i) {
    if (fa[i] == i) {
        return i;
    } else {
        int p = fa[i];
        fa[i] = find(fa[i]);
        offset[i] = (offset[i] + offset[p]) % 3;

        return fa[i];
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        offset[i] = 0;
    }
    int err = 0;
    int fax, fay;
    while (k--) {
        int type, x, y;
        scanf("%d%d%d", &type, &x, &y);

        if (x > n || y > n) {
            err++;
            continue;
        }

        fax = find(x);
        fay = find(y);
        if (fax == fay) {
            if ((offset[x] - offset[y] + 3) % 3 != type - 1) {
                err++;
                continue;
            }
        } else {
            fa[fax] = fay;
            offset[fax] = (type - 1 - (offset[x] - offset[y]) + 3) % 3;
        }
    }
    printf("%d\n", err);

    return 0;
}
