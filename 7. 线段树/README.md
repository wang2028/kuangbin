# 线段树

> kuangbin 系列专题 7 线段树，题解见 [Github](https://github.com/Zen-w/kuangbin/tree/master/7.%20%E7%BA%BF%E6%AE%B5%E6%A0%91)，持续更新中

个人理解为以“空间换时间”，从而快速求序列某段范围的某种值（以最小值为例）的算法，且用于换“时间”的“空间”以特殊数据结构存储数据。即，将各段范围的最小值保存，从而在求不同段的时候不需重复遍历求。而这些保存的值，恰好符合“树”的形式，且选择二叉树（非满二叉树）的形式，方便操作。

对该专题的题目一些体会：
* scanf() 确实比 cin 快不少，有时就是 AC 与 TLE 的区别...
* 有时 int 不能满足，需要 long long
* 注意线段树非“满二叉树”、“完全二叉树”，所以建树 build() 时不能直接将原始数据存入 array[n~2n-1] 之后 从 array[n-1] 遍历至 array[1] 来生成树，而需要递归实现
* 又复习并加深了对二叉树的理解

## 点修改

即求解动态范围的最小值问题，将一个范围看做一个线段，完整的根线段作根结点，建立二叉树（线段树），每个结点对应一个范围线段，每个结点的值存储该范围线段内的最小值（以最小值为例）。

### 查询、更新、建树

注意
* 因为以数组的形式存储树，所以从 0 开始与从 1 开始时某些计算不同
* maxn 该树的最大节点数，实际可取略大于元素个数的 4 倍，不是 2 倍！因为节点数大于 2^x^ 时，取 2^x+1^ 明显不够

以下代码（模板）以求区间最小值为例：

```C++ {.lang-type-C++}
const int maxn = 100009;
int minv[maxn]; // 每个节点保存的线段最小值
int origin[maxn/4]; // 读入的原始数据，建树操作需要

// 建树：
void build(int o, int l, int r) {
    // 递归实现，复杂度相当于遍历一次树，大约 2n，i.e.O(n)
    if (l == r) {
        minv[o] = origin[l];
    }
    else {
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        minv[o] = min(minv[o * 2], minv[o * 2 + 1]);
    }
}

// 查询：
int queryLeft, queryRight; // 需要查询最小值的闭区间
int queryMin(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return minv[o];
    }
    int mid = left + (right - left) / 2; // 取中点
    int ans = INF;
    if (queryLeft <= mid) {
        ans = min(ans, queryMin(o * 2, left, mid));
    }
    if (queryRight > mid) {
        ans = min(ans, queryMin(o * 2 + 1, mid + 1, right));
    }
    return ans;
}

// 更新 minv[toUpdate] = val：
int toUpdate, val;
void update(int o, int left, int right) {
    // 因为是二叉树，所以当根线段元素数量确定时所有点在数组中的位置都确定了
    // 因此先递归找到叶节点，并更新
    // 同时更新该递归路径上每个非叶节点的值（最小值）
    // 复杂度为 logn
    if (left == right) {
        // 叶节点
        minv[o] = val;
    } else {
        int mid = left + (right - left) / 2; // 取中点
        if (toUpdate <= mid) {
            // 递归左子树
            update(o * 2, left, mid);
        } else {
            update(o * 2 + 1, mid + 1, right);
        }
        minv[o] = min(minv[o * 2], minv[o * 2 + 1]); // 更新线段最小值
    }
}

int main() {
    int n = 8;
    // 建树：
    for (int i = 1; i <= n; i++) {
        scanf("%d", &origin[i]);
    }
    build(1, 1, n);

    while (1) {
        cin >> queryLeft >> queryRight;
        cout << queryMin(1, 1, n) << endl;
    }

    return 0;
}

```

### 扩展

#### 动态最大连续和

线段树同样可求“动态最大连续和”的问题，只是将保存每个节点处的（线段）最小值 minv 改为保存每个节点处的最大字段和 max_sub、最大前缀和 max_prefix、最大后缀和 max_suffix，在根据子节点递推根节点的这三个值时相应的改变算法即可。

<br>

## 区间修改

> 对紫书上此部分的讲解不太理解，于是开始 google...找到一篇 http://www.cnblogs.com/TenosDoIt/p/3453089.html#f ，看了其中的的“区间修改”部分，才大致懂了
> by the way, 有时候书上讲的看不懂真的急得慌...紫书有时候讲几句就给代码，是俺这么辣鸡吗？...幸好去网上搜了搜，才大致懂了，真的是讲的不一样差别真的大...

“点修改”中每次更新操作涉及一个点，影响 logn 个节点的值，而对于对一个区间的值进行统一的增值或减值操作时，多次调用“点修改”来实现显然会导致很多次更新，由此而生“区间修改”。

区间修改的实现思想即“延迟更新”，如对某节点 x 所对应的线段范围内的元素都增值 1，则对 x 点做“标记 mark”，且使标记值 mark=1，代表其（子树中）所有子节点中的叶节点都应增值 1，当实际查询或更新其子树中某个叶节点时，由递归依次将该“标记”向下传递，直到真正加至叶节点上。

有点类似操作系统中的内存的分页管理的替换页面时，对内存中修改过的页面添加标记，被新页面替换时，若页面带标记，则需要写回硬盘，以保持硬盘中的数据与内存中新的数据保持一致，但不需要替换出内存时，也不需要对硬盘进行写入，（而没标记的页面，被替换时显然不用写回硬盘了）。

以下代码（模板）以求区间和、对区间增加值为例，其中函数参数等说明同上文“点修改”：

```C {.lang-type-C++}
// 实际使用时注意是否需要 long long 类型：
const int maxn = 400009; // 同上“点修改”
int sumv[maxn]; // 每个节点保存的线段和
int mark[maxn]; // 对点进行标记，以示该点的所有子叶节点实际上需要更新
int origin[maxn / 4]; // 读入的原始数据，建树操作需要

// 建树：
void build(int o, int l, int r) {
    mark[o] = 0;
    if (l == r) {
        sumv[o] = origin[l];
    } else {
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
}

// 延迟更新标记向子树传递：
void markDown(int o, int left, int right) {
    if (mark[o]) {
        // 设置左右孩子节点的标志域，
        // 因为孩子节点可能被多次延迟标记又没有向下传递，所以是 “+=” ！！
        mark[o * 2] += mark[o];
        mark[o * 2 + 1] += mark[o];
        
        sumv[o * 2] += mark[o] * ((right + left) / 2 - left + 1);
        sumv[o * 2 + 1] += mark[o] * (right - (right + left) / 2);
        mark[o] = 0; // 向下传递后清空该根结点的标记
    }
}

// 查询：
int queryLeft, queryRight; // 需要查询最小值的闭区间
int querySum(int o, int left, int right) {
    // 当前节点，当前节点的线段范围的左、右
    if (queryLeft <= left && queryRight >= right) {
        // 待查询线段完全覆盖当前点，直接返回当前点的线段最小值
        return sumv[o];
    }
    markDown(o, left, right);
    int mid = (right + left) / 2; // 取中点
    int ans = 0;
    if (queryLeft <= mid) {
        ans += querySum(o * 2, left, mid);
    }
    if (queryRight > mid) {
        ans += querySum(o * 2 + 1, mid + 1, right);
    }
    return ans;
}

// 更新 minv[toUpdate] = val：
int toUpdateLeft, toUpdateRight, val;
void update(int o, int left, int right) {
    if (left >= toUpdateLeft && right <= toUpdateRight) {
        // 叶节点
        sumv[o] += val * (right - left + 1);
        mark[o] += val;
    } else {
        markDown(o, left, right);
        int mid = left + (right - left) / 2; // 取中点
        if (toUpdateLeft <= mid) {
            // 递归左子树
            update(o * 2, left, mid);
        }
        if (toUpdateRight > mid) {
            // 递归右子树
            update(o * 2 + 1, mid + 1, right);
        }
        sumv[o] = sumv[o * 2] + sumv[o * 2 + 1];
    }
}
```


