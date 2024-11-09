#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
  struct timeval tv_start;
  int node_num = 10;
  int edge_num = 0;
  int demands_num = 1;

  gettimeofday(&tv_start, NULL);
  srand(tv_start.tv_usec);

  FILE *fp = fopen("test.c", "w");
  fprintf(fp,
          "#include \"input.h\"\n\n"); // 记录此时的偏移，最后需要打印三个变量
  int num_write = ftell(fp);
  int edge_num_write = 0;

  if (argv[1]) {
    node_num = atoi(argv[1]);
  }

  int edge_num_offset_buf[node_num]; // 记录每个节点的edge打印位置
  // ******************************************* 先来占位，最后再写入
  // ******************************************* //
  fprintf(fp, "const int nodes_num   = %5d;\n", 0);
  fprintf(fp, "const int edges_num   = %5d;\n", 0);
  fprintf(fp, "const int demands_num = %5d;\n\n", 0);
  // ******************************************* 生成结点
  // ******************************************* //
  fprintf(fp, "node_t node_buf[]={\n");
  for (int i = 0; i < node_num; i++) {
    fprintf(fp, "\t{%5d, %5d, %5d,", i, 0, 0);
    edge_num_offset_buf[i] = ftell(fp);
    fprintf(fp, " %5d},\n", 1);
  }
  fprintf(fp, "};\n\n");
  // ******************************************* 生成边
  // ******************************************* //
  edge_num = 0;
  fprintf(fp, "edge_t edge_buf[]={\n");
  for (int i = 0; i < node_num - 1;
       i++) // 初始化初始通路  ，初始通路必定能满足条件
  {
    int capacity = rand() % 99 + 100; // 容量
    int delay = rand() % 451 + 50;    // 花费
    fprintf(fp, "\t{%5d, %5d, %5d, %5d, %5d},\n", edge_num, i, i + 1, capacity,
            delay);
    edge_num++;
  }

  for (int start_node = 0; start_node < node_num - 1; start_node++) // 生成分支
  {
    int len2end = (node_num - 1) - start_node; // 到终点的距离
    int base = len2end > 7 ? 7 : len2end;
    int branch_num =
        (rand() % 4 == 1) ? rand() % base : 0; // 产生多少条分支，75%概率不生成
    int node_write[len2end]; // 计分表，保证通路不重复

    fseek(fp, edge_num_offset_buf[start_node], SEEK_SET);
    fprintf(fp, " %5d", branch_num + 1); // 一条原路与branch_num条支路
    fseek(fp, 0, SEEK_END);

    for (int i = 0; i < len2end; i++)
      node_write[i] = 0;

    for (int i = 0; i < branch_num; i++) // 分支，不保证能用
    {
      int capacity = rand() % 255 + 1; // 容量
      int delay = rand() % 500 + 1;    // 花费
      int end_node;
      do {
        end_node = rand() % (len2end - 1) + start_node + 1;
      } while (node_write[end_node - start_node - 1] == 1); // 只能向后生成
      node_write[end_node - start_node - 1] = 1; // 不能重复
      fprintf(fp, "\t{%5d, %5d, %5d, %5d, %5d},\n", edge_num, start_node,
              end_node, capacity, delay);
      edge_num++; // 输出完成后再加
    }
  }
  fprintf(fp, "};\n\n");
  // ******************************************* 生成目标
  // ******************************************* //

  fprintf(fp, "demands_t demands_buf[]={\n");
  fprintf(fp, "\t{%5d, %5d, %5d, %5d},\n", 0, 0, node_num - 1,
          10); // 打印第一个目标，该目标为固定值

  for (int start_node = 0; start_node < node_num - 1; start_node++) // 生成分支
  {
    int len2end = (node_num - 1) - start_node; // 到终点的距离
    int base = len2end > 15 ? 15 : len2end;
    int branch_num = rand() % base; // 该起点产生多少条需求
    int node_write[len2end];        // 计分表，保证通路不重复
    for (int i = 0; i < len2end; i++)
      node_write[i] = 0;

    for (int i = 0; i < branch_num; i++) // 开始生成
    {
      int demands = rand() % 100 + 1; // 需求容量
      int end_node;
      do {
        end_node = rand() % len2end + start_node + 1;
      } while (node_write[end_node - start_node - 1] == 1); // 只能向后生成
      node_write[end_node - start_node - 1] = 1; // 不能重复
      fprintf(fp, "\t{%5d, %5d, %5d, %5d},\n", demands_num, start_node,
              end_node, demands);
      demands_num++; // 输出完成后再加
    }
  }
  fprintf(fp, "};\n");

  // *******************************************
  // ******************************************* //
  fseek(fp, num_write, SEEK_SET);
  fprintf(fp, "const int nodes_num   = %5d;\n", node_num);
  fprintf(fp, "const int edges_num   = %5d;\n", edge_num);
  fprintf(fp, "const int demands_num = %5d;\n\n", demands_num);

  fclose(fp);
}
