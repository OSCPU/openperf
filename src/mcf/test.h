#ifndef __test_h__
#define __test_h__

extern const int nodes_num;
extern const int edges_num;
extern const int demands_num;

typedef struct{
    int id;     // node id
    int x,y;    // (x,y) location in um, location is not used currently for anything;
    int edge_num;
}node_t;

typedef struct{
    int id;    
    int src; 
    int des;
    double capacity;
    double delay;   
}edge_t;

typedef struct{
    int id;
    int src;
    int des;
    double amount;
}demands_t;

extern node_t node_buf[];
extern edge_t edge_buf[];
extern demands_t demands_buf[];

#endif