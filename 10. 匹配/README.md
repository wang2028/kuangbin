# 匹配问题

## 二分匹配

### 基于最大流解法

可新增起点 s，汇点 t，将 s 连 U 中点 u 一条流量为 1 的边，V 中点 v 连 t 一条流量为 1 的边，这样求从 s 到 t 的最大流，即为 U-V 二分匹配的结果。

```C++ {.lang-type-C++}
const int maxn = 203, maxm = 203; // U、V 最大点数

int s = n + m, t = s + 1; // 新增源点、汇点
int binMatch(){
    // s -> U
    for(int i = 0;i<n;i++){
        addEdge(s, i);
    }
    // V -> t
    for (int i = n; i < n+m;i++){
        addEdge(i, t);
    }

    // 省略题目中所给的 U->V 的加边过程

    return maxFlow(s, t); // 求最大流的 maxFlow() 详见：专题11.网络流 README.md
}
```


### 匈牙利算法

对每个 u ∈ U，调用 find(u) 函数找到其适配的 v ∈ V。对于 find()，遍历所有 v，找到可达且未被标记的 v，（此处未被标记与未访问过还不太一样，因为存在调整之前的 u' 适配对象 v' 的问题），将 v 置为“标记过”，若该点 v 还未被之前的 u' 适配过，或者，递归调用 find(u') 为 u' 找到了新的适配对象，则可把当前的 v 分配给 u。

有向图版本：
```C++ {.lang-type-C++}
bool marked[maxm];
int match[maxm];
bool find(int x){
    for(int i = 0;i<m;i++){
        if(can[x][i] && !marked[i]){
            marked[i] = true;
            if(match[i] == -1 || find(match[i])){
                // 判断条件中：前者 -1 表示还未匹配过；后者表示为原配对象找到了新的匹配者
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}
void solve(){
    memset(match, -1, sizeof(match));
    for(int i = 0;i<n;i++){
        memset(marked, 0, sizeof(marked));
        find(i);
    }
}
```

无向图版本：
```C++ {.lant-type-C++}
// 以 vector<int> G[maxn] 存图
int match[maxm];
bool marked[maxm];
bool find(int x) {
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (!marked[v]) {
            marked[v] = true;
            if (match[v] == -1 || find(match[v])) {
                match[v] = x;
                match[x] = v; // 因为是无向图，所以双向匹配
                return true;
            }
        }
    }
    return false;
}
int solve() {
    int p = 0; // 可匹配对数；在 solve() 中求过之后需要除以 2
    memset(match, -1, sizeof(match));
    for (int i = 0; i<n; i++) {
        memset(marked, 0, sizeof(marked));
        if (match[i]!=-1 || find(i)) p++;
    }
    return p/2;
}
```

TODO 后缀数组