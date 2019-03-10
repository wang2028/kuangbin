#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

/*
    Tickets HDU - 1260
    将每个人 i 看做当前第 i 阶段，每个阶段中：
    若前人选双人票，此时该人只能选单人票，
    若前人选单人票，此时单双均可选。
*/

const int maxn = 2003, maxm = 100005;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int peo;
        cin >> peo;
        int cost[maxn];
        for (int i = 0; i < peo; i++) {
            cin >> cost[i];
        }
        int adjCost[maxn];
        for (int i = 0; i < peo - 1; i++) {
            cin >> adjCost[i]; // 第 i 和 i+1 个人一起买的时间
        }

        int d[maxn][2];
        d[0][0] = cost[0];
        d[0][1] = adjCost[0];
        for (int i = 1; i < peo; i++) {
            d[i][0] = d[i][1] = INF;
            d[i][0] = min(d[i - 1][1], d[i - 1][0] + cost[i]);
            d[i][1] = min(d[i][1], d[i - 1][0] + adjCost[i]);
        }

        int ans = d[peo - 1][0];

        // 将秒数 ans 转为时间：
        int hh = ans / 3600 + 8;
        ans %= 3600;
        int mm = ans / 60;
        ans %= 60;
        int ss = ans;
        string out;
        if (hh > 12) {
            out = "pm";
            hh = hh - 12;
        } else {
            out = "am";
        }
        if (hh < 10) {
            cout << "0";
        }
        cout << hh << ":";
        if (mm < 10) {
            cout << "0";
        }
        cout << mm << ":";
        if (ss < 10) {
            cout << "0";
        }
        cout << ss << " " << out << endl;
    }

    return 0;
}
