#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
typedef long long ll;

using namespace std;
const int INF = 0x3f3f3f3f;

/*
    H - Pots POJ - 3414
    bfs
*/

const int maxn = 410, maxm = 22000;

struct state {
    int a, b;
    int last;
};

vector<state> s;
bool vis[103][103];
int a, b, c;
stack<int> ans;

bool check(int i) {
    if (s[i].a == c || s[i].b == c) {
        int last = s[i].last;
        ans.push(i);
        while (last != -1) {
            ans.push(last);
            last = s[last].last; // 之前写成 s[i].last 导致死循环了
        }
        if (!ans.empty()) {
            state cur = s[ans.top()];
            ans.pop();
            cout << ans.size() << endl;
            while (!ans.empty()) {
                state nxt = s[ans.top()];
                ans.pop();
                if (nxt.a < cur.a && nxt.b == cur.b) {
                    cout << "DROP(1)" << endl;
                } else if (nxt.a == cur.a && nxt.b < cur.b) {
                    cout << "DROP(2)" << endl;
                } else if (nxt.a > cur.a && nxt.b == cur.b) {
                    cout << "FILL(1)" << endl;
                } else if (nxt.a == cur.a && nxt.b > cur.b) {
                    cout << "FILL(2)" << endl;
                } else if (nxt.a < cur.a && nxt.b > cur.b) {
                    cout << "POUR(1,2)" << endl;
                } else {
                    cout << "POUR(2,1)" << endl;
                }
                cur = nxt; // 要记得更新“上一个状态”
            }
        }
        return true;
    }
    return false;
}

int main() {
    cin >> a >> b >> c;

    s.push_back({0, 0, -1});
    vis[0][0] = true;
    for (int i = 0; i < s.size(); i++) {
        // 在每新增一步立即检查是否成功而不是在读取队列头时再检查，会加快
        state cur = s[i];
        if (s[i].a < a) {
            if (!vis[a][s[i].b]) {
                vis[a][s[i].b] = true;
                s.push_back({a, s[i].b, i});
                if (check(s.size() - 1)) {
                    return 0;
                }
            }
            if (s[i].b) {
                int t = min(a - s[i].a, s[i].b);
                if (!vis[s[i].a + t][s[i].b - t]) {
                    vis[s[i].a + t][s[i].b - t] = true;
                    s.push_back({s[i].a + t, s[i].b - t, i});
                    if (check(s.size() - 1)) {
                        return 0;
                    }
                }
            }
        }
        if (s[i].b < b) {
            if (!vis[s[i].a][b]) {
                vis[s[i].a][b] = true;
                s.push_back({s[i].a, b, i});
                if (check(s.size() - 1)) {
                    return 0;
                }
            }
            if (s[i].a) {
                int t = min(b - s[i].b, s[i].a);
                if (!vis[s[i].a - t][s[i].b + t]) {
                    vis[s[i].a - t][s[i].b + t] = true;
                    s.push_back({s[i].a - t, s[i].b + t, i});
                    if (check(s.size() - 1)) {
                        return 0;
                    }
                }
            }
        }
        if (s[i].a) {
            if (!vis[0][s[i].b]) {
                vis[0][s[i].b] = true;
                s.push_back({0, s[i].b, i});
                if (check(s.size() - 1)) {
                    return 0;
                }
            }
        }
        if (s[i].b) {
            if (!vis[s[i].a][0]) {
                vis[s[i].a][0] = true;
                s.push_back({s[i].a, 0, i});
                if (check(s.size() - 1)) {
                    return 0;
                }
            }
        }
    }

    // 不要忘记输出这个情况
    cout << "impossible" << endl;

    return 0;
}