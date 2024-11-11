#include "input.h"

const int nodes_num = 4;
const int edges_num = 3;
const int demands_num = 4;

node_t node_buf[] = {
    {0, 0, 0, 1},
    {1, 0, 0, 1},
    {2, 0, 0, 1},
    {3, 0, 0, 1},
};

edge_t edge_buf[] = {
    {0, 0, 1, 121, 468},
    {1, 1, 2, 185, 328},
    {2, 2, 3, 141, 271},
};

demands_t demands_buf[] = {
    {0, 0, 3, 10},
    {1, 0, 3, 60},
    {2, 0, 1, 92},
    {3, 1, 2, 18},
};
