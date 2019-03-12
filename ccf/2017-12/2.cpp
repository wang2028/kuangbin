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
    int n, k;
    cin >> n >> k;
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
    }
    int cnt = 0;
    int t;
    while (q.size() > 1)
    {
        cnt++;
        t = q.front();
        q.pop();
        if (cnt % k == 0 || cnt % 10 == k)
        {
            continue;
        }
        else
        {
            q.push(t);
        }
    }
    cout << q.front() << endl;

    return 0;
}
