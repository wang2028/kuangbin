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

int mon2day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool run(int y) {
    if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0) {
        return true;
    }
    return false;
}

struct date {
    int y, m, d;
    int w;
    void operator--() {
        if (w > 1) {
            w--;
        } else {
            w = 7;
        }
        if (d > 1) {
            d--;
            return;
        }
        if (m > 1) {
            m--;
            if (run(m) && m == 2) {
                d = mon2day[m] + 1;
            } else {
                d = mon2day[m];
            }
            return;
        }
        y--;
        m = 12;
        d = 31;
    }
};

int main() {
    // 2019.3.18 周一
    struct date dt = {2019, 3, 18, 1};
    int ans = 0;
    bool start = false;
    while (true) {
        --dt;
        if (dt.y == 2000 && dt.m == 12 && dt.d == 31) {
            start = true;
        }
        if (start && dt.w == 1) {
            ans++;
        }
        if (dt.y == 1901 && dt.m == 1 && dt.d == 1) {
            break;
        }
    }
    cout << ans << endl;

    return 0;
}
