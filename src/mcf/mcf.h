#ifndef _MCF_H_
#define _MCF_H_

#include <klib.h>
#include <my_malloc.h>
#include <openlibm.h>



// #define MAX_DEGREE 40
#define DBL_MAX 1.7976931348623157e+308

// MCF: "max commodity flow"; MCMCF: "min-cost max concurrent flow"
typedef enum { MCF_TYPE = 0, MCMCF_TYPE = 1 }PROBLEM_TYPE;

////////////////////////////////////////////////////////////////////////////////
//
// NODE
//
////////////////////////////////////////////////////////////////////////////////

static inline int max(int a, int b){return b > a ? b : a;}

typedef struct 
{
   int id; // start from 0
   int x, y; // location coordinates directly in um; // 位置坐标直接在um中;
   int pre; // parent node in shortest path tree     // 最短路径树的父节点
   int pre_edge; // parent edge in shortest path tree   // 最短路径树中的父边
   double dist; // distance for shortest path algorithm // 最短路径算法的距离
   int no_comm; // number of destinations for commodities starting from this node  // 从该节点出发的商品目的地数量
   int *comms; // list of commodities starting from the node  // 从该节点开始的商品列表
   int no_edge; // number of edges incident to the node // 与节点关联的边数
   int *edges; // list of edges incident to the node // 与节点关联的边列表
   int dij_visited; // flag for Dijkstra algo  // Dijkstra 算法的标志
   int dij_updated; // second flag for Dijkstra algo // Dijkstra 算法的第二个标志
   int min_visited; // flag for searching min c(e)   // 搜索 min c(e) 的标志
   // _preferred_path has a number of elements equal to the number of 
   // commodities; each entry stores the next, downstream, node index
   // of the preferred unique path of the flow of this commodity from 
   // src toward des; this is constructed during the randomized rounding;
   // _preferred_path 的元素数量等于商品数量； 每个条目存储该商品从 src 到 des 的
   // 首选唯一路径的下一个下游节点索引； 这是在随机舍入期间构建的；
   int *_preferred_path;
}NODE;

////////////////////////////////////////////////////////////////////////////////
//
// EDGE
//
////////////////////////////////////////////////////////////////////////////////
typedef struct  
{
   int id; // start from 0
   int src, dest; // source and destination node id
   double latency; // delay of this edge; will play role of cost;   // 该边沿的延迟； 将发挥成本的作用；
   double length;
   // _flows has a number of elements equal to the number of demands/
   // commodities with the index being the id of demand;
   // _flows有与需求商品数量相等的元素，索引为需求的id；
   double *_flows;
   double flow; // accumulated total flow;  // 累计总流量；
   double capacity; // c_e 
   double left_capacity;
   // dual of capacity;
   // 容量的对偶；
   double _Y_e;
   double _old_Y_e;
}EDGE;

static inline void set_flow_of_commodity(EDGE *edge, int id, double flow) { edge->_flows[ id] = flow; }
static inline void add_to_flow_of_commodity(EDGE *edge,  int id, double val) { edge->_flows[ id] += val; }
static inline double flow_of_commodity(EDGE *edge,  int id) { return edge->_flows[ id]; }

////////////////////////////////////////////////////////////////////////////////
//
// COMMODITY
//
////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
   int id; // start from 0
   int src, dest; // source and destination 
   double demand;
   double left_demand;

}COMMODITY;

