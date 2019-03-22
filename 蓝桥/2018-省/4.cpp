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

set<ll> s;
int main() {
    int base[3] = {3, 5, 7};
    int cnt = 0;
    s.insert(1);
    ll cur = 0;
    while (cur != 59084709587505) {
        cur = *s.begin();
        for (int i = 0; i < 3; i++) {
            s.insert(cur * base[i]);
        }
        cnt++;
        s.erase(s.begin());
    }
    cout << --cnt << endl;

    return 0;
}
