#include <algorithm>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

/*
    POJ 3268 Silver Cow Party
    Floyd
*/

const int maxn = 1005;
int n = 0;
int d[maxn][maxn];

void floyd() {
    // 初始化：
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if(i == k){
                continue;
            }
            for (int j = 0; j < n; j++) {
                if(i == j || j == k){
                    continue;
                }
                if (d[i][k] < INF && d[k][j] < INF) {
                    // 避免两个初始 INF 相加后的和超过 INF，所以判断一下
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
}

int main() {
    int m, tar; // 路、终点
    cin >> n >> m >> tar;
    tar--; // 统一从 0 开始
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = INF;
        }
    }
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        d[u - 1][v - 1] = w;
    }
    floyd();
    int maxtime = 0;
    for (int i = 0; i < n; i++) {
        maxtime = max(maxtime, d[i][tar] + d[tar][i]);
    }
    cout << maxtime << endl;

    return 0;
}
