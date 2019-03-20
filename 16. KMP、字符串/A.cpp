#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Number Sequence HDU - 1711
    滚动哈希模板题
*/

const int INF = 0x3f3f3f3f;
const int maxn = 1000005, maxm = 6;

int a[maxn], b[maxn];
int n, m;

typedef unsigned long long ull;
const ull B = 100000007; // 哈希的基数，即 B
                         // 进制（我也不知道为什么取这么大，感觉 256 就够了）
int solve(int *a, int *b) {
    // 判断 a 是否在 b 中，返回出现次数
    int ans = 0;

    int alen = m, blen = n;
    if (alen > blen)
        return false;

    ull t = 1; // 移动位置后最高位的权值
    for (int i = 0; i < m; i++) {
        t *= B;
    }

    // 计算 a 的哈希、 b 的初始 a 位子字符串的哈希：
    ull ahash = 0, bhash = 0;
    for (int i = 0; i < alen; i++) {
        ahash = ahash * B + a[i];
        bhash = bhash * B + b[i];
    }
    if (ahash == bhash)
        return 0;

    // 开始滚动：
    for (int i = 1; i <= blen - alen; i++) {
        bhash = bhash * B - b[i - 1] * t + b[i - 1 + alen];
        if (ahash == bhash)
            return i;
    }

    return -2;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &b[i]);
        }
        printf("%d\n", solve(b, a) + 1);
    }

    return 0;
}