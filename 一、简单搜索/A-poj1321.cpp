#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;

// 回溯即可

int n = 0, k = 0;
vector<pair<int, int>> qipan; // vj(poj)的 G++ 编译器报错，嵌套尖括号时需要空格
bool x[8], y[8];              // 回溯中记录 x 轴和 y 轴是否被占
int C;                        // 方案数

void back(int t, int start)
{
    if (t >= k)
    {
        C++;
        return;
    }
    for (int i = start; i < qipan.size(); i++)
    {
        if (x[qipan[i].first] && y[qipan[i].second])
        {
            x[qipan[i].first] = false;
            y[qipan[i].second] = false;
            back(t + 1, i + 1);
            x[qipan[i].first] = true;
            y[qipan[i].second] = true;
        }
    }
}

int main()
{
    char temp;
    while (cin >> n >> k)
    {
        if (n == -1)
        {
            break;
        }
        qipan.clear();
        C = 0;
        for (int i = 0; i < 8; i++)
        {
            x[i] = true;
            y[i] = true;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> temp;
                if (temp == '#')
                {
                    qipan.push_back(make_pair(i, j));
                }
            }
        }

        back(0, 0);
        cout << C << endl;
    }

    return 0;
}