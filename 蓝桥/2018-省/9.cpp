#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

/*
    复杂度：n+k(n/k)log(n/k)+(k^2)/6 约1e6
*/

const int maxk = 1001;
vector<int> mod[maxk];

bool cmp(int a, int b) { return a > b; }

int main() {
    int n, k;
    cin >> n >> k;
    int t;
    for (int i = 0; i < n; i++) {
        cin >> t;
        mod[t % k].push_back(t);
    }
    for (int i = 0; i < k; i++) {
        sort(mod[i].begin(), mod[i].end(), cmp);
    }
    int ans = 0;
    int cur[maxk];
    for (int i = 0; i <= k / 3; i++) {
        if (!mod[i].size()) {
            continue;
        }
        memset(cur, 0, sizeof(int) * k);
        cur[i]++;
        for (int j = i; j <= k / 2; j++) {
            if (mod[j].size() <= cur[j]) {
                continue;
            }
            cur[j]++;
            if ((k - i - j) % k >= j) {
                if (mod[(k - i - j) % k].size() <= cur[(k - i - j) % k]) {
                    continue;
                }
                ans = max(ans, (mod[i][cur[i] - 1] + mod[j][cur[j] - 1] +
                                mod[(k - i - j) % k][cur[(k - i - j) % k]]));
            } else {
                break;
            }
        }
    }
    cout << ans << endl;

    return 0;
}

/*

7
.......
.##....
.##....
....##.
..####.
...###.
.......


*/