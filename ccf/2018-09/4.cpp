#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;

/*
    直接暴力dfs，80分，据说加上记忆化可100分。
*/

const int maxn = 305, maxm = 1000005;

int n;
int two[maxn], one[maxn];

bool dfs(int t) {
    if (t == 0) {
        for (int i = 1; i < 2 * two[t]; i++) {
            one[t] = i;
            one[t + 1] = 2 * two[t] - i;
            if (dfs(t + 1))
                return true;
            one[t + 1] = 2 * two[t] - i + 1;
            if (dfs(t + 1))
                return true;
        }
        one[t] = 2 * two[t];
        one[t + 1] = 1;
        return dfs(t + 1);
    } else if (t == n - 1) {
        return (one[t - 1] + one[t]) / 2 == two[t];
    } else {
        one[t + 1] = two[t] * 3 - one[t] - one[t - 1];
        if (one[t + 1] > 0) {
            if (dfs(t + 1))
                return true;
        }
        one[t + 1] = two[t] * 3 - one[t] - one[t - 1] + 1;
        if (one[t + 1] > 0) {
            if (dfs(t + 1))
                return true;
        }
        one[t + 1] = two[t] * 3 - one[t] - one[t - 1] + 2;
        if (one[t + 1] > 0) {
            if (dfs(t + 1))
                return true;
        }
    }
    return false;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> two[i];
    }
    // 注意 n==2 的情况
    if (dfs(0)) {
        for (int i = 0; i < n; i++) {
            cout << one[i] << " ";
        }
    }

    return 0;
}