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
    Doing Homework HDU - 1074
    所谓的状压DP，其实就是利用二进制表示集合，
    求出每个状态最小的扣分，
    状态转移方法：假设3道题，3题全做完时状态为 111，
    前一状态必定是 011、110、101 中的一个，
    所以状态 s 从 0 遍历到 (1<<n)-1，
    每一次转移时遍历 s 当前所有题目，取其中一道作为现状态新做题目 i，
    计算 i 的花费 t 与上一状态已经花费 t' 天数之和 sum
    是否大于 i 的截止日期，超过截止日期的部分加到 dp[s] 中，
    经过遍历 i，取最小的 dp[s]，同时记录此时的 i，用于最后输出
*/

const int maxn = 16, maxm = 10005;

typedef struct {
    int ddl, cost;
    string name;
} Job;

int main() {
    Job job[maxn];
    int T;
    cin >> T;
    int n;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> job[i].name >> job[i].ddl >> job[i].cost;
        }
        int d[(1 << maxn)];
        int past[(1 << maxn)];
        int fa[(1 << maxn)];
        past[0] = 0;
        d[0] = 0;
        fa[0] = -1;
        for (int s = 1; s < (1 << n); s++) {
            d[s] = INF;
            for (int i = n - 1; i >= 0; i--) {
                if (s & (1 << i)) {
                    int newD = 0;
                    int t = past[s ^ (1 << i)] + job[i].cost;
                    if (t > job[i].ddl) {
                        newD += t - job[i].ddl;
                    }
                    newD += d[s ^ (1 << i)];
                    if (d[s] > newD) {
                        d[s] = newD;
                        fa[s] = i;
                        past[s] = t;
                    }
                }
            }
        }
        cout << d[(1 << n) - 1] << endl;
        stack<string> sta;
        for (int s = (1 << n) - 1; s > 0; s ^= (1 << fa[s])) {
            sta.push(job[fa[s]].name);
        }
        while (!sta.empty()) {
            cout << sta.top() << endl;
            sta.pop();
        }
    }

    return 0;
}
