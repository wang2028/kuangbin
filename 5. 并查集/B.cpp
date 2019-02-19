#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

/*
    The Suspects POJ - 1611 并查集
    直接并查集，将每个小组第一人之后的人都并入第一人的集合，
    最后找到第 0 号 suspect 的根结点，一重循环判断其他所有人的根结点，
    若与 0 号处于同一集合，则也是 suspect
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
