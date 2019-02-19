#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

/*
    不知道会不会超时啊...
    TODO 未提交
*/

const int maxn = 30005;
int fa[maxn];

int find(int i) {
    // 带路径压缩“fa[i] = find(fa[i])”的查找
    return fa[i] == i ? i : fa[i] = find(fa[i]);
}

int main() {
    int n, m;
    while (cin >> n >> m && n) {
        for (int i = 0; i < n; i++) {
            fa[i] = i;
        }
        int k, tempi, firstFa, p;
        for (int i = 0; i < m; i++) {
            cin >> k; // k 个组
            if (k) {
                cin >> tempi; // 第一个人
                firstFa = find(tempi);
                for (int j = 1; j < k; j++) {
                    // 每组
                    cin >> tempi;
                    p = find(tempi);
                    if (p != firstFa) {
                        fa[p] = firstFa;
                    }
                }
            }
        }
        int res = 0;
        p = find(0);
        for (int i = 0; i < n; i++) {
            if (find(i) == p) {
                res++;
            }
        }
        cout << res << endl;
    }

    return 0;
}
