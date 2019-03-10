#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    L - Common Subsequence POJ - 1458
*/

const int maxn = 1500;

int main() {
    string s1, s2;
    int dp[maxn][maxn];
    while (cin >> s1 >> s2) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < s1.length(); i++) {
            for (int j = 0; j < s2.length(); j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = s1[0] == s2[0] ? 1 : 0;
                } else {
                    if (s1[i] == s2[j]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                        // 数组访问到负索引时为负无穷，而不会报越界错误
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
        }
        cout << dp[s1.length() - 1][s2.length() - 1] << endl;
    }

    return 0;
}
