#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// TODO 

const int maxn = 20000;
int map[4][4];
int zero = 0; //空格个数
int d[maxn];

int check() //检查是否出现赢的局面
{
    for (int i = 0; i < 3; i++)
    {
        if (map[i][0] && map[i][0] == map[i][1] && map[i][1] == map[i][2])
            return map[i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        if (map[0][i] && map[0][i] == map[1][i] && map[1][i] == map[2][i])
            return map[0][i];
    }
    if (map[0][0] && map[0][0] == map[1][1] && map[1][1] == map[2][2])
        return map[0][0];
    if (map[0][2] && map[0][2] == map[1][1] && map[1][1] == map[2][0])
        return map[0][2];
    return 0;
}
int fpow(int x, int t) //x^t,快速幂
{
    int ans = 1;
    int tt = x;
    while (t)
    {
        if (t & 1)
            ans = ans * tt;
        tt *= tt;
        t >>= 1;
    }
    return ans;
}

int dfs(int t) //t==1 Alice t==2 Bob
{
    int tmp = check();
    if (tmp)
    {
        return tmp == 1 ? (zero + 1) : (-zero - 1);
    }

    if (zero == 0) //无棋可下，平局
        return 0;

    int mx = -1e9, mi = 1e9; //mx 最大值，mi 最小值

    int state = 0; //计算当前状态，记忆化
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            state += pow(3, 3 * i + j) * map[i][j];
    }
    if (d[state] != -1e9)
        return d[state];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!map[i][j])
            {
                map[i][j] = t;
                zero--;
                int tmp = dfs(3 - t);
                mx = max(mx, tmp);
                mi = min(mi, tmp);
                zero++; //回溯
                map[i][j] = 0;
            }
        }
    }
    if (t == 1)
        return d[state] = mx; //记忆化
    else
        return d[state] = mi;
}

int main()
{
    int cas;
    scanf("%d", &cas);
    for (int i = 0; i < maxn; i++) // maxn 为何取 6e4+10 ？
        d[i] = -1e9;            
    while (cas--)
    {
        zero = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                scanf("%d", &map[i][j]);
                if (!map[i][j])
                    zero++;
            }
        int t = check(); //首先判断当前局面是否有人赢
        if (t)
        {
            printf("%d", t == 1 ? zero + 1 : -zero - 1);
            cout << endl;
            continue;
        }

        printf("%d", dfs(1));
        cout << endl;
    }
    return 0;
}