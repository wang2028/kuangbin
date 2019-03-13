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
#define INF 1e9
#define ll long long

// TODO

const int maxn = 1000005, maxm = 10005;
int d[maxn];
int dd[2][maxn];
int origin[maxn];
int main() {
    int n, m;
    while (~scanf("%d%d", &m, &n)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &origin[i]);
        }

        for (int j = 0; j <= m; j++)
            d[j] = -INF;

        for (int i = 0; i <= m; i++) {
            dd[0][i] = -INF;
        }
        dd[0][0] = 0;
        int tmp;

        d[0] = 0;
        int ans = -INF;
        int tt = 0;
        for (int i = 1; i <= n; i++) { //
            tmp = -INF;
            for (int j = 1; j <= m; j++) {
                // dp[i][j]=max(dp[i-1][j], max(dp[1..i-1][j-1]))+a[i]
                d[j] = max(d[j], dd[tt][j - 1]) + origin[i]; 
                dd[tt ^ 1][j] = max(d[j], dd[tt][j]);
            }
            ans = max(ans, d[m]);
            tt ^= 1;
        }
        cout << ans << endl;
    }

    return 0;
}
