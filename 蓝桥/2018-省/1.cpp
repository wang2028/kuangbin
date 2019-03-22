#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;

const int maxn = 101;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int mu = pow(2, 19);
    int ans = 0;
    for (int i = 0; i <= 19; i++) {
        ans += pow(2, i);
    }
    int g;
    do {
        g = gcd(mu, ans);
        mu /= g;
        ans /= g;
    } while (g != 1);

    cout << mu << endl;
    cout << ans << endl;

    return 0;
}
