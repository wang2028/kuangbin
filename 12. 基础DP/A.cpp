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

// TODO 未过 ？？？

const int maxn = 1000005, maxm = 10005;
int main() {
    int n, m;
    int origin[maxn];
    while (~scanf("%d%d", &m, &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &origin[i]);
        }
        int d[maxn];
        int dd[maxn];
        memset(d, 0, sizeof(d));
        for (int i = 0; i < maxn; i++) {
            dd[i] = -INF;
        }
        dd[0] = 0;
        int tmp;
        for (int j = 1; j <= m; j++) {
            tmp = -INF;
            for (int i = 0; i < n; i++) {
                d[j] = max(d[j], dd[j - 1]) + origin[i];
                if (j != 1) {
                    dd[j - 1] = tmp;
                }
                tmp = max(d[j], dd[j]);
            }
            dd[m] = tmp;
        }
        cout << tmp << endl;
    }

    return 0;
}
