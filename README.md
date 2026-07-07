# ArchBench

## 编译方法

本项目依赖于[`abstract-machine`][am]或[`navy-apps`][navy]，需要提前设置`AM_HOME`或`NAVY_HOME`，具体方式请参考相应的仓库。

[am]: https://github.com/NJU-ProjectN/abstract-machine
[navy]: https://github.com/NJU-ProjectN/navy-apps

首先设置环境变量`BENCH_HOME`为当前目录：
```bash
export BENCH_HOME=`pwd`
```

同一组程序支持四种规模的输入：test，train，ref和huge。

| 名称  | 计分 | 建议使用场景  |
| ----- | ---- | ----- |
| test  |  X   | 正确性测试  |
| train |  O   | 在RTL仿真环境中研究微结构行为 |
| ref   |  O   | 在模拟器或FPGA环境中评估处理器性能 |
| huge  |  O   | 衡量高性能处理器(如真机)的性能 |

默认运行test数据规模，可通过`mainargs`选择其它的数据规模。

然后在相应程序的目录下编译并执行, 例如:
```bash
cd bench/000.hello
make ARCH=riscv32-nemu run   # 需要提前设置AM_HOME
make TARGET=x86_64-linux-gnu run mainargs=huge  # 需要提前设置NAVY_HOME
```

## 评分根据

每个benchmark都记录以`REF_CPU`为基础测得的运行时间微秒数。每个benchmark的评分是相对于`REF_CPU`的运行速度，与基准处理器一样快的得分为`REF_SCORE=1000000`。

## 并行评测脚本

本项目提供了一个并行评测脚本`scripts/run.sh`，当程序运行时间不受宿主机负载影响时（如RTL仿真），可考虑通过该脚本并行评测所有程序，如：
```bash
bash run.sh ARCH=riscv32e-npc mainargs=train
```
当程序运行时间受宿主机负载影响时（如模拟器或真机），可在使用单线程运行该脚本，如：
```bash
nproc=1 bash run.sh ARCH=native mainargs=huge
```

脚本最后还会统计所有benchmark得分的算术平均和几何平均。

可以通过设置`benchlist`变量来指定需要运行哪些benchmark。具体可参考`scripts/benchlist/all.sh`。

## 基准程序

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
|      | [204.hypergraph][hypergraph] | 超图划分             |                 |
| 大型 | [300.bzip3][bzip3]           | 数据压缩             |                 |
|      | [301.gsim][gsim]             | RTL仿真              |                 |
|      | [302.lua][lua]               | 脚本解释器           |                 |
|      | [303.cproc][cproc]           | C语言编译器          |                 |
|      | [304.mp3][mp3]               | MP3解码器            | 仅含整数操作    |
|      | [305.h264][h264]             | H264解码器           | 仅含整数操作    |


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
[hypergraph]: https://github.com/alidasdan/hypergraph-partitioning-algorithms
[bzip3]: https://github.com/iczelia/bzip3
[gsim]: https://github.com/OpenXiangShan/gsim
[lua]: https://github.com/lua/lua/tree/v5.3
[cproc]: https://github.com/michaelforney/cproc
[mp3]: https://github.com/ultraembedded/libhelix-mp3
[h264]: https://github.com/oneam/h264bsd
