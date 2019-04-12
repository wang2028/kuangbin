#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

const int maxn = 1005, maxm = 1003;

/*
    C - How Many Tables HDU - 1213
    并查集模板
*/

int fa[maxn];
set<int> table;

int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = find(fa[x]);
}

int main() {
    int T;
    cin >> T;
    int n, m;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            fa[i] = i;
        }
        table.clear();
        int pa, pb, a, b;
        while (m--) {
            cin >> a >> b;
            a--;
            b--;
            pa = find(a);
            pb = find(b);
            if (pa != pb) {
                fa[pb] = pa;
            }
        }
        for (int i = 0; i < n; i++) {
            table.insert(find(i));
        }
        cout << table.size() << endl;
    }

    return 0;
}