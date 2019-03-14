#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

const int maxn = 1005;

typedef struct {
    int key, time;
    int type; // 0 拿走，1 还回
} Event;
Event events[maxn * 2]; // 要细心，一次拿走还回是 2 个事件，需要乘 2
bool cmp(Event e1, Event e2) {
    if (e1.time != e2.time) {
        return e1.time < e2.time;
    } else if (e1.type != e2.type) {
        return e1.type > e2.type;
    } else {
        return e1.key < e2.key;
    }
}
int main() {
    int n, k;
    cin >> n >> k;
    int key, start, keep;
    for (int i = 0; i < k; i++) {
        cin >> key >> start >> keep;
        events[i * 2].key = key;
        events[i * 2].time = start;
        events[i * 2].type = 0;
        events[i * 2 + 1].key = key;
        events[i * 2 + 1].time = start + keep;
        events[i * 2 + 1].type = 1;
    }
    sort(events, events + k * 2, cmp);
    int keys[maxn];
    for (int i = 1; i <= n; i++) {
        keys[i] = i;
    }
    for (int i = 0; i < k * 2; i++) {
        Event e = events[i];
        if (e.type == 0) {
            for (int j = 1; j <= n; j++) {
                if (keys[j] == e.key) {
                    keys[j] = -1;
                    break; // 要细心，处理完要 break
                }
            }
        } else {
            for (int j = 1; j <= n; j++) {
                if (keys[j] == -1) {
                    keys[j] = e.key;
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << keys[i] << " ";
    }

    return 0;
}