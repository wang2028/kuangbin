#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;

const int maxn = 1003;

int gcd(int a, int b) {
    if (!b) {
        return a;
    }
    return gcd(b, a % b);
}

int f[maxn], g[maxn];
int main() {
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> f[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> g[i];
        }
        bool ok = false;
        for (int i = n - 1; i >= 0; i--) {
            if (f[i] == 0 && g[i] != 0) {
                cout << "0/1" << endl;
                break;
            } else if (f[i] != 0 && g[i] == 0) {
                cout << "1/0" << endl;
                break;
            } else if (f[i] != 0 && g[i] != 0) {
                int gg = gcd(f[i], g[i]);
                cout << (f[i] / gg) << "/" << (g[i] / gg) << endl;
                break;
            }
        }
    }

    return 0;
}
