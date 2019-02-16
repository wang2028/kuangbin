#include <cstring>
#include <iostream>
#include <set>
#include <string>
using namespace std;
#define INF 0x3f3f3f3f

// HDU 2181 哈密顿绕行世界问题

// 直接深搜（回溯），用 vis[] 数组记录每条路线中已经过的点，
// 将每次搜索的路线（序号 0~19 转为 char 型）存入字符串 path，
// 每次搜索得到结果时将 path 插入集合 paths，以获得字典序排列，便于最终输出。
// 没想到直接回溯竟然过了...

string path; // 因为最大为 20，所以用 char 存成字符串即可，便于字典序输出
set<string> paths;
int adj[20][3];
bool vis[20];
int start;

void back(int t) {
    if (path.length() == 21) {
        if (path[path.length() - 1] == start) {
            paths.insert(path);
        }
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (!vis[adj[t][i]]) {
            vis[adj[t][i]] = true;
            path += adj[t][i];
            back(adj[t][i]);
            vis[adj[t][i]] = false;
            path.erase(path.length() - 1);
        }
    }
}

int main() {
    memset(adj, 0, sizeof(adj));
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> adj[i][j];
            adj[i][j]--; // 题目序号为 1~20，存储时统一转为 0~19
        }
    }

    while (cin >> start) {
        if (start == 0)
            break;
        path.clear();
        paths.clear();
        memset(vis, 0, sizeof(vis));
        start--; // 题目序号为 1~20，存储时统一转为 0~19
        path += start;
        back(start);

        int cnt = 1;
        for (set<string>::iterator i = paths.begin(); i != paths.end(); i++) {
            path = *i;
            cout << cnt++ << ": ";
            for (int j = 0; j < path.length(); j++) {
                start = path[j];
                start++;
                cout << " " << start;
            }
            cout << "\n";
        }
    }

    return 0;
}
