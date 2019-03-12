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
#define INF 0x7fffffff
#define ll long long

/*
    看《挑战》上解法，因为不确定动物到底属于A、B、C哪一类，
    只能确定其相对的捕食关系，所以将某动物“拆点”为3点，
    也就是分为3个集合 Sn，分别用 x、x+n、x+2*n 表示 x 属于 A、B、C，
    若 x1 与 x2+n 同属 Sn，则表示当 x1 是 A 时，x2 一定是 B，以此类推，
    也就是同时维护三个集合，在每一个集合中，动物们的相对关系是一定的，
    但不确定到底是 A、B、C 中哪一个，并且用 +0、+n、+2*n 的关系来表示其相对关系
*/

const int maxn = 50005, maxm = 23;

int fa[maxn * 3];
int hei[maxn * 3];
int find(int a) {
    if (a == fa[a])
        return a;
    return fa[a] = find(fa[a]);
}

// void unite(int x, int y) {
//    int a = find(x);
//    int b = find(y);
//    if (a == b) return;
//    if (hei[a] < hei[b]) {
//        fa[a] = b;
//    }
//    else {
//        fa[b] = a;
//        if (hei[a] == hei[b]) {
//            hei[a]++;
//        }
//    }
//}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int ans = 0;
    int t, x, y;
    for (int i = 0; i <= n * 3; i++) {
        fa[i] = i;
        hei[i] = 0;
    }
    while (k--) {
        scanf("%d%d%d", &t, &x, &y);
        if (x > n || x < 0 || y > n || y < 0) {
            ans++;
            continue;
        }
        x--;
        y--;
        if (t == 1) {
            if (find(x) == find(y + n) || find(x) == find(y + 2 * n)) {
                ans++;
                continue;
            } else {
                fa[find(x)] = find(y);
                fa[find(x + n)] = find(y + n);
                fa[find(x + 2 * n)] = find(y + 2 * n);
                // unite(x, y);
                // unite(x+n, y+n);
                // unite(x+2*n, y+2*n);
            }
        } else {
            if (find(x) == find(y) || find(x) == find(y + 2 * n)) {
                ans++;
                continue;
            } else {
                fa[find(x)] = find(y + n);
                fa[find(x + n)] = find(y + 2 * n);
                fa[find(x + 2 * n)] = find(y);
                // unite(x, y + n);
                // unite(x + n, y + 2 * n);
                // unite(x + 2 * n, y);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
