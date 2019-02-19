#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

/*
    D - How Many Answers Are Wrong 扩展并查集（我感觉称作向量并查集更好）

    题目表意不清，我咋感觉很多要求题目都没说到，如下：
    1. 题目未说多组测试并以 EOF 结束，错以为仅一组测试
    2. 题目未说第一条指令一定是正确的，可能第一条就是错的呢？
    3. 题目未说 Si 取值！经网上很多 ac 代码测试， 
        类似 10 2 1 10 10 3 6 30 的测试数据结果均测为 0，说明 Si 可取负数

    难以想到的点：
    1. 读入 left right sum 之后 left 需要减 1，
        因为给出的是闭区间，而对于向量化的并查集来讲其应该是统一的，
        减 1 之后变成了左开右闭区间，便统一了
    2. 第一次做扩展并查集，在 find() 函数中路径压缩时 “偏移量”offset 的计算有问题
        详见 find() 函数中注释
*/

const int maxn = 200086;
int fa[maxn];
int offset[maxn];
int find(int i) {
    if (fa[i] == i) {
        return i;
    } else {
        int p = fa[i];
        fa[i] = find(fa[i]);
        // 注意！在上一步 find() 内 i 的父结点 fa[i] 的 offset 已经被改变了
        // （如果 fa[i] 仍不是根结点时）
        // 因此不能再 find() 之前保存 fa[i] 的值以后用
        offset[i] += offset[p];
        return fa[i];
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        int err = 0;
        for (int i = 0; i <= n; i++) {
            fa[i] = i;
            offset[i] = 0;
        }
        int fax, fay;
        int x, y, sum;
        while (m--) {
            cin >> x >> y >> sum;
            x--;
            fax = find(x);
            fay = find(y);
            if (fax == fay) {
                if (sum != offset[x] - offset[y]) {
                    err++;
                }
            } else {
                fa[fax] = fay;
                offset[fax] = offset[y] - offset[x] + sum;
            }
        }

        cout << err << endl;
    }
    return 0;
}
