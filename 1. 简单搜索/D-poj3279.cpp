#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

// POJ 3279 Fliptile

// 这个略难啊...感觉有点像脑筋急转弯...
// 思想：因为每一次翻转均会影响上下左右，且每个瓷砖最多 1 次翻转（有点绕）
// 所以先确定第一行的所有可能的翻转状态，
// 之后每一行的每一个瓷砖(i,j) 都使前一行对应的瓷砖(i-1,j) 翻转为 0（白色）即可
// 最后一行使倒数第二行全为 0 之后判断最后一行是否全为 0，不是的话则不存在该情况。

// 思考过程：因为存在相互影响的情况，所以肯定需要从一点切入
// 自然从开头（第一行）切入，并且利用了某瓷砖(i-1,j)可只由(i,j)的翻转而确定

// 用到了移位枚举的技巧，如二进制 1 左移 3 位便是 1000，
// 则从 000 ~ 1000 的每个数确定了一个三位的状态（如：010 001 011）等

int m, n;
const int LIMIT = 16;
bool originGrid[LIMIT][LIMIT], grid[LIMIT][LIMIT];
int res[LIMIT][LIMIT], minRes[LIMIT][LIMIT];
int cnt, minCnt = INF;

void flip(int i, int j) {
    // 翻转一个瓷砖

    res[i][j]++;
    cnt++;
    grid[i][j] = !grid[i][j];
    if (i > 0) {
        grid[i - 1][j] = !grid[i - 1][j];
    }
    if (i < m - 1) {
        grid[i + 1][j] = !grid[i + 1][j];
    }
    if (j > 0) {
        grid[i][j - 1] = !grid[i][j - 1];
    }
    if (j < n - 1) {
        grid[i][j + 1] = !grid[i][j + 1];
    }
}

int main() {
    cin >> m >> n;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> originGrid[i][j];
        }
    }

    // 枚举第一行的所有状态
    for (int status = 0, all = 1 << n; status < all; status++) {
        memcpy(grid, originGrid, sizeof(grid));
        memset(res, 0, sizeof(res));
        cnt = 0;

        // 第一行：
        for (int j = 0; j < n; j++) {
            if ((status >> j) & 1) {
                flip(0, j);
            }
        }
        // 接下来 m-1 行：
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i - 1][j]) {
                    flip(i, j);
                }
            }
        }
        // 检查最后一行：
        for (int j = 0; j < n; j++) {
            if (grid[m - 1][j]) {
                cnt = INF;
            }
        }

        if (cnt < minCnt) {
            minCnt = cnt;
            memcpy(minRes, res, sizeof(res));
        } 
        else if (cnt == minCnt && cnt != INF) {
            // 翻转次数相同时比较字典序，
            // 即比较第一个不同的值即可：
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (res[i][j] != minRes[i][j]) {
                        if (res[i][j] < minRes[i][j]) {
                            memcpy(minRes, res, sizeof(res));
                        }
                        goto next;
                    }
                }
            }
        }
        next:;
    }

    // 输出
    // 注意！行末多余的空格、多行最后的回车可能会导致错误！！
    if (minCnt != INF) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << minRes[i][j];
                if (j != n - 1)
                    cout << " ";
            }
            if (i != m - 1)
                cout << "\n";
        }
    } 
    else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}