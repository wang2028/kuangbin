#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;

const int maxn = 36;
int G[maxn];

bool check() {
    bool ok = false;
    for (int i = 0; i < 6; i++) {
        if (G[i] || G[i * 6]) {
            ok = true;
            break;
        }
    }
    if (!ok) {
        return false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < maxn; j++) {
            if (G[i * 6 + j] + G[(5 - i) * 6 + (5 - j)] != 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    for (int i = 0; i < 18; i++) {
        G[i] = 0;
    }
    for (int i = 18; i < maxn; i++) {
        G[i] = 1;
    }
    int ans = 0;
    do {
        if (check()) {
            ans++;
        }
    } while (next_permutation(G, G + maxn));
    cout << ans << endl;

    return 0;
}
