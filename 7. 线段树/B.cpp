#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    I Hate It HDU - 1754
    直接套模板，把模板中求 min 改为求 max 即可，模板见 README.md
*/

const int maxn = 800009;
int maxv[maxn];
int origin[maxn / 4];

// 建树：
void build(int o, int l, int r) {
    if (l == r) {
        maxv[o] = origin[l];
    } else {
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        maxv[o] = max(maxv[o * 2], maxv[o * 2 + 1]);
    }
}

// 查询：
int queryLeft, queryRight; // 需要查询最小值的闭区间
int query(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return maxv[o];
    }
    int mid = left + (right - left) / 2; // 取中点
    int ans = 0; // 其他最大值最小值题目记得改这里
    if (queryLeft <= mid) {
        ans = max(ans, query(o * 2, left, mid));
    }
    if (queryRight > mid) {
        ans = max(ans, query(o * 2 + 1, mid + 1, right));
    }
    return ans;
}

// 更新 minv[toUpdate] = val：
int toUpdate, val;
void update(int o, int left, int right) {
    // 因为是二叉树，所以当根线段元素数量确定时所有点在数组中的位置都确定了
    // 因此先递归找到叶节点，并更新
    // 同时更新该递归路径上每个非叶节点的值（最小值）
    // 复杂度为 logn
    if (left == right) {
        // 叶节点
        maxv[o] = val;
    } else {
        int mid = left + (right - left) / 2; // 取中点
        if (toUpdate <= mid) {
            // 递归左子树
            update(o * 2, left, mid);
        } else {
            update(o * 2 + 1, mid + 1, right);
        }
        maxv[o] = max(maxv[o * 2], maxv[o * 2 + 1]); // 更新线段最小值
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &origin[i]);
        }
        build(1, 1, n);
        char cmd[5];
        int t1, t2;
        while (m--) {
            scanf("%s", cmd);
            if (!strcmp(cmd, "Q")) {
                scanf("%d%d", &queryLeft, &queryRight);
                cout << query(1, 1, n) << endl;
            } else {
                scanf("%d%d", &toUpdate, &val);
                update(1, 1, n);
            }
        }
    }

    return 0;
}
