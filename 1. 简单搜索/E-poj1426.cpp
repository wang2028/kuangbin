#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

// POJ 1426 Find The Multiple

// 因为结果上限 100 位，所以直接暴力存会爆掉（但好像有人直接暴力过了...）
// 所以按照手算除法的思路，
// 如：11/3=3...2，接下来 20/3、21/3 的余数与 110/3、111/3 的余数相同，
// 所以可以用余数 2 代替原数 11，原数直接按位 push 进一个数组保存即可

// 之所以涉及到“搜索”是因为每一位可取 0 或 1，是一个（双入口）广搜

const int LIMIT = 201;
const int DIGIT = 100; // 最多 100 位十进制

typedef struct {
    int mod;         // 当前余数
    vector<int> res; // 到目前为止的结果
} State;             // 状态

int main() {
    // 深搜需要搜到上限（100 digits），太耗时，
    // 采用队列实现的 bfs

    bool checked[LIMIT];
    queue<State> q;
    int n;

    vector<int> tempres;
    State temps, start;
    start.mod = 1; // 首位一定是 1
    start.res.push_back(1);
    int tempi;
    while (cin >> n && n) {
        memset(checked, 0, sizeof(checked));
        q = queue<State>();
        q.push(start);
        checked[1] = true;

        while (!q.empty()) {
            temps = q.front();
            q.pop();
            for (int i = 0; i <= 1; ++i) {
                // 注意！不能直接修改temps！因为下一次循环还要用！

                tempres = temps.res;
                tempres.push_back(i);
                tempi = temps.mod * 10 + i;
                tempi = tempi % n;
                if (tempi == 0 && tempres.size() <= DIGIT) {
                    for (int j = 0, len = tempres.size(); j < len; j++) {
                        cout << tempres[j];
                    }
                    cout << "\n";
                    goto next;
                }
                if (!checked[tempi]) {
                    checked[tempi] = true;
                    q.push({tempi, tempres});
                }
            }
        }

    next:;
    }

    return 0;
}