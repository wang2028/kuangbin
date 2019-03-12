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

const int maxn = 10005;

int main()
{
    bool arr[maxn];
    int n;
    cin >> n;
    int t;
    memset(arr, 0, sizeof(arr));
    int minGap = INF;
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        if (arr[t])
        {
            minGap = 0;
        }
        else
        {
            arr[t] = true;
        }
    }
    if (minGap)
    {
        int gap = INF;
        for (int i = 0; i < maxn; i++)
        {
            gap++;
            if (arr[i])
            {
                minGap = min(minGap, gap);
                gap = 0;
            }
        }
    }
    cout << minGap << endl;

    return 0;
}
