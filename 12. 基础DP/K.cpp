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
#define INF 0x7fffffff
#define ll long long

// RE 啊啊啊

const int maxn = 203, maxm = 23;
int dp[maxn][maxm][823];
int se[maxn][maxm][823];
int main() {
    int n, m;
    int d[maxn], p[maxn];
    int gap[maxn]; // 差值
    int Case = 1;  // 输出用到的序号
    while (cin >> n >> m && n && m) {
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            cin >> p[i] >> d[i];
            gap[i] = p[i] - d[i]; //
            dp[i][0][400] = 0;
        }
        dp[0][0][400] = 0; //

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= 800; k++) {
                    if (dp[i - 1][j][k] != -1) {
                        dp[i][j][k] = dp[i - 1][j][k];
                        se[i][j][k] = se[i - 1][j][k];
                    }
                    if (j > 0 && k >= gap[i] && k - gap[i] <= 800) { //
                        if (dp[i - 1][j - 1][k - gap[i]] + p[i] + d[i] >
                                dp[i][j][k] &&
                            dp[i - 1][j - 1][k - gap[i]] != -1) {
                            dp[i][j][k] =
                                dp[i - 1][j - 1][k - gap[i]] + p[i] + d[i];
                            se[i][j][k] = i;
                        }
                    }
                }
            }
        }
        int i = 400;                                                      //
        for (; dp[n][m][i] == -1 && dp[n][m][400 - (i - 400)] == -1; i++) //
            ;

        // 调试：
        // cout << i - 400 << "   " << max(dp[n][m][i], dp[n][m][400 - (i -
        // 400)]) << endl; //

        cout << "Jury #" << Case++ << " " << endl;
        ;
        int sump, sumd;
        if (dp[n][m][i] > dp[n][m][400 - (i - 400)]) {
            sump = (dp[n][m][i] + i - 400) / 2;
            sumd = dp[n][m][i] - sump;
        } else {
            sumd = (dp[n][m][i] + i - 400) / 2;
            sump = dp[n][m][i] - sumd;
        }
        cout << "Best jury has value " << sump << " for prosecution and value "
             << sumd << " for defence: " << endl;
        stack<int> sta;
        while (dp[n][m][i]) {
            sta.push(se[n][m][i]);
            i -= gap[se[n][m][i]];
            n--;
            m--;
        }
        while (!sta.empty()) {
            cout << " " << sta.top();
            sta.pop();
        }
        cout << "\n\n";
    }

    return 0;
}
