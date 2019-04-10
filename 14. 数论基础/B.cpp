#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
typedef long long ll;

using namespace std;

/*
    C - Aladdin and the Flying Carpet LightOJ - 1341
*/

const ll maxn = 1e6 + 10;
// 这里 maxn 直接取的就是题中最大值开根号，所以下方筛时不能再开根号了...
// 竟然又犯了忘题的错...！！

bool isPrime[maxn];
int prime[maxn], cnt = 0;
void ei() {
    memset(isPrime, true, sizeof(isPrime));
    prime[cnt++] = 1;
    for (ll i = 2; i < maxn; i++) {
        if (isPrime[i]) {
            prime[cnt++] = i;
            for (ll j = i * i; j < maxn; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    ei();
    ll T;
    scanf("%lld", &T);
    ll n, minEdge;
    for (ll kase = 0; kase < T; kase++) {
        scanf("%lld%lld", &n, &minEdge);
        if (minEdge * minEdge > n) {
            printf("Case %d: 0\n", kase + 1);
            continue;
        }
        ll curMi, sum = 1, del = 0, origin = n;
        for (ll i = 1; prime[i] * prime[i] <= n && i < cnt; i++) {
            if (n % prime[i] == 0) {
                curMi = 0;
                while (n % prime[i] == 0) {
                    n /= prime[i];
                    curMi++;
                }
                sum *= (curMi + 1);
            }
        }
        // 注意这种情况：
        if (n > 1) {
            // 此时存在一个大于 sqrt(n) 的素因子（当然，最多就 1 个）
            sum *= 2;
        }
        // 这里 sum 为奇数时，不用加 1，因为题目中说不可以是正方形，
        // 所以假如面积为 4，2*2 是不符合要求的
        // if (sum % 2) {
        // sum = (sum + 1) / 2;
        //}
        // else {
        sum /= 2;
        //}

        // 将 n 中小于 minEdge 的因数对去除掉
        for (ll i = 1; i < minEdge; i++) {
            if (origin % i == 0) {
                sum--;
            }
        }
        printf("Case %d: %lld\n", kase + 1, sum);
    }

    return 0;
}
