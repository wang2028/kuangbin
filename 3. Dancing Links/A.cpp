#include <iostream>
#include <stdio.h>
using namespace std;
const int maxnode = 450010;
const int maxm = 901; // 列数
const int maxn = 505; // 行数

// ZOJ 3209
// 把二维区域展开成一维的一行，每个纸片（覆盖的区域）同样展开，
// 即把每个纸片的覆盖区域在一维中对应位置看做 1，未覆盖的为 0

// 来自：https://blog.csdn.net/sr_19930829/article/details/39778883

struct DLX {
    int n, m, size; // 行、列、计数器（用来记录数组当前元素个数以向尾添加元素）
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode],
        Col[maxnode];     // 舞蹈链结构 6 字段
    int head[maxn];       // 每行头节点
    int thisColHas[maxm]; //每列有多少个节点
    int ansd;             // 当前选择了 ansd 行
    int ans[maxn];        // 具体是哪几行放在ans[]数组里面，ans[0~ansd-1];

    void init(int _n, int _m) {
        n = _n, m = _m;
        for (int i = 0; i <= m; i++) {
            thisColHas[i] = 0;
            U[i] = D[i] = i; //初始状态下，上下自己指向自己
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0, L[0] = m;
        size = m; //编号，每列都有一个头节点，编号1-m
        for (int i = 1; i <= n; i++)
            head[i] = -1; //每一行的头节点
    }

    void link(int r, int c) //第r行，第c列
    {
        ++thisColHas[Col[++size] =
                         c]; //第size个节点所在的列为c,当前列的节点数++
        Row[size] = r;  //第size个节点行位置为r
        D[size] = D[c]; //下面这四句头插法（图是倒着的？)
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if (head[r] < 0)
            head[r] = L[size] = R[size] = size;
        else {
            R[size] = R[head[r]];
            L[R[head[r]]] = size;
            L[size] = head[r];
            R[head[r]] = size;
        }
    }

    void remove(int c) {
        //删除节点c，以及c上下节点所在的行,每次调用这个函数，都是从列头节点开始向下删除，这里c也可以理解为第c列
        //因为第c列的列头节点编号为c
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i])
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --thisColHas[Col[j]];
            }
    }

    void resume(int c) {
        //恢复节点c,以及c上下节点所在的行(同上，也可以理解为从第c列的头节点开始恢复
        for (int i = U[c]; i != c; i = U[i])
            for (int j = L[i]; j != i; j = L[j])
                ++thisColHas[Col[U[D[j]] = D[U[j]] = j]]; //打这一行太纠结了 T T
        L[R[c]] = R[L[c]] = c;
    }

    void dance(int d) {
        //递归深度 d

        // 剪枝：
        if (ansd != -1 && ansd <= d) {
            //行数最少，以前找到一组答案ansd<=d，当前就不用再向下递归查找了
            return;
        }
        if (R[0] == 0) {
            if (ansd == -1 || d < ansd) {
                //要求最少用多少块
                ansd = d;
            }
            return;
        }

        int c = R[0];
        for (int i = R[0]; i != 0; i = R[i]) {
            //找到节点数最少的列
            if (thisColHas[i] < thisColHas[c])
                c = i;
        }

        // 开始回溯：
        remove(c);
        for (int i = D[c]; i != c; i = D[i]) {
            ans[d] = Row[i]; //列头节点下面的一个节点
            for (int j = R[i]; j != i; j = R[j]) {
                // 选择第 j 行保留
                remove(Col[j]);
            }
            dance(d + 1); //找到，返回
            for (int j = L[i]; j != i; j = L[j])
                resume(Col[j]);
        }
        resume(c);
    }
};

DLX x;
int n, m, p;
// 获取每个长方形（piece）的每个小格在大长方形里的编号：
int pos[32][32];
int cnt;
void getPos(int n, int m) {
    cnt = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            pos[i][j] = cnt++;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &p);
        x.init(p, n * m);
        getPos(n, m);
        for (int r = 1; r <= p; r++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            for (int i = x1 + 1; i <= x2; i++)
                for (int j = y1 + 1; j <= y2; j++)
                    x.link(r, pos[i][j]);
        }
        x.ansd = -1;
        x.dance(0);
        printf("%d\n", x.ansd);
    }
    return 0;
}