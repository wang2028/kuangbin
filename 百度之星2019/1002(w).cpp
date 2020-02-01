#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;

const int maxn = 1003;

struct Task {
    int l, r;
};
Task tasks[maxn];
bool cmp(const Task &t1, const Task &t2) {
    if (t1.r < t2.r) {
        return true;
    } else if (t1.r == t2.r) {
        return t1.l > t2.l;
    } else {
        return false;
    }
}
int main() {
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tasks[i].l >> tasks[i].r;
        }
        sort(tasks, tasks + n, cmp);
        int ans = 0;

        int start = tasks[0].r;
        for (int i = 1; i < n; i++) {
            if (start >= tasks[i].l && start <= tasks[i].r) {
                continue;
            }
            if ((tasks[i].l - start) ^ 1) {
                // 距离为奇数
                ans += (tasks[i].l + 1 - start) / 2;
                if (tasks[i].r > tasks[i].l) {
                    start = tasks[i].l + 1;
                } else {
                    start = tasks[i].l;
                }
            } else {
                ans += (tasks[i].l - start) / 2;
                start = tasks[i].l;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
