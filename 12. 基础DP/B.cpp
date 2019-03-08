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
#define INF 9999
#define ll long long

/*
    B - Ignatius and the Princess IV HDU - 1029
    测试也太水了吧...别说DP了，连STL都没用上...
    直接开一个数组，每次读一个 t 直接把 arr[t] 加 1，
    然后判断 arr[t] 是不是大于 (n+1)/2 就行了
*/

const int maxn = 105, maxm = 10005;
int main() {
    int n;
    while (cin >> n) {
        int pos[INF] = {0};
        int least = (n + 1) / 2;
        int t, ans;
        for (int i = 0; i < n; i++) {
            cin >> t;
            pos[t]++;
            if (pos[t] >= least) {
                ans = t;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
