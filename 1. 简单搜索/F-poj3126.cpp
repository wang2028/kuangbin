#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

// POJ 3126 Prime Path

// 即判断素数+bfs，题目时限要求较水，以下代码可以较大程度的优化

const int MAX = 10001;
bool isPrime[MAX];
bool vis[MAX];

typedef struct {
    int v[4]; // 0~3 从左到右
    int m;    // 花的钱
} Node;

void checkPrime() {
    // 筛出素数，可优化
    memset(isPrime, 0, sizeof(isPrime));
    int j;
    for (int i = 1000; i < MAX; i++) {
        for (j = 3; j < i / 2; j += 2) {
            if (i % j == 0) {
                break;
            }
        }
        if (i % 2 != 0 && j >= i / 2) {
            isPrime[i] = true;
        }
    }
}

int assemble(int a[4]) { return a[0] * 1000 + a[1] * 100 + a[2] * 10 + a[3]; }

int bfs(int from, int to) {
    if (from == to) {
        return 0;
    }
    memset(vis, 0, sizeof(vis));
    queue<Node> q;
    Node tempn;
    tempn.m = 0;
    tempn.v[0] = from / 1000;
    tempn.v[1] = from % 1000 / 100;
    tempn.v[2] = from % 100 / 10;
    tempn.v[3] = from % 10;
    q.push(tempn);
    vis[from] = true;

    int tempi;
    while (!q.empty()) {
        for (int i = 0; i <= 3; i++) {
            for (int j = 0; j <= 9; j++) {
                tempn = q.front();
                if (i == 0 && j == 0)
                    continue;
                if (tempn.v[i] != j) {
                    tempn.v[i] = j;
                    tempi = assemble(tempn.v);
                    if (tempi == to) {
                        return q.front().m + 1;
                    }
                    if (isPrime[tempi] && !vis[tempi]) {
                        vis[tempi] = true;
                        tempn.m++;
                        q.push(tempn);
                    }
                }
            }
        }
        q.pop();
    }
    return -1;
}

int main() {
    int n;
    cin >> n;
    int from, to;
    int m;
    checkPrime();
    for (int i = 0; i < n; i++) {
        cin >> from >> to;
        m = bfs(from, to);
        if (m == -1) {
            cout << "Impossible" << endl;
        } else {
            cout << m << endl;
        }
    }

    return 0;
}