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
#define INF 0x3f3f3f3f
#define ll long long

/*
    TODO 未过 ？？？
*/

bool cmp(int a, int b) { return a > b; }
const int maxn = 1000005, maxm = 10005;
int main() {
    int n, m;
    vector<int> posSegs;
    vector<int> negSegs;
    int origin[maxn];
    while (~scanf("%d%d", &m, &n)) {
        posSegs.clear();
        negSegs.clear();
        memset(origin, 0, sizeof(origin));
        int x, curSum = 0, postive = 0;
        int posSum = 0; // 正数和
        int negCnt = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            if (x > 0) {
                posSum += x;
                postive++;
            } else if (x < 0) {
                origin[negCnt++] = x;
            }
            if (curSum == 0 || curSum * x > 0) {
                // 同符号
                curSum += x;
            } else {
                if (curSum > 0) {
                    posSegs.push_back(curSum);
                } else if (posSegs.size()) {
                    negSegs.push_back(curSum);
                }
                curSum = x;
            }
        }
        if (curSum) {
            if (curSum > 0) {
                posSegs.push_back(curSum);
            } else if (posSegs.size()) {
                negSegs.push_back(curSum);
            }
        }

        if (m >= posSegs.size()) {
            if (m <= postive) {
                cout << posSum << endl;
            } else {
                sort(origin, origin + negCnt, cmp);
                for (int i = 0; i < m - postive; i++) {
                    posSum += origin[i];
                }
                cout << posSum << endl;
            }
            continue;
        }
        sort(posSegs.begin(), posSegs.end());
        sort(negSegs.begin(), negSegs.end(), cmp);
        vector<int>::iterator posIt = posSegs.begin();
        vector<int>::iterator negIt = negSegs.begin();

        // 需要减小段数
        int maxSum[maxn];
        maxSum[posSegs.size()] = posSum;
        int t1, t2;
        for (int i = posSegs.size() - 1; i >= m; i--) {
            maxSum[i] = -INF - INF;
            // 去掉某一正数段
            t1 = maxSum[i + 1] - *posIt;
            // 将该负段与左右正段合并
            t2 = maxSum[i + 1] + *negIt;
            if (t1 > t2) {
                maxSum[i] = t1;
                posIt++;
            } else {
                maxSum[i] = t2;
                negIt++;
            }
        }
        cout << maxSum[m] << endl;
    }

    return 0;
}
