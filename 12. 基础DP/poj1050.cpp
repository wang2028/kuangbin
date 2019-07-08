#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int INF = 0x3f3f3f3f;

/*
    最大子矩阵和；
    预处理 O(n^2)：先对每行求前缀和，
    这样每行的每一连续段就可以 O(1) 的求出，因此可看作是一个元素，
    再对列枚举 i、j，在第 i 和 j 列之间，跑一维的最大字段和，
    总复杂度 O(n^3)
*/

const int maxn = 103, maxw = 10005;

int arr[maxn][maxn];
int preSum[maxn][maxn]; // 每行的前缀和

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            preSum[i][j] = (j > 0 ? preSum[i][j - 1] : 0) + arr[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // 在第 i 列到第 j 列上，将每行看做一个元素，跑一维大最大字段和
            int sum = 0;
            for (int k = 0; k < n; k++) {
                if (sum < 0) {
                    sum = preSum[k][j] - (i > 0 ? preSum[k][i - 1] : 0);
                } else {
                    sum += preSum[k][j] - (i > 0 ? preSum[k][i - 1] : 0);
                }
                ans = max(ans, sum);
            }
        }
    }
    cout << ans << endl;

    return 0;
}

/*
4
0 -2 -7 0
9 2 -6 2
-4 1 -4  1
-1 8  0 -2
*/