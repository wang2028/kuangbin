#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
typedef long long ll;

using namespace std;

const int maxt = 100003;
const ll maxn = 1e12 + 3;
int res[maxn];
bool ok[maxn];

ll solve(ll n) {
    if (ok[n]) {
        return res[n];
    }
    ll ans = 0;
    for (ll i = 1; i < n; i++) {
        ans += solve(i);
    }
    ok[n] = true;
    res[n] = ans;
    return ans;
}

int main() {
    int T;
    ll n;
    scanf("%d", &T);
    memset(ok, false, sizeof(ok));
    ok[1] = ok[2] = true;
    res[1] = res[2] = 1;
    while (T--) {
        scanf("%lld", &n);
        cout << solve(n) << endl;
    }

    return 0;
}
