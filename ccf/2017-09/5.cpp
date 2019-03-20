#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

/*
    还是超时。。。
    （区间修改的）线段数组，
    与模板不太一样的地方是：
    因为题目中仅对特定条件（v的倍数）的值进行修改，
    所以在非叶子节点中无法直接计算出线段和，只能保留延迟更新标记，
    所以在更新时，直接递归到叶节点，而不能直接更新非叶节点，
    查询时仍直接查询就好了。
*/

const ll maxn = 100000 * 4 + 5;
ll sumv[maxn]; // 每个节点保存的线段和
ll mark[maxn]; // 对点进行标记，以示该点的所有子叶节点实际上需要更新
ll origin[maxn / 4]; // 读入的原始数据，建树操作需要

// 建树：
void build(ll o, ll l, ll r) {
    mark[o] = 0;
    if (l == r) {
        sumv[o] = origin[l];
    } else {
        ll mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
}

// 延迟更新标记向子树传递：
void markDown(ll o, ll left, ll right) {
    if (mark[o]) {
        // 设置左右孩子节点的标志域，
        // 因为孩子节点可能被多次延迟标记又没有向下传递，所以是 “+=” ！！
        mark[o * 2] += mark[o];
        mark[o * 2 + 1] += mark[o];
        /*
        sumv[o * 2] += mark[o] * ((right + left) / 2 - left + 1);
        sumv[o * 2 + 1] += mark[o] * (right - (right + left) / 2);*/
        mark[o] = 0; // 向下传递后清空该根结点的标记
    }
}

// 查询：
ll queryLeft, queryRight; // 需要查询最小值的闭区间
ll querySum(ll o, ll left, ll right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return sumv[o];
    }
    markDown(o, left, right);
    ll mid = (right + left) / 2; // 取中点
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
ll toUpdateLeft, toUpdateRight, val;
void update(ll o, ll left, ll right) {
    if (left == right) {
        // 叶节点
        if (sumv[o] % val == 0) {
            sumv[o] /= val;
        }
    } else {
        markDown(o, left, right);
        ll mid = left + (right - left) / 2; // 取中点
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
    ll n, m;
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> origin[i];
    }
    build(1, 1, n);
    ll opt, l, r, v;
    for (ll i = 0; i < m; i++) {
        cin >> opt;
        if (opt == 1) {
            cin >> toUpdateLeft >> toUpdateRight >> val;
            update(1, 1, n);
        } else {
            cin >> l >> r;
            queryLeft = l;
            queryRight = r;
            cout << querySum(1, 1, n) << endl;
        }
    }

    return 0;
}
