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
    Treats for the Cows POJ - 3186
    总结：
    1. 找不到如何设置状态转移变量时，想一想什么情况下的值一定确定（也就是找到可最优的子结构）
    2. 记忆化搜索时 min() 或 max() 内要用递归函数，不要误写成 dp[i][j]
*/

const int maxn = 2005, maxm = 20005;
int dp[maxn][maxn] = {0};
int n;
bool vis[maxn][maxn] = {false};
int val[maxn];

int maxVal(int i, int j) {
    if (vis[i][j])
        return dp[i][j];
    if (i > j)
        return INF;
    vis[i][j] = true;
    int len = j - i + 1;
    int age = (n - len + 1);
    if (len == 1) {
        dp[i][j] = age * val[i];
    } else {
        dp[i][j] = max(maxVal(i + 1, j) + age * val[i],
                       maxVal(i, j - 1) + age * val[j]);
    }
    return dp[i][j];
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    cout << maxVal(0, n - 1) << endl;

    return 0;
}
