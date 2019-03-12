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

const int maxn = 505, maxm = 100005;

int main()
{
    int last = -1, cur = 0, all = 0;
    while (cin >> cur && cur)
    {
        if (cur == 1)
        {
            all += 1;
            last = 1;
        }
        else
        {
            if (last == 1 || last == -1)
            {
                all += 2;
                last = 2;
            }
            else
            {
                last += 2;
                all += last;
            }
        }
    }
    cout << all << endl;

    return 0;
}