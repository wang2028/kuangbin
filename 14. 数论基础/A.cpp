#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
typedef long long ll;

using namespace std;
/*
    A - Bi-shoe and Phi-shoe LightOJ - 1370
    小于 n 且与 n 互质的数的个数称为 n 的欧拉函数 φ(n)，
    有性质，对于质数 p，φ(p) = p-1
    因此此题对每个人，求大于其幸运数字的最小质数即可。
    找素数用素数筛；并且注意用 long long 而不是 int。
*/

const ll maxn = 1000010;
bool isPrime[maxn];

void ei() {
    for (ll i = 0; i < maxn; i++) {
        isPrime[i] = true;
    }
    for (ll i = 2; i < maxn; i++) {
        if (isPrime[i]) {
            for (ll j = i * i; j < maxn; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    ei();
    ll T;
    cin >> T;
    ll n;
    for (ll kase = 0; kase < T; kase++) {
        cin >> n;
        ll t, ans = 0;
        for (ll i = 0; i < n; i++) {
            cin >> t;
            for (ll j = t + 1; j < maxn; j++) {
                if (isPrime[j]) {
                    ans += j;
                    break;
                }
            }
        }
        cout << "Case " << (kase + 1) << ": " << ans << " Xukha\n";
    }

    return 0;
}
