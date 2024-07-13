#include "test.h"

const int nodes_num   =     5;
const int edges_num   =     4;
const int demands_num =     5;

node_t node_buf[]={
	{    0,     0,     0,     1},
	{    1,     0,     0,     1},
	{    2,     0,     0,     1},
	{    3,     0,     0,     1},
	{    4,     0,     0,     1},
};

edge_t edge_buf[]={
	{    0,     0,     1,   144,   390},
	{    1,     1,     2,   153,   470},
	{    2,     2,     3,   147,   372},
	{    3,     3,     4,   156,    81},
};

demands_t demands_buf[]={
	{    0,     0,     4,    10},
	{    1,     0,     2,    96},
	{    2,     0,     3,    83},
	{    3,     1,     2,     8},
	{    4,     1,     4,    92},
};
