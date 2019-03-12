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

// 有点编译原理里面词法分析器的意思...

vector<string> params;
bool check(string reg, string test)
{
    params.clear();
    int pos = 0;
    for (int i = 0; i < reg.length(); i++)
    {
        if (reg[i] != '<')
        {
            if (test[pos] == reg[i])
            {
                pos++;
            }
            else
            {
                return false;
            }
        }
        else
        {
            i++;
            string p = ""; // 保存参数
            if (reg[i] == 'i')
            {
                // int
                bool pre0 = true;
                while (test[pos] >= '0' && test[pos] <= '9')
                {
                    if (!(test[pos] == '0' && pre0))
                    {
                        pre0 = false;
                        p += test[pos];
                    }
                    pos++;
                }
                if (!p.length())
                {
                    return false;
                }
                else
                {
                    params.push_back(p);
                }
                i += 3;
            }
            else if (reg[i] == 's')
            {
                // str
                while ((test[pos] >= 'a' && test[pos] <= 'z') || (test[pos] >= 'A' && test[pos] <= 'Z') || (test[pos] >= '0' && test[pos] <= '9') || test[pos] == '-' || test[pos] == '_' || test[pos] == '.')
                {
                    p += test[pos];
                    pos++;
                }
                if (!p.length())
                {
                    return false;
                }
                else
                {
                    params.push_back(p);
                }
                i += 3;
            }
            else if (reg[i] == 'p')
            {
                // path
                while ((test[pos] >= 'a' && test[pos] <= 'z') || (test[pos] >= 'A' && test[pos] <= 'Z') || (test[pos] >= '0' && test[pos] <= '9') || test[pos] == '-' || test[pos] == '_' || test[pos] == '.' || test[pos] == '/')
                {
                    p += test[pos];
                    pos++;
                }
                if (!p.length())
                {
                    return false;
                }
                else
                {
                    params.push_back(p);
                }
                i += 4;
                if (i < reg.length() - 1)
                {
                    return false;
                }
            }
        }
    }
    if (pos < test.length())
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    int n, test;
    cin >> n >> test;
    vector<pair<string, string>> regs;
    string a, b;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        regs.push_back(make_pair(a, b));
    }
    for (int i = 0; i < test; i++)
    {
        cin >> a;
        int j = 0;
        for (; j < n; j++)
        {
            string reg = regs[j].first;
            if (check(reg, a))
            {
                cout << regs[j].second;
                for (int i = 0; i < params.size(); i++)
                {
                    cout << " " << params[i];
                }
                cout << "\n";
                break;
            }
        }
        if (j == n)
        {
            cout << "404"
                 << "\n";
        }
    }

    return 0;
}
