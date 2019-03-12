#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

/*
    这个模拟还稍微有点复杂，，，。。。
*/

const int maxn = 105, maxl = 1005;

int main()
{
    int dir[maxn];
    int pos[maxn];
    int n, l, t;
    cin >> n >> l >> t;
    vector<int> axisTemp[maxl];
    for (int i = 0; i < n; i++)
    {
        cin >> pos[i];
        dir[i] = 1;
        axisTemp[pos[i]].push_back(i);
    }

    for (int i = 1; i <= t; i++)
    {
        vector<int> axis[maxl];
        for (int j = 0; j <= l; j++)
        {
            axis[j].assign(axisTemp[j].begin(), axisTemp[j].end());
            axisTemp[j].clear();
        }
        for (int j = 0; j <= l; j++)
        {
            if (j == 0)
            {
                while (axis[j].size())
                {
                    dir[axis[j][0]] = 1;
                    pos[axis[j][0]] = j + 1;
                    axisTemp[j + 1].push_back(axis[j][0]);
                    axis[j].erase(axis[j].begin());
                }
            }
            else if (j == l)
            {
                while (axis[j].size())
                {
                    dir[axis[j][0]] = -1;
                    pos[axis[j][0]] = j - 1;
                    axisTemp[j - 1].push_back(axis[j][0]);
                    axis[j].erase(axis[j].begin());
                }
            }
            else
            {
                while (axis[j].size())
                {
                    pos[axis[j][0]] = j + dir[axis[j][0]];
                    axisTemp[j + dir[axis[j][0]]].push_back(axis[j][0]);
                    axis[j].erase(axis[j].begin());
                }
            }
        }
        for (int j = 1; j < l; j++)
        {
            // 在端点不会两球相撞，所以遍历 1~l-1
            if (axisTemp[j].size() > 1)
            {
                for (int k = 0; k < axisTemp[j].size(); k++)
                {
                    dir[axisTemp[j][k]] *= -1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << pos[i] << " ";
    }
    cout << endl;

    return 0;
}
