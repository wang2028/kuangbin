#include <cstdio>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f

/*
    E - Just a Hook HDU - 1698
    线段树模板小改
*/

const int maxn = 100000 * 4 + 5;
int n, m;
int sumv[maxn]; // 每个节点保存的线段和
int mark[maxn]; // 对点进行标记，以示该点的所有子叶节点实际上需要更新
int origin[maxn / 4]; // 读入的原始数据，建树操作需要
// 左子树 left ~ (left+right)/2，右子树 (left+right)/2+1 ~ right
// 建树：
void build(int o, int l, int r) {
    mark[o] = 0;
    if (l == r) {
        sumv[o] = 1;
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
        mark[o * 2] = mark[o];
        mark[o * 2 + 1] = mark[o];

        sumv[o * 2] = mark[o] * ((right + left) / 2 - left + 1);
        sumv[o * 2 + 1] = mark[o] * (right - (right + left) / 2);
        mark[o] = 0; // 向下传递后清空该根结点的标记
    }
}

// 查询：
int queryLeft, queryRight; // 需要查询最小值的闭区间
int querySum(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return sumv[o];
    }
    markDown(o, left, right);
    int mid = (right + left) / 2; // 取中点
    int ans = 0;
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
    if (toUpdateLeft <= left && right <= toUpdateRight) {
        // 叶节点
        sumv[o] = val * (right - left + 1);
        mark[o] = val;
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
    int T;

    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {

        scanf("%d%d", &n, &m);
        build(1, 1, n);
        while (m--) {
            scanf("%d%d%d", &toUpdateLeft, &toUpdateRight, &val);
            update(1, 1, n);
        }
        queryLeft = 1;
        queryRight = n;
        printf("Case %d: The total value of the hook is %d.\n", t,
               querySum(1, 1, n));
    }

    return 0;
}