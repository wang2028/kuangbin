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
    线段树（区间修改） + 区间压缩
    线段树：
        将每个“海报”看做一种颜色，
        color[i] 表示节点 i 当前颜色，未访问的点置为 -1，
        修改标记下移时将父结点置为 -2，表示访问过该节点且子节点颜色不统一，
        子节点颜色统一时，color[i] 表示其颜色。
        添加海报时直接用模板中区间修改的方法，
        最后树遍历一遍，跳过 color[i]==-1 的点，递归遍历 color[i]==-2 的点，
        记录 color[i] 为具体颜色值（0~n-1）的点到一个 set 中，
        最后输出 set 元素个数。
    区间压缩：
        因为海报墙范围到 1e7，所以直接用线段树肯定 TLE or RE or MLE，
        因此需要压缩区间。
        如有两海报左右端点分别为：1~3, 5~10，可压缩为 1~2, 3~4 即可，
        实现思路：记录下出现的所有端点的值（这些点必须要保留），
        去重之后进行升序排序，之后将第一个点的值映射为 1，第二点映射为 2 ...
        之后将每个海报张贴时，直接用压缩后的映射的值来张贴（线段树区间修改）。
        下方代码中去重使用的 set，且可省去排序了~
    结果：922ms（压线过，惊险...）；34.5MB
*/

const int maxm = 1e7;
const int maxn = 10003;
int press[maxm];
int color[maxn * 2 * 4 + 5];

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
pair<int, int> post[maxn];
set<int> s;
int main() {
    // freopen("C:\\Users\\DELL\\Desktop\\tests\\G.1.dat", "r", stdin);
    // freopen("C:\\Users\\DELL\\Desktop\\tests\\G.1.dat", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        build();
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &post[i].first, &post[i].second);
            s.insert(post[i].first);
            s.insert(post[i].second);
        }
        int cnt = 1;
        for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
            press[*it] = cnt++;
        }
        for (int i = 0; i < n; i++) {
            toUpdateLeft = press[post[i].first];
            toUpdateRight = press[post[i].second];
            val = i;
            update(1, 1, cnt - 1);
        }
        solve(1);
        cout << ans.size() << endl;
        ans.clear();
        s.clear();
    }

    return 0;
}