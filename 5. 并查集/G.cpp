#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

const int maxn = 10005, maxm = 1003;

/*
    G - Supermarket POJ - 1456

    该题难点在于需要同时实现：
        1. 价格从高到低的排序（要能遍历的那种）；
        2. 将截止日期同天的归为一组（要统一管理）；
        3. 在第 i 天卖了某种截止日期为 i 的产品 x，其他原截止为 i 的产品 x' 应该
            将截止改为 i-1，不过若原截止为 i-1 的产品在之前已经改为 i-n 了，
            那么 x' 的截止也应该递归改为 i-n 而不是 i-1。
    要满足第 1 点，肯定要放到数组中，满足第 2、3 点，应放到并查集中，
    通过将截止日期 t 的根结点（或间接根结点）不断改为 t-1, t-2, ...
    以此来实现满足每天只能卖一种产品的同时，可以将截止靠后的产品放入靠前的日期，
    一并根据价格从高到低确定先卖谁，因为若有一 (90,2) 的卖掉了，
    所有截止日期为 2 的根结点都变为 2-1=1 了，
    因此除了被卖掉的其他产品可以同截止日期为 1 天的一并比较。
    因为最开始根据价格从高到低排序了，所以直接遍历一遍，遍历时更新截止日期即可。

    注意：不能先卖过期早的，再卖过期晚的，因为可能过期晚的利润更大，过期早的没必要卖了；
    有点贪心的思想；
*/

int fa[maxn];

int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = find(fa[x]);
}

struct Thing {
    int p, d;
} thing[maxn];
bool cmp(Thing t1, Thing t2) { return t1.p > t2.p; }

int main() {
    int n;
    while (cin >> n) {
        int maxd = 0; // 用来获取最大日期，以节省初始化 fa[] 时间
        for (int i = 0; i < n; i++) {
            cin >> thing[i].p >> thing[i].d;
            maxd = max(maxd, thing[i].d);
            // 不能只对出现的日期初始化 fa
            // 因为可能在日期减过之后根植变为 0 了
            // 比如 fa[6] = 6，在卖掉该截止日期为 6 的产品后，
            // fa[6] = 6-1 = 5，但因为没有原截止为 5 的产品，
            // 所以此时 fa[5] = 0，
            // 所以在 find(6) 之后 fa[6] 直接为 0 了！
            // fa[thing[i].d] = thing[i].d;
            // 当然，也可以初始化 fa[] 为 -1，在 fa[i]==-1 时返回 i 即可
        }
        for (int i = 0; i <= maxd; i++) {
            fa[i] = i;
        }
        sort(thing, thing + n, cmp);
        int ans = 0, p;
        for (int i = 0; i < n; i++) {
            p = find(thing[i].d);
            if (p > 0) {
                ans += thing[i].p;
                fa[p] = p - 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}