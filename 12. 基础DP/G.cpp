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
    免费馅饼 HDU - 1176
    注意循环的内外层不要颠倒：
    外层遍历坐标，内层遍历时间时，会导致某点 i 的值 d[i][t] 并不是真实最大的值，
    因为时间 t 时的其他点的最大值（d[i][t] 的依赖值）还没有算出来。
*/

const int maxn = 13, maxm = 100005;

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        int x, t, maxt = 0;
        int bing[maxn][maxm]; // 这种初始化安全吗？
        memset(bing, 0, sizeof(bing));
        for (int i = 0; i < n; i++) {
            cin >> x >> t;
            bing[x][t]++;
            maxt = max(maxt, t);
        }
        int d[maxn][maxm];
        int maxSum = 0;
        for (int i = 0; i <= 11; i++) {
            for (int j = 0; j <= maxt; j++) {
                d[i][j] = -INF;
            }
        }
        d[5][0] = 0;
        for (int j = 1; j <= maxt; j++) {
            for (int i = 0; i <= 11; i++) {
                d[i][j] = max(d[i][j], d[i][j - 1] + bing[i][j]);
                if (i > 0) {
                    d[i][j] = max(d[i][j], d[i - 1][j - 1] + bing[i][j]);
                }
                if (i < 11) {
                    d[i][j] = max(d[i][j], d[i + 1][j - 1] + bing[i][j]);
                }
                if (j == maxt) {
                    maxSum = max(maxSum, d[i][j]);
                }
            }
        }
        cout << maxSum << endl;
    }

    return 0;
}
