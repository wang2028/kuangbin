#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 不知道到底对不对...

const int INF = 0x3f3f3f3f;
const int maxn = 1003, maxm = 6;

int m[maxn][maxn];
bool vis[maxn][maxn];
string s;
int minNeed(int i, int j) {
    if (vis[i][j]) {
        return m[i][j];
    }
    if (i >= j) {
        return 0;
    }
    vis[i][j] = true;
    if (s[i] == s[j]) {
        return m[i][j] = minNeed(i + 1, j - 1);
    } else {
        return m[i][j] = min(minNeed(i + 1, j), minNeed(i, j - 1)) + 1;
    }
}

int main() {
    cin >> s;
    int i = 0, j = s.length() - 1;
    cout << minNeed(i, j) << endl;

    return 0;
}