#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;

/*
    剪花布条 HDU - 2087
    滚动哈希，当遇到相同子串时跳过 a.length-1 次，再继续判断
*/

const int maxn = 1005, maxm = 10005;

char a[maxn], b[maxn];
int m, n;

typedef unsigned long long ull;
const ull B = 100000007; // 哈希的基数，即 B
                         // 进制（我也不知道为什么取这么大，感觉 256 就够了）
int solve(char *a, char *b) {
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
    int jump = 0;
    if (ahash == bhash) {
        ans++;
        jump = alen - 1;
    }

    // 开始滚动：
    for (int i = 1; i <= blen - alen; i++) {
        bhash = bhash * B - b[i - 1] * t + b[i - 1 + alen];
        if (!jump) {
            if (ahash == bhash) {
                ans++;
                jump = alen - 1;
            }
        } else {
            jump--;
        }
    }

    return ans;
}

int main() {
    while (~scanf("%s", b) && b[0] != '#') {
        scanf("%s", a);
        n = strlen(b);
        m = strlen(a);
        cout << solve(a, b) << endl;
    }

    return 0;
}