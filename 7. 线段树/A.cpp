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
    敌兵布阵 HDU - 1166
    线段树，详见 README.md
    每个结点存其对应的线段的元素和，
    本题中 update()更新操作具体为 add()加操作 和 off()减操作
    注意：maxn 不够大会超时；cin 会超时，要用 scanf ！
*/

const int maxn = 200005;
int sumv[maxn]; // 每个线段节点的最小值
int origin[maxn / 4];

// 查询：
int queryLeft, queryRight; // 需要查询最小值的闭区间
int querySum(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return sumv[o];
    }
    int mid = (left + right) >> 1;
    int ans = 0;
    if (queryLeft <= mid) {
        ans += querySum((o << 1), left, mid);
    }
    if (queryRight > mid) {
        ans += querySum((o << 1) + 1, mid + 1, right);
    }
    return ans;
}

// 建树：
void build(int l, int r, int rt) {
    if (l == r) {
        sumv[rt] = origin[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
        sumv[rt] = sumv[rt * 2] + sumv[rt * 2 + 1];
    }
}

// 更新 minv[toUpdate] = val：
int toUpdate, val;
void add(int o, int left, int right) {
    if (left == right) {
        // 叶节点
        sumv[o] += val;
    } else {
        int mid = (left + right) >> 1;
        if (toUpdate <= mid) {
            // 递归左子树
            add((o << 1), left, mid);
        } else {
            add((o << 1) + 1, mid + 1, right);
        }
        sumv[o] = sumv[(o << 1)] + sumv[(o << 1) + 1]; // 更新线段最小值
    }
}

void off(int o, int left, int right) {
    if (left == right) {
        // 叶节点
        sumv[o] -= val;
    } else {
        int mid = (left + right) >> 1;
        if (toUpdate <= mid) {
            // 递归左子树
            off((o << 1), left, mid);
        } else {
            off((o << 1) + 1, mid + 1, right);
        }
        sumv[o] = sumv[o << 1] + sumv[(o << 1) + 1];
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            // 用后半段 sumv 存数据，之后通过 build()建树操作
            scanf("%d", &origin[i]);
        }
        build(1, n, 1);

        cout << "Case " << t << ":" << endl;
        char cmd[10];
        int x, y;
        while (true) {
            scanf("%s", cmd);
            if (!strcmp(cmd, "End"))
                break;
            else if (!strcmp(cmd, "Add")) {
                scanf("%d%d", &toUpdate, &val);
                add(1, 1, n);
            } else if (!strcmp(cmd, "Sub")) {
                scanf("%d%d", &toUpdate, &val);
                off(1, 1, n);
            } else {
                scanf("%d%d", &queryLeft, &queryRight);
                cout << querySum(1, 1, n) << endl;
            }
        }
    }

    return 0;
}
