# 数论基础

https://vjudge.net/contest/210228#problem/A

注：数较多时，注意用 long long、%lld、scanf 等

## 最大公约数

```C++ {.lang-type-C++}
int gcd(int a, int b){
    if(!b)
        return a;
    return gcd(b, a % b);
}
```

## 最小公倍数

a、b 两数的最小公倍数为两数的乘积除以它们的最大公约数

## 素数筛

素数：除 1 和其本身外没有其他因子；两素数必互质。

注意：素数筛应该把筛出的素数单独存放在一个数组中，否则遍历原布尔数组仍会超时

```C++ {.lang-type-C++}
const int maxn = 100;
int primes[maxn];
int init(){
    // 筛出 1~maxn 的素数
    bool isPrime[maxn];
    memset(isPrime, 0, sizeof(isPrime));
    for(int i = 0;i<maxn;i++){
        isPrime[i] = true;
    }
    
    int primeCnt = 0;
    for (int i = 2; i < maxn;i++){
        if(!isPrime[i])
            continue;
        primes[primeCnt++] = i;
        for(int j = i*i;j<maxn;j+=i){
            isPrime[j] = false;
        }
    }
    return primeCnt;
}
```

## 分解素因数

1. 利用素数筛法筛得 0 到 100000（即 sqrt(n)）区间内所有素数。 
2. 输入 n。 
3. 依次测试步骤 1 中得到的素数能否整除 n，若能则表明该素数为它的一个素因数。 
4. 不断将 n 除以该素数，直到不能再被整除为止，同时统计其幂指数。 
5. 若在完成某个素数的幂指数统计后，n 变为 1，则表明 n 的所有素因数全 部被分解出来，这样就不用再去遍历后续的素数，分解活动提前终止。 
6. 若遍历、测试、分解完所有预处理出来的素数，n 仍旧没被除成 1，则表明 n 存在一个大于 100000 的因子，且该因子必为其素因子，且其幂指数必然为 1。

### 扩展

整数 n 的所有因子个数为其各素因素的幂加 1 的和的乘积

## 方程

对于 a0x0 + a1x1 + ... + anxn = C，若 a0,a1,...,an 互质，则一定有解，但存在 C 使得无非负数解。
（且对于大于 a*b-a-b 的 C 几乎全都有解）
若不互质，则存在无限多 C 使得无解。

## 闰年

闰年：year % 100 != 0 && year % 4 == 0 || year % 400 == 0