////////////////////////////////////////////////////////////////////////////////
//
// MCF acts as a host to the graph and methods such as Dijkstra and solver;
//
////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    // Note: "inherited" like this from the original code; I should
    // make them vectors;
    // 注意：从原始代码中这样“继承”； 我应该把它们做成矢量；
    int no_node;
    NODE *nodes;
    int no_edge;
    EDGE *edges;
    int no_cut;
    int no_commodity;
    COMMODITY *_commodities;

    // primal variables are the actual final flows through edges of graph;
    // their values are stored in _flows of EDGE class;
    // dual variable PHI_d; the other dual variables are Y_e
    // and the "length function" (see Ababei paper);
    // 原始变量是通过图边的实际最终流量； 它们的值存储在 EDGE 类的 _flows 中；
    //  双变量PHI_d； 其他对偶变量是 Y_e 和“长度函数”（参见 Ababei 论文）；
    double _phi_latency;
    // L is used to record the minimum latency achievable; utilized as
    // budget in the MCF problem formulation; found out via binary search;
    // L用于记录可实现的最小延迟； 用作 MCF 问题制定中的预算； 通过二分查找找到；
    double L, LL, UL; // L is latency budget; LL/UP is lower/upper latency;   // L 是延迟预算； LL/UP 是较低/较高延迟；

    // lambda_max is the first lambda that mcf() returns, with initial
    // latency_limit relaxed to 1000000 (inf);
    // lambda_max 是 mcf() 返回的第一个 lambda，初始 Latency_limit 放宽至 1000000 (inf)；
    double _lambda_max;
    double _latency_max; // associated with lambda_max;  // 与 lambda_max 关联；
    double _total_latency;

    // control variables;
    // 控制变量；
    double _delta;
    double _epsilon1;
    double _scale;
    // s = [P(lambda_max) - L]/[lambda_max - dual]; see eq. 9 of Hu
    // paper; used to implement "interval estimation";
    // s = [P(lambda_max) - L]/[lambda_max - 对偶]; 参考Hu的论文的例9； 用于实现“区间估计”；
    double _s;
    // temp_edge_flow stores how much flow is routed during an iteration;
    // it is a sketch array;
    // temp_edge_flow 存储迭代期间路由的流量； 它是一个草图数组；
    double *_temp_edge_flow;
    int _rd;
    int _min_rd;
    // arguments;
    PROBLEM_TYPE _problem_type;
    char _network_filename[512];
}MCF;

void MCF_init(MCF *mcf) ;

// utils;
static inline double flow_of_commodity_thru_edge(MCF *mcf, int c_id, int e_id) 
{
   //assert(c_id >= 0 && c_id < no_commodity);
   //assert(e_id >= 0 && e_id < no_edge);
   return flow_of_commodity(&mcf->edges[ e_id], c_id);
}
static inline double get_L(MCF *mcf) { return mcf->L; }
static inline int problem_type(MCF *mcf) { return mcf->_problem_type; }

// host;
void initialize(MCF *mcf, double delta, int flag);
bool parse_options(MCF *mcf, char *arg, float epsilon);
bool feasibility_check(MCF *mcf);
double compute_D(MCF *mcf);
double compute_alpha(MCF *mcf);
double compute_lambda(MCF *mcf);
void route_flow(MCF *mcf, int t, double amount, int commodity_id);
double check_latency_constraint(MCF *mcf, int t);
double min_capacity(MCF *mcf, int s);
double min_capacity_this_commodity(MCF *mcf, int dest);
void reset_left_capacities_in_tree(MCF *mcf, int s);
void update_dual_variables(MCF *mcf, int s, double epsilon, int flag);
double minimum(double x, double y, double z);
void scale_down_linear(MCF *mcf, float times);
void scale_down_flows(MCF *mcf, int phase_count);

// Dijkstra;
void shortest_paths(MCF *mcf, int s, int num_commodities, int *dest_flag);

// MCF solver;
void init_param(MCF *mcf);
int run_mcf_solver(MCF *mcf);
double mcf(MCF *mcf, double delta, double epsilon, int flag);
bool do_randomized_rounding(MCF *mcf);

// graph related utilities;
bool build_network_from_file(MCF *mcf, double latency_limit, double rate);
bool build_network_from_host_application(MCF *mcf);
void read_network_topology_and_demands(MCF *mcf, double rate);
void free_topology(MCF *mcf);
void print_network_demands(MCF *mcf, bool print_only_edges);
void print_backward_shortest_path(MCF *mcf, int t);
void print_routing_paths(MCF *mcf); 


#endif
