#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// POJ 3278 Catch That Cow

// 思想：广搜，每次搜索即三种情况（+1 -1 *2）

// 在提交后多次出现 Runtime Error，
// 之后发现错误为使用了 reached 数组来记录某点是否到达过，以剪枝，
// 但出现了漏判数组越界的问题（即当前所在位置小于0 或 大于上限）。

typedef struct {
    int d; // 当前位置
    int t; // 到达当前位置所用时间
} Status;

int main() {
    const int LIMIT = 100005;
    int fj = 0, cow = 0;           // 农民位置，奶牛位置
    int minT;                      // 最短时间
    bool reached[LIMIT] = {false}; // 记录某点是否到达过，以剪枝
    Status temps;                  // 临时变量
    int tempd;                     // 临时变量

    cin >> fj >> cow;
    minT = abs(cow - fj);

    queue<Status> q;
    q.push({fj, 0});
    reached[fj] = true;

    // 以下代码中很多判断条件都是为了剪枝
    while (!q.empty()) {
        temps = q.front();
        q.pop();

        if (temps.t >= minT - 1 || temps.d < 0)
            continue;

        if (temps.d > cow) {
            // 当前位置大于奶牛位置时只可能 -1
            tempd = temps.d - 1;
            if (tempd >= 0 && !reached[tempd]) {
                reached[tempd] = true;
                if (tempd == cow) {
                    if (temps.t + 1 < minT) {
                        minT = temps.t + 1;
                    }
                } else {
                    q.push({tempd, temps.t + 1});
                }
            }
        } else {
            tempd = temps.d * 2;
            if (tempd < LIMIT && !reached[tempd]) {
                reached[tempd] = true;
                if (tempd == cow) {
                    if (temps.t + 1 < minT) {
                        minT = temps.t + 1;
                    }
                } else {
                    q.push({tempd, temps.t + 1});
                }
            }
            tempd = temps.d - 1;
            if (tempd >= 0 && !reached[tempd]) {
                reached[tempd] = true;
                if (tempd == cow) {
                    if (temps.t + 1 < minT) {
                        minT = temps.t + 1;
                    }
                } else {
                    q.push({tempd, temps.t + 1});
                }
            }
            tempd = temps.d + 1;
            if (tempd < LIMIT && !reached[tempd]) {
                reached[tempd] = true;
                if (tempd == cow) {
                    if (temps.t + 1 < minT) {
                        minT = temps.t + 1;
                    }
                } else {
                    q.push({tempd, temps.t + 1});
                }
            }
        }
    }

    cout << minT;

    return 0;
}