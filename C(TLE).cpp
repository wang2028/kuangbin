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

const long long maxn = 400009;
long long sumv[maxn];       // 每个节点保存的线段最小值
long long origin[maxn / 4]; // 读入的原始数据，建树操作需要
long long pos[maxn / 4];    // 第 i 个元素在树数组中的位置

// 建树：
void build(long long o, long long l, long long r) {
    // 递归实现，复杂度相当于遍历一次树，大约 2n，i.e.O(n)
    if (l == r) {
        sumv[o] = origin[l];
        pos[l] = o;
    } else {
        long long mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
}

// 查询：
long long queryLeft, queryRight; // 需要查询最小值的闭区间
long long queryMin(long long o, long long left, long long right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return sumv[o];
    }
    long long mid = left + (right - left) / 2; // 取中点
    long long ans = 0;
    if (queryLeft <= mid) {
        ans += queryMin(o * 2, left, mid);
    }
    if (queryRight > mid) {
        ans += queryMin(o * 2 + 1, mid + 1, right);
    }
    return ans;
}

// 更新 minv[toUpdate] = val：
long long toUpdate, val;
void update(long long o, long long left, long long right) {
    // 因为是二叉树，所以当根线段元素数量确定时所有点在数组中的位置都确定了
    // 因此先递归找到叶节点，并更新
    // 同时更新该递归路径上每个非叶节点的值（最小值）
    // 复杂度为 logn
    if (left == right) {
        // 叶节点
        sumv[o] = val;
    } else {
        long long mid = left + (right - left) / 2; // 取中点
        if (toUpdate <= mid) {
            // 递归左子树
            update(o * 2, left, mid);
        } else {
            update(o * 2 + 1, mid + 1, right);
        }
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
}

int main() {
    long long n, q;
    scanf("%ld%ld", &n, &q);
    for (long long i = 1; i <= n; i++) {
        scanf("%ld", &origin[i]);
    }
    build(1, 1, n);
    char cmd[3];
    long long l, r, curPos;
    while (q--) {
        scanf("%s", cmd);
        if (!strcmp(cmd, "Q")) {
            scanf("%ld%ld", &queryLeft, &queryRight);
            cout << queryMin(1, 1, n) << endl;
        } else {
            scanf("%ld%ld%ld", &l, &r, &val);
            for (long long i = l; i <= r; i++) {
                curPos = pos[i];
                while (curPos != 1) {
                    sumv[curPos] += val;
                    curPos /= 2;
                }
                sumv[curPos] += val;
            }
        }
    }

    return 0;
}
