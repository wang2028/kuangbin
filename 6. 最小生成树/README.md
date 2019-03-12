# 最小生成树

根据 MST 性质，主要有 Prim（见 专题8.生成树 README.md）和 Kruscal 两类算法，个人倾向 Kruscal 嘿嘿（因为紫书没讲 Prim...）


## Kruscal

除 MST 性质外，Kruscal 的实现主要还依靠两思想：
* 并查集：见 专题5.并查集 中 README.md
* 间接排序：即仍将数据存储在固定的数组中，仅将其序号单独存放在另一数组，进行排序，因为所需排序的数据量变小很多，效率实测也会提升（适用于元素结构很大的数组，一般结构体的数组可以不用）

详见：[图论 · 最小生成树 · Kruscal](https://wangxw.cn/htmls/p-k-d-f.html#H3-2)