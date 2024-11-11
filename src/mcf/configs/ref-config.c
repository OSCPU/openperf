#include "input.h"

const int nodes_num = 14;
const int edges_num = 25;
const int demands_num = 1;

node_t node_buf[] = {
    {0, 0, 0, 6},  {1, 0, 0, 1},  {2, 0, 0, 1},  {3, 0, 0, 1},  {4, 0, 0, 6},
    {5, 0, 0, 1},  {6, 0, 0, 1},  {7, 0, 0, 1},  {8, 0, 0, 2},  {9, 0, 0, 1},
    {10, 0, 0, 1}, {11, 0, 0, 2}, {12, 0, 0, 1}, {13, 0, 0, 1},
};

edge_t edge_buf[] = {
    {0, 0, 1, 101, 122},    {1, 1, 2, 179, 377},    {2, 2, 3, 124, 202},
    {3, 3, 4, 125, 261},    {4, 4, 5, 182, 423},    {5, 5, 6, 184, 405},
    {6, 6, 7, 140, 259},    {7, 7, 8, 118, 398},    {8, 8, 9, 128, 228},
    {9, 9, 10, 186, 238},   {10, 10, 11, 172, 236}, {11, 11, 12, 187, 350},
    {12, 12, 13, 163, 217}, {13, 0, 4, 180, 181},   {14, 0, 6, 5, 249},
    {15, 0, 7, 108, 427},   {16, 0, 12, 155, 139},  {17, 0, 8, 3, 322},
    {18, 4, 7, 106, 182},   {19, 4, 9, 81, 345},    {20, 4, 5, 212, 289},
    {21, 4, 6, 166, 419},   {22, 4, 10, 198, 30},   {23, 8, 12, 221, 308},
    {24, 11, 12, 179, 235},
};

demands_t demands_buf[] = {
    {0, 0, 13, 10},  {1, 0, 1, 96},   {2, 1, 6, 78},   {3, 1, 9, 95},
    {4, 3, 5, 35},   {5, 3, 10, 77},  {6, 3, 13, 38},  {7, 3, 9, 98},
    {8, 3, 11, 92},  {9, 3, 6, 29},   {10, 3, 4, 38},  {11, 4, 10, 73},
    {12, 4, 5, 6},   {13, 4, 12, 28}, {14, 4, 13, 4},  {15, 4, 8, 56},
    {16, 4, 9, 22},  {17, 4, 7, 48},  {18, 4, 6, 29},  {19, 5, 9, 35},
    {20, 5, 13, 39}, {21, 5, 12, 77}, {22, 5, 8, 42},  {23, 5, 10, 63},
    {24, 6, 12, 7},  {25, 6, 10, 25}, {26, 6, 11, 18}, {27, 6, 8, 29},
    {28, 6, 13, 36}, {29, 6, 9, 45},  {30, 7, 11, 36}, {31, 7, 13, 95},
    {32, 7, 12, 68}, {33, 7, 8, 33},  {34, 7, 10, 11}, {35, 8, 13, 82},
    {36, 8, 10, 7},  {37, 9, 10, 25}, {38, 9, 11, 84}, {39, 10, 13, 78},
};