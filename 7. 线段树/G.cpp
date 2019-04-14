#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

/*
    G - Balanced Lineup POJ - 3264
    线段树很基础的模板题，维护两个数组（最大和最小）即可
*/

const int maxn = 50005 * 4 + 5;
int n, m;
int minv[maxn];       // 每个节点保存的线段和
int maxv[maxn];       // 每个节点保存的线段和
int origin[maxn / 4]; // 读入的原始数据，建树操作需要

// 左子树 left ~ (left+right)/2，右子树 (left+right)/2+1 ~ right
// 建树：
void build(int o, int l, int r) {
    if (l == r) {
        minv[o] = origin[l]; // 应该将此时 o 点的范围左端下标对应 origin
                             // 赋值，而不是 minv[o]=origin[o]
        maxv[o] = origin[l];
    } else {
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        minv[o] = min(minv[o * 2], minv[o * 2 + 1]);
        maxv[o] = max(maxv[o * 2], maxv[o * 2 + 1]);
    }
}

// 查询：
int queryLeft, queryRight; // 需要查询最小值的闭区间
int queryMin(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return minv[o];
    }
    int mid = (right + left) / 2; // 取中点
    int ans = INF;
    if (queryLeft <= mid) {
        ans = min(ans, queryMin(o * 2, left, mid));
    }
    if (queryRight > mid) {
        ans = min(ans, queryMin(o * 2 + 1, mid + 1, right));
    }
    return ans;
}
int queryMax(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return maxv[o];
    }
    int mid = (right + left) / 2; // 取中点
    int ans = 0;
    if (queryLeft <= mid) {
        ans = max(ans, queryMax(o * 2, left, mid));
    }
    if (queryRight > mid) {
        ans = max(ans, queryMax(o * 2 + 1, mid + 1, right));
    }
    return ans;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &origin[i]);
    }
    build(1, 1, n);

    while (q--) {
        scanf("%d%d", &queryLeft, &queryRight);

        cout << queryMax(1, 1, n) - queryMin(1, 1, n) << endl;
    }

    return 0;
}