# 字符串算法

## Rabin-Karp（滚动哈希）

利用哈希可以确定一种映射关系（当然会存在冲突），因此，可以将字符串匹配问题基于哈希来解。即，将问题：字符串a出现在字符串b中的位置（及次数等问题）换做遍历b以寻找哈希值与a相等的子串。
那么用来对一个字符串“编码”，也就是用来完成哈希函数映射的方法为：

H(s) = (c<sub>1</sub>B<sup>m-1</sup> + c<sub>2</sub>B<sup>m-2</sup> + ... +c<sub>m</sub>B<sup>0</sup>) mod h

即，将字符串看做 B 进制（取 B=100 000 000）的整数（用 unsigned long long 来存），（因为字符本质也是整数，所以可以参与运算），每当子串 s 位置后移 1 位时，将原 H(s) 乘 B，减去 原最高位 s[i]*b<sup>m</sup>，加上 s[i+m] 即为新的位置的哈希值。

```C++ {.lang-type-C++}
typedef unsigned long long ull;
const ull B = 100000007; // 哈希的基数，即 B 进制（我也不知道为什么取这么大，感觉 256 就够了）
int solve(string a, string b) {
    // 判断 a 是否在 b 中，返回出现次数
    int ans = 0;

    int alen = a.length(), blen = b.length();
    if (alen > blen)
        return false;

    ull t = 1; // 移动位置后最高位的权值
    for (int i = 0; i < a.length(); i++) {
        t *= B;
    }

    // 计算 a 的哈希、 b 的初始 a 位子字符串的哈希：
    ull ahash = 0, bhash = 0;
    for (int i = 0; i < alen; i++) {
        ahash = ahash * B + a[i];
        bhash = bhash * B + b[i];
    }
    if (ahash == bhash)
        ans++;

    // 开始滚动：
    for (int i = 1; i <= blen - alen; i++) {
        bhash = bhash * B - b[i - 1] * t + b[i - 1 + alen];
        if (ahash == bhash)
            ans++;
    }

    return ans;
}

int main() {
    string a = "abc", b = "aabcabc";
    cout << solve(a, b) << endl;
    
    return 0;
}
```