#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

/*
    D - Mayor's posters POJ - 2528
    TODO 未提交
    线段树（区间修改）
    将每个“海报”看做一种颜色，
    color[i] 表示节点 i 当前颜色，未访问的点置为 -1，
    修改标记下移时将父结点置为 -2，表示访问过该节点且子节点颜色不统一，
    子节点颜色统一时，color[i] 表示其颜色。
    添加海报时直接用模板中区间修改的方法，
    最后树遍历一遍，跳过 color[i]==-1 的点，递归遍历 color[i]==-2 的点，
    记录 color[i] 为具体颜色值（0~n-1）的点到一个 set 中，最后输出 set 元素个数。
*/

const int maxm = 13;
const int maxn = maxm * 4 + 5; // 同上“点修改”
int color[maxn];
int mark[maxn];

// 左子树 left ~ (left+right)/2，右子树 (left+right)/2+1 ~ right
// 建树：
void build() { memset(color, -1, sizeof(color)); }

// 延迟更新标记向子树传递：
void markDown(int o, int left, int right) {
    if (color[o] >= 0) {
        color[o * 2] = color[o];
        color[o * 2 + 1] = color[o];
    }
    color[o] = -2;
}

// 更新 minv[toUpdate] = val：
int toUpdateLeft, toUpdateRight, val;
void update(int o, int left, int right) {
    if (toUpdateLeft <= left && right <= toUpdateRight) {
        // 叶节点
        color[o] = val;
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
    }
}

set<int> ans;
void solve(int o) {
    if (color[o] >= 0) {
        ans.insert(color[o]);
        return;
    }
    if (color[o] == -2) {
        solve(o * 2);
        solve(o * 2 + 1);
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        build();
        for (int i = 0; i < n; i++) {
            cin >> toUpdateLeft >> toUpdateRight;
            val = i;
            update(1, 1, maxm);
        }
        solve(1);
        cout << ans.size() << endl;
    }

    return 0;
}