#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

// HDU 1043、POJ 1077 Eight

// 真的难啊...暴力广搜+STL各种超时溢出...
// 需要哈希（康托展开）+打表才能过 hdu...
// 以下仅是自写的康托展开的模板...

const int Digit = 5;
int F[Digit]; // 0 ~ Digit-1 阶乘
const char base[Digit] = {'1', '2', '3', '4', '5'};
void getArr(int val, char *t) {
    bool vis[Digit];
    memset(vis, 0, sizeof(vis));
    int lessThan;
    for (int i = 0; i < Digit; i++) {
        lessThan = val / F[Digit - 1 - i];
        val %= F[Digit - 1 - i];

        int num = 0;
        for (int j = 0; j < Digit; j++) {
            if (!vis[j]) {
                num++;
            }
            if (num == lessThan + 1) {
                t[i] = base[j];
                vis[j] = true;
                break;
            }
        }
    }
}

int getNum(char *t) {
    int res = 0;
    for (int i = 0; i < Digit; i++) {
        for (int j = i + 1; j < Digit; j++) {
            if (t[j] < t[i]) {
                res += F[Digit - i - 1];
            }
        }
    }
    return res;
}

int main() {
    F[0] = 1;
    for (int i = 1; i < Digit; i++) {
        F[i] = F[i - 1] * i;
    }
   




    return 0;
}
