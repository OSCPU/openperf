# ArchBench

| 类型 | benchmark                    | 介绍                 | 说明            |
|------|:----------------------------:|----------------------|-----------------|
| 测试 |  000.hello                   | Hello程序            | 测试用          |
| 小型 | [100.blockchain][blockchain] | 区块链               | 计算sha256      |
|      | [101.igemm][igemm]           | 矩阵乘法             | 仅含整数操作    |
|      | [102 queen][queen]           | N皇后问题            | 用位运算实现    |
|      | [103.dinic][dinic]           | 求解二分图最大流     |                 |
|      | [104.malloc][malloc]         | 动态内存分配         |                 |
|      | [105.bf][bf]                 | brainf\*ck语言解释器 |                 |
|      | [106.qsort][qsort]           | 快速排序             |                 |
|      | [107.stream][stream]         | 内存带宽测量         |                 |
|      | [108.ntt][ntt]               | 数论变换求多项式乘法 |                 |
| 中型 | [200.genann][genann]         | 神经网络             | 仅含整数操作    |
|      | [201.jpeg][jpeg]             | JPEG解码             |                 |
|      | [202.llama2][llama2]         | 大语言模型           | 仅含整数操作    |
|      | [203.rsa][rsa]               | RSA加解密            |                 |


[blockchain]: https://github.com/aproxp/blockchain
[igemm]: https://github.com/iVishalr/GEMM
[queen]: https://github.com/NJU-ProjectN/am-kernels/tree/master/benchmarks/microbench
[dinic]: https://github.com/lab104yifan/ACM/blob/93daae9b997aa4df1af96d3140ad81b3506cee49/UVA10779.cpp
[malloc]: https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/umalloc.c
[bf]: http://github.com/kgabis/brainfuck-c
[qsort]: https://github.com/NJU-ProjectN/am-kernels/tree/master/benchmarks/microbench
[stream]: https://github.com/jeffhammond/STREAM
[ntt]: https://github.com/Nedal-haltam/NTT
[genann]: https://github.com/codeplea/genann
[jpeg]: https://github.com/nothings/stb/blob/master/stb_image.h
[llama2]: https://github.com/karpathy/llama2.c
[rsa]: https://github.com/pantaloons/RSA
