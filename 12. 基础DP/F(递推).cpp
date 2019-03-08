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
    F - Piggy-Bank HDU - 1114 
    直接二维递推一遍即可。。。
    有时候脑子糊涂了...咋都想不出来...
*/

const int maxn = 505, maxm = 10005;

struct Coin {
    int val, wei;
} coin[maxn];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int d[maxm];
        int n, all;

        int emp, full;
        cin >> emp >> full;
        all = full - emp;
        int val, wei;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> coin[i].val >> coin[i].wei;
        }
        for (int i = 0; i <= maxm; i++) {
            d[i] = INF;
        }
        d[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = coin[i].wei; j <= all; j++) {
                d[j] = min(d[j], d[j - coin[i].wei] + coin[i].val);
            }
        }
        if (d[all] == INF) {
            cout << "This is impossible." << endl;
        } else {
            cout << "The minimum amount of money in the piggy-bank is "
                 << d[all] << "." << endl;
        }
    }

    return 0;
}
