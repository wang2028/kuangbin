#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;

// 肯定超时啊啊啊

const int maxn = 5, maxm = 6;

int main() {
    int n;
    cin >> n;
    for (int i = 0, mx1 = ceil(sqrt(n)); i <= mx1; i++) {
        int e1 = n - i * i;
        for (int j = 0, mx2 = ceil(sqrt(e1)); j <= mx2; j++) {
            int e2 = e1 - j * j;
            for (int k = 0, mx3 = ceil(sqrt(e2)); k <= mx3; k++) {
                int e3 = e2 - k * k;
                int e33 = ceil(sqrt(e3));
                if (e33 * e33 == e3) {
                    cout << i << " " << j << " " << k << " " << e33 << endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}