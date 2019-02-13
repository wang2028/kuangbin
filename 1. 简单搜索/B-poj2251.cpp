#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

// POJ 2251 Dungeon Master

// 思想：通过队列实现广搜（bfs），只是扩展到了三维；
// 每一个状态有三个轴的值（l,r,c），可以简单封装为一个结构体，
// 但我好久没写算法题了...忘了封装...

// 每一组对应的 dirL[i],dirR[i],dirC[i] 表示：向6个方向之一 走一步的偏移量
const int dirL[] = {1, -1, 0, 0, 0, 0};
const int dirR[] = {0, 0, 0, 0, 1, -1};
const int dirC[] = {0, 0, -1, 1, 0, 0};

const int INF = 2 * 1000000000; // 最大值，用作最短时间的初始值
const int LIMIT = 32;
bool maze[LIMIT][LIMIT][LIMIT] = {false}; // 用布尔值代表可走与否
int l, r, c;

int endL, endR, endC;
int curL, curR, curC;
int minTime, curT;
queue<int> qL;
queue<int> qR;
queue<int> qC;
queue<int> qT; // 时间队列

int main() {
    char tempch;
    int templ, tempr, tempc, tempt;
    // 最外圈筑墙：
    for (int j = 0; j <= r + 1; j++) {
        for (int k = 0; k <= c + 1; k++) {
            maze[0][j][k] = false;
        }
    }
    for (int i = 0; i <= l + 1; i++) {
        for (int k = 0; k <= c + 1; k++) {
            maze[i][0][k] = false;
        }
    }
    for (int i = 0; i <= l + 1; i++) {
        for (int j = 0; j <= r + 1; j++) {
            maze[i][j][0] = false;
        }
    }

    while (cin >> l >> r >> c) {
        if (l == 0) break;

        // 最外圈筑墙：
        for (int j = 0; j <= r + 1; j++) {
            for (int k = 0; k <= c + 1; k++) {
                maze[l + 1][j][k] = false;
            }
        }
        for (int i = 0; i <= l + 1; i++) {
            for (int k = 0; k <= c + 1; k++) {
                maze[i][r + 1][k] = false;
            }
        }
        for (int i = 0; i <= l + 1; i++) {
            for (int j = 0; j <= r + 1; j++) {
                maze[i][j][c + 1] = false;
            }
        }

        // 开始读取：
        for (int i = 1; i <= l; i++) {
            for (int j = 1; j <= r; j++) {
                for (int k = 1; k <= c; k++) {
                    cin >> tempch;
                    if (tempch == '#') {
                        maze[i][j][k] = false;
                    } 
                    else if (tempch == '.') {
                        maze[i][j][k] = true;
                    } 
                    else if (tempch == 'S') {
                        curL = i;
                        curR = j;
                        curC = k;
                        maze[i][j][k] = true;
                    } 
                    else if (tempch == 'E') {
                        endL = i;
                        endR = j;
                        endC = k;
                        maze[i][j][k] = true;
                    }
                }
            }
        }

        minTime = INF;
        curT = 0;
        qL = queue<int>(); // 直接清空队列，
        qR = queue<int>(); // 不过这样可能会泄露内存...
        qC = queue<int>();
        qT = queue<int>();

        qL.push(curL);
        qR.push(curR);
        qC.push(curC);
        qT.push(curT);
        maze[curL][curR][curC] = false;

        while (!qT.empty() && minTime == INF) {
            // 此处有第二个判断条件的原因是 minTime 改变时说明已找到终点
            // 所以无需继续广搜，因为最先找到的一定时间最短
            curL = qL.front();
            curR = qR.front();
            curC = qC.front();
            curT = qT.front();
            qL.pop();
            qR.pop();
            qC.pop();
            qT.pop();

            for (int i = 0; i < 6; i++) {
                // 此处不能直接用 curL += dirL[i]，会使之后的循环中 curL 错误
                templ = curL + dirL[i];
                tempr = curR + dirR[i];
                tempc = curC + dirC[i];
                tempt = curT + 1;
                if (maze[templ][tempr][tempc]) {
                    // 第一次遇到一定是最短的，所以直接结束去输出
                    if (templ == endL && tempr == endR && tempc == endC) {
                        minTime = tempt;
                        break;
                    }
                    maze[templ][tempr][tempc] = false;
                    qL.push(templ);
                    qR.push(tempr);
                    qC.push(tempc);
                    qT.push(tempt);
                }
            }
        }

        if (minTime == INF) {
            cout << "Trapped!" << endl;
        } 
        else {
            cout << "Escaped in " << minTime << " minute(s)." << endl;
        }
    }

    return 0;
}

// 这是本来用的深搜（回溯），超时，换成广搜（bfs）了
// void back() {
//     if (curL == endL && curR == endR && curC == endC) {
//         if (minTime == -1 || curT<minTime) {
//             minTime = curT;
//             return;
//         }
//     }
//     if (minTime!=-1 && curT >= minTime-1) {
//         return;
//     }
//     for (int i = 0; i < 6; i++) {
//         curL += dirL[i];
//         curR += dirR[i];
//         curC += dirC[i];
//         if (maze[curL][curR][curC]) {
//             maze[curL - dirL[i]][curR - dirR[i]][curC - dirC[i]] = false;
//             curT++;
//             back();
//             maze[curL - dirL[i]][curR - dirR[i]][curC - dirC[i]] = true;
//             curT--;
//         }
//         curL -= dirL[i];
//         curR -= dirR[i];
//         curC -= dirC[i];
//     }
// }