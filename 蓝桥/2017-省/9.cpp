#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;

// 超时，正确做法应该用二分优化枚举

const int maxn = 100005;
int hei[maxn], wid[maxn];

typedef struct {
    int hei, wid;
} Cho;
Cho;

bool operator<(const Cho &c1, const Cho &c2) { return c1.hei < c2.hei; }

int main() {
    int n, k;
    cin >> n >> k;
    int t1, t2;
    priority_queue<Cho> pq;
    for (int i = 0; i < n; i++) {
        // nlogn
        cin >> t1 >> t2;
        if (t1 > t2) {
            pq.push({t2, t1});
        } else {
            pq.push({t1, t2});
        }
    }
    for (int len = pq.top().hei; len >= 1; len--) {
        priority_queue<Cho> pq1 = pq;
        int cnt = k;
        Cho cho;
        while (pq1.top().hei >= len) {
            cho = pq1.top();
            pq1.pop();
            cnt--;
            if (!cnt) {
                cout << len << endl;
                return 0;
            }
            pq1.push({min(cho.hei - len, len), max(cho.hei - len, len)});
            pq1.push({min(cho.wid - len, len), max(cho.wid - len, len)});
            pq1.push({cho.wid - len, cho.hei - len});
        }
    }
    cout << "INF" << endl;

    return 0;
}
