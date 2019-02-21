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
#define ll long long

/*
    A Simple Problem with Integers POJ - 3468
    区间修改的线段树（详见 README.md）
    注意：线段和sumv 以及 标记mark 因为存在累加操作，所以需要 long long 类型
*/

const int maxn = 400009; // 同上“点修改”
ll sumv[maxn];           // 每个节点保存的线段最小值
ll mark[maxn];
int origin[maxn / 4]; // 读入的原始数据，建树操作需要

// 建树：
void build(int o, int l, int r) {
    mark[o] = 0;
    if (l == r) {
        sumv[o] = origin[l];
    } else {
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
}

// 延迟更新标记向子树传递：
void markDown(int o, int left, int right) {
    if (mark[o]) {
        // 设置左右孩子节点的标志域，
        // 因为孩子节点可能被多次延迟标记又没有向下传递，所以是 “+=” ！！
        mark[o * 2] += mark[o];
        mark[o * 2 + 1] += mark[o];
        sumv[o * 2] += mark[o] * ((right + left) / 2 - left + 1);
        sumv[o * 2 + 1] += mark[o] * (right - (right + left) / 2);
        mark[o] = 0; // 向下传递后清空该根结点的标记
    }
}

// 查询：
int queryLeft, queryRight; // 需要查询最小值的闭区间
ll querySum(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return sumv[o];
    }
    markDown(o, left, right);
    int mid = (right + left) / 2; // 取中点
    ll ans = 0;
    if (queryLeft <= mid) {
        ans += querySum(o * 2, left, mid);
    }
    if (queryRight > mid) {
        ans += querySum(o * 2 + 1, mid + 1, right);
    }
    return ans;
}

// 更新 minv[toUpdate] = val：
int toUpdateLeft, toUpdateRight, val;
void update(int o, int left, int right) {
    // 以增加值为例：

    if (left >= toUpdateLeft && right <= toUpdateRight) {
        // 叶节点
        sumv[o] += val * (right - left + 1);
        mark[o] += val;
    } else {
        markDown(o, left, right);
        int mid = left + (right - left) / 2; // 取中点
        if (toUpdateLeft <= mid) {
            // 递归左子树
            update(o * 2, left, mid);
        }
        if (toUpdateRight > mid) {
            // 递归右子树
            update(o * 2 + 1, mid + 1, right);
        }
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
}
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &origin[i]);
    }
    build(1, 1, n);

    char cmd[5];
    for (int i = 0; i < q; i++) {
        scanf("%s", cmd);
        if (!strcmp(cmd, "Q")) {
            scanf("%d%d", &queryLeft, &queryRight);
            cout << querySum(1, 1, n) << endl;
        } else {
            scanf("%d%d%d", &toUpdateLeft, &toUpdateRight, &val);
            update(1, 1, n);
        }
    }

    return 0;
}
