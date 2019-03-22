#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f;

const ll maxn = 101;

int main() {
    ll tmp = 1;
    ll n;
    ll ans = 0;
    for (int i = 0; i < 100; i++) {
        cin >> n;
        tmp *= n;
        if (tmp < 0) {
            cout << "error" << endl;
        }
        while (tmp % 10 == 0 && tmp) {
            cout << tmp << endl;
            ans++;
            tmp /= 10;
        }
        ll base = 1;
        ll t = 0;
        while ((tmp % 2 == 0 || tmp % 5 == 0) && tmp) {
            if (tmp % 5 == 0) {
                t += base * 5;
                base *= 10;
            } else {
                t += base * 2;
                base *= 10;
            }
            tmp /= 10;
        }
        tmp = t;
    }
    while (tmp % 10 == 0 && tmp) {
        ans++;
        tmp /= 10;
    }
    cout << ans << endl;

    return 0;
}
