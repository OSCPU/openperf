#include <klib.h>
#include <printf.h>
#include <stdio.h>
#include "pqueue.h"
#include <mcf.h>
#include <test.h>


void MCF_init(MCF *mcf) 
{
   mcf->no_node = 0;
   mcf->no_edge = 0;
   mcf->no_commodity = 0;

   mcf->L=0; 
   mcf->LL=0; 
   mcf->UL=0;
   mcf->_phi_latency = 0;
   mcf->_lambda_max = 0;
   mcf->_latency_max = 0;
   mcf->_total_latency = 0;

   mcf->_delta = 1.0;
   mcf->_epsilon1 = 0.1;
   mcf->_scale = 1;
   mcf->_s = -1;
   mcf->_min_rd = 0;
   mcf->_rd = 0;
   mcf->_temp_edge_flow = 0;
   mcf->_problem_type = MCMCF_TYPE;
}

////////////////////////////////////////////////////////////////////////////////
//
// MCF host
//
////////////////////////////////////////////////////////////////////////////////

void initialize(MCF *mcf, double delta, int flag)
{
    // called each time mcf() is called;
    // 每次调用 mcf() 时都会调用；
    int i=0;

    // init dual variables
    // 初始化 dual 变量
    if (flag == 0) { // 0: "max concurrent flow"
        mcf->_phi_latency = 0.0;
    } else { // 1 "min-cost max concurrent flow"
        mcf->_phi_latency = delta / mcf->L; // dual variable PHI_d = 1/1000000
    }
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->edges[i]._Y_e = delta / mcf->edges[i].capacity;
        mcf->edges[i]._old_Y_e = mcf->edges[i]._Y_e;
    }
    // init edges
    for (i = 0; i < mcf->no_edge; i++) {
        mcf->edges[i].flow = 0.0;
        for (int j = 0; j < mcf->no_commodity; j++) {
            mcf->edges[i]._flows[ j] = 0.0;
        }
    }
    // reset edge flows
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->_temp_edge_flow[i] = 0.0;
    }   
    // init edge "length function" l(e)
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->edges[i].length = 0.0;
        mcf->edges[i].length += mcf->edges[i]._Y_e;
        mcf->edges[i].length += mcf->edges[i].latency * mcf->_phi_latency; // 0 for flag=0;
    }
    // init commodities
    for ( i = 0; i < mcf->no_commodity; i++) {
        mcf->_commodities[i].left_demand = mcf->_commodities[i].demand;
    }

    // reset _total_latency, which will be computed as the summation
    // of individual latencies from shortest-path trees for each source
    // of commodities;
    // 重置 _total_latency，它将被计算为每个商品来源的最短路径树的各个延迟的总和；
    mcf->_total_latency = 0.0;
}

bool parse_options(MCF *mcf, char *arg, float epsilon)
{
    // mcf->_problem_type = MCMCF_TYPE; // default;
    // mcf->_epsilon1 = 0.1; // default;

    if (strcmp(arg, "MCF") == 0) {
        mcf->_problem_type = MCF_TYPE;
    } 
    else if (strcmp(arg, "MCMCF") == 0) {
        mcf->_problem_type = MCMCF_TYPE;
    } else {
        my_printf("Error:  -problem_type must be MCF or MCMCF.\n");
        assert(0);
    }

    mcf->_epsilon1 = epsilon;
    if (mcf->_epsilon1 <= 0 || mcf->_epsilon1 >= 1) {
        my_printf("Error:  -epsilon option requires a float in (0,1).\n");
        assert(0);
    }

    return true;
}

void init_param(MCF *mcf)
{
    // called one time only from inside build_network_from_file() because
    // we need the number of edges of the graph for delta calculation;
    // () set latency budget to infinity (inf);
    // 仅从 build_network_from_file() 内部调用一次，因为我们需要图的边数来计算 delta；
    // () 将延迟预算设置为无穷大 (inf)；
    mcf->L = 1000000.0;
    // () epsilon is now set to default _epsilon1 = 0.1 inside parse_options();
    // or it could be set by user via command line argument;
    // () delta is set according to equation 3 from Karakostas paper;
    // () epsilon 现在在 parse_options() 中设置为默认 _epsilon1 = 0.1;
    // 或者可以由用户通过命令行参数设置；
    // () delta 根据 Karakostas 论文中的方程 3 设置；
    double epsilon = mcf->_epsilon1;
    mcf->_delta = (1/pow(1+epsilon, (1-epsilon)/epsilon))*(pow((1-epsilon)/mcf->no_edge, 1/epsilon));
    // () expected number of iterations (or phases) of the outer loop;
    // currently it is not used for any purpose;
    // () 外循环的预期迭代（或阶段）次数；
    // 目前它没有用于任何目的；
    mcf->_scale = log((1+epsilon)/mcf->_delta) / log(1+epsilon);
    //printf("\nepsilon=%e delta=%e _scale=%e\n",_epsilon1,_delta,_scale); // assert(0);
}

bool feasibility_check(MCF *mcf)
{
    // check and see if the routed flows violate capacities; if so,
    // then return false: no feasible solution; this is a "stretch";
    // feasibility should be checked differently;
    // 检查路由流是否违反容量； 如果是，则返回 false：无可行解； 这是一个“伸展”； 应以不同方式检查可行性；
    double threshold, violation;
    bool printed_warning = false;
    for ( int i = 0; i < mcf->no_edge; i++) {
        if (mcf->edges[i].flow > mcf->edges[i].capacity) {
            // consider only violations that are greater than 3 * epsilon;
            // 仅考虑大于 3 * epsilon 的违规；
            threshold = 3 * mcf->_epsilon1 * mcf->edges[i].capacity;
            violation = (mcf->edges[i].flow - mcf->edges[i].capacity);
            if ( violation > threshold) {
                return false;
            } else {
                // print once only a warning;
                // 仅打印一次警告；
                if ( !printed_warning) {
                    my_printf("\nWarning:  Some edges have capacity violation within 3*epsilon");
                    printed_warning = true;
                }
            }
        }
    }
    return true; // solution is ok;
}

double compute_D(MCF *mcf)
{
    // "D" is the numerator of dual=D/alpha; see section 6 of Garg paper;
    // “D”是dual=D/alpha的分子； 参见 Garg 论文第 6 节；
    double D = 0.0; 
    for ( int i = 0; i < mcf->no_edge; i++) {
        D += mcf->edges[i]._Y_e * mcf->edges[i].capacity;
    }
    D += mcf->L *mcf->_phi_latency;

    return D;
}

double compute_alpha(MCF *mcf)
{
    // "alpha" is the denuminator of dual=D/alpha; see section 6 of Garg paper;
    //“alpha”是dual=D/alpha的分母； 参见 Garg 论文第 6 节；
    int i, j;
    double alpha = 0.0; // to return;
    for ( i = 0; i < mcf->no_node; i++) {
        if ( mcf->nodes[i].no_comm) {
            int *dest_flag = (int*)bench_malloc((mcf->no_node)*sizeof(int));
            assert(dest_flag);
            if ( dest_flag == NULL) {
                printf("\nError: Unable to bench_malloc <getAlpha>.\n"); assert(0);
            }
            memset((void*)dest_flag,0,(mcf->no_node)*sizeof(int));
                
            for ( j = 0; j < mcf->nodes[i].no_comm; j++) {
                dest_flag[mcf->_commodities[mcf->nodes[i].comms[j]].dest] = 1;
            }
            
            shortest_paths(mcf, mcf->nodes[i].id, mcf->nodes[i].no_comm, dest_flag);
            mcf->_rd++;
            bench_free( dest_flag);

            for ( j = 0; j < mcf->nodes[i].no_comm; j++) {
                alpha += mcf->_commodities[mcf->nodes[i].comms[j]].demand * 
                    mcf->nodes[mcf->_commodities[mcf->nodes[i].comms[j]].dest].dist;
            }
        }
    }

    return alpha;
}

double compute_lambda(MCF *mcf)
{
    // compute lambda=MIN(actual flow/demand) among all commodities;
    // 计算所有商品中的 lambda=MIN(实际流量/需求);
    double lambda = DBL_MAX;

    for ( int comm_i = 0; comm_i < mcf->no_commodity; comm_i++) {
        // for each commodity we take its source node and look
        // at its outgoing edges to sum all flow pushed/routed 
        // for this commodity;
        // 对于每种商品，我们获取其源节点并查看其传出边缘，以总结该商品推送/路由的所有流量；
        int src_id = mcf->_commodities[comm_i].src; // source node;
        double routed_flow_this_commodity = 0.0;
        for ( int j = 0; j < mcf->nodes[src_id].no_edge; j++) {
            int edge_id = mcf->nodes[src_id].edges[j];
            routed_flow_this_commodity += mcf->edges[edge_id]._flows[ comm_i];
        }
        double this_lambda = routed_flow_this_commodity / mcf->_commodities[comm_i].demand;
        if ( this_lambda < lambda) {
            lambda = this_lambda;
        }
    }

    return lambda;
}

double check_latency_constraint(MCF *mcf, int dest)
{
    // this is L/c(P) in Fleischer paper (pp. 10), where
    // c(P) is is the cost of sending one unit of flow along
    // the shortest path: Sum_{e in P}{D(e)}, where D(e) is
    // latency of each edge along path;
    // 这是 Fleischer 论文（第 10 页）中的 L/c(P)，其中 c(P) 是沿最短路径发送
    // 一个单位流量的成本：Sum_{e in P}{D(e) }，其中 D(e) 是路径上每条边的延迟；
    int t = dest;
    double cost_to_send_unit_flow = 0.0; // along the shortest path to this dest;   // 沿着最短路径到达目的地；
    while ( mcf->nodes[t].pre != -1) {
        cost_to_send_unit_flow += mcf->edges[mcf->nodes[t].pre_edge].latency;
        t = mcf->nodes[t].pre;
    }
    
    return mcf->L/cost_to_send_unit_flow;
}

double min_capacity(MCF *mcf, int s) 
{
    // Note: currently not used;
    // find "c" as the minimum capacity of the edges on ALL
    // the paths in the shortest paths tree for this source node "s";
    // 注意：当前未使用；
    // 找到“c”作为源节点“s”的最短路径树中所有路径上边的最小容量；
    int t = 0;
    double min_capacity = 1000000.0;

    mcf->_min_rd++;
    // start from all dest nodes, traverse shortest path tree;
    // 从所有dest节点开始，遍历最短路径树；
    for ( int i = 0; i < mcf->nodes[s].no_comm; i++) {
        if ( mcf->_commodities[mcf->nodes[s].comms[i]].left_demand > 1e-3) {
            // pick up this destination and walk backward to sourse "s";
            // 选择这个目的地并向后走到源“s”；
            t = mcf->_commodities[mcf->nodes[s].comms[i]].dest;
            while ( (mcf->nodes[t].pre != -1) && (mcf->nodes[t].min_visited != mcf->_min_rd)) {
                int edge_id = mcf->nodes[t].pre_edge;
                mcf->nodes[t].min_visited = mcf->_min_rd;

                if (mcf->edges[edge_id].capacity < min_capacity) {
                    min_capacity = mcf->edges[edge_id].capacity;
                }
            }
        }
    }
    return min_capacity;
}

double min_capacity_this_commodity(MCF *mcf, int dest) 
{
    // find "c" as the minimum available capacity of the edges on 
    // the shortest path for this sink node "t";
    // 找到“c”作为该汇聚节点“t”的最短路径上边的最小可用容量；
    double min_avail_capacity = 1000000.0;

    int t = dest;
    while ( mcf->nodes[t].pre != -1) {
        int edge_id = mcf->nodes[t].pre_edge;
        if ( mcf->edges[edge_id].left_capacity < min_avail_capacity) {
            min_avail_capacity = mcf->edges[edge_id].left_capacity;
        }
        t = mcf->nodes[t].pre;
    }
    return min_avail_capacity;
}

void reset_left_capacities_in_tree(MCF *mcf, int s)
{
    // reset left_capacities of edges in the shortest paths tree to the
    // initial capacities; u'(e)=u(e), for any e in tree;
    // 将最短路径树中边的 left_capacities 重置为初始容量； u'(e)=u(e)，对于树中的任何 e；
    int t = 0;
    // start from all dest nodes, traverse shortest path tree;
    // 从所有dest节点开始，遍历最短路径树；
    for ( int i = 0; i < mcf->nodes[s].no_comm; i++) {
        if ( mcf->_commodities[mcf->nodes[s].comms[i]].left_demand > 1e-3) {
            // pick up this destination and walk backward to sourse "s";
            // 选择这个目的地并向后走到源“s”；
            t = mcf->_commodities[mcf->nodes[s].comms[i]].dest;
            while ( mcf->nodes[t].pre != -1) {
                int edge_id = mcf->nodes[t].pre_edge;
                mcf->edges[edge_id].left_capacity = mcf->edges[edge_id].capacity;
                t = mcf->nodes[t].pre;
            }
        }
    }
}

void route_flow(MCF *mcf, int t, double routed_amount, int commodity_id)
{
    // t is destination to which we route "amount" of commodity;
    // t 是我们将“数量”的商品路由到的目的地；
    while ( mcf->nodes[t].pre != -1) {
        int edge_id = mcf->nodes[t].pre_edge;
        mcf->_temp_edge_flow[edge_id] += routed_amount;
        mcf->edges[edge_id].left_capacity -= routed_amount;
        
        // record this routed_amount for this commodity id on the 
        // corresponding edge also;
        // 在对应的边上也记录该商品id的routed_amount；
        assert(commodity_id >= 0 && commodity_id < mcf->no_commodity);
        mcf->edges[ edge_id]._flows[ commodity_id] += routed_amount;

        t = mcf->nodes[t].pre;
    }
    return;
}

void update_dual_variables(MCF *mcf, int s, double epsilon, int flag)
{
    // update dual variables; compute l_i_j_s(e), where
    // "j" is jth iteration of phase "i", and "s" is the current step;
    // 更新 dual 变量； 计算 l_i_j_s(e)，其中“j”是阶段“i”的第 j 次迭代，“s”是当前步骤；
    int i, t;
    double old_phi_latency;
    double temp_latency = 0.0;

    // (1) accumulate temp_latency along the shortest paths for the
    // shortest paths tree for the commodities of this source node;
    // (1) 沿着该源节点商品的最短路径树的最短路径累积temp_latency；
    mcf->_min_rd++;
    for ( i = 0; i < mcf->nodes[s].no_comm; i++) {
        t = mcf->_commodities[mcf->nodes[s].comms[i]].dest;
        while ( (mcf->nodes[t].pre != -1) && (mcf->nodes[t].min_visited != mcf->_min_rd)) {
            int edge_id = mcf->nodes[t].pre_edge;
            mcf->nodes[t].min_visited = mcf->_min_rd;
            
            temp_latency += mcf->_temp_edge_flow[edge_id] * mcf->edges[edge_id].latency;

            // update the dual variable Y_e;
            // 更新 dual 变量 Y_e;
            mcf->edges[edge_id]._old_Y_e = mcf->edges[edge_id]._Y_e;
            // Note: _temp_edge_flow[edge_id] represents the amount of total
            // flow of all commodities that have the same source "s", which is
            // pushed thru this edge during this step "s";
            // 注：_temp_edge_flow[edge_id]表示在本步骤“s”中通过该边推送的具有相同来源“s”的所有商品的总流量；
            mcf->edges[edge_id]._Y_e *= 
                (1 + epsilon * mcf->_temp_edge_flow[edge_id] / mcf->edges[edge_id].capacity);

            // walk upstream on shortest path;
            // 沿最短路径逆流而上；
            t = mcf->nodes[t].pre;
        }
    }
    mcf->_min_rd++;
    // record latency contributed due to total flow pushed thru during
    // this step "s";
    // 记录由于在此步骤“s”期间推送的总流量而造成的延迟；
    mcf->_total_latency += temp_latency;

    // (2) update additional dual variable PHI_d;
    old_phi_latency = mcf->_phi_latency;
    mcf->_phi_latency *= (1 + epsilon * temp_latency / mcf->L); // adjust value from prev. iter;

    // (3) update the "length function";
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->edges[i].length += (mcf->edges[i]._Y_e - mcf->edges[i]._old_Y_e);
        // the above length function is enough for "max concurrent flow" problem;
        // howver, if we solve "min-cost max concurrent flow", then, we must add
        // more to the length function;
        // 上面的长度函数足以解决“最大并发流”问题； 然而，如果我们解决“最小成本最大并发流”，那么，我们必须在长度函数上添加更多；
        if ( flag != 0) { // 1
            mcf->edges[i].length += mcf->edges[i].latency * (mcf->_phi_latency - old_phi_latency);
        }
    }

    // (4) add to the flow recorded for each edge the accumulated 
    // amounts (as sum of f_{i,j,s}^{c_q}) for each commodity routed during
    // this iteration, amounts which are reflected by _temp_edge_flow (which
    // has values != zero) for edges of shortest path of this iter;
    // (4) 将本次迭代期间路由的每种商品的累计金额（作为 f_{i,j,s}^{c_q} 的总和）添加到为每条边
    // 记录的流中，这些金额由 _temp_edge_flow 反映（其中有 值！=零）用于此迭代器的最短路径的边缘；
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->edges[i].flow += mcf->_temp_edge_flow[i];
    }

    // (5) reset temp storage of pushed flow during this iter; prepare it
    // for the next push/iteration;
    // (5) 在迭代期间重置推送流的临时存储； 为下一次推送/迭代做好准备；
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->_temp_edge_flow[i] = 0.0;
    }

    return;
}

void scale_down_linear(MCF *mcf, float times) 
{
    // Note: currently not used;
    // 注意：当前未使用；
    for ( int i = 0; i < mcf->no_edge; i++) {
        mcf->edges[i].length /= times;
        mcf->edges[i]._Y_e /= times;
    }
    mcf->_phi_latency /= times;
    return;
}

void scale_down_flows(MCF *mcf, int phase_count)
{
    // scale down final solution; basically averaging over the number 
    // of phases (iterations of the main big loop of mcf);
    // 缩小最终解决方案； 基本上对阶段数进行平均（MCF 主大循环的迭代）；
    int scale = max( 1, phase_count); // this is "t";
    for ( int i = 0; i < mcf->no_edge; i ++) {
        mcf->edges[i].flow /= scale;
        for ( int j = 0; j < mcf->no_commodity; j ++) {
            mcf->edges[i]._flows[ j] /= scale;
        }
    }
}

double minimum(double x, double y, double z) 
{
    double min;
    if ( x < y) {
        if ( x < z) min = x;
        else min = z;
    } else {
        if ( y < z) min = y;
        else min = z;
    }
    return min;
}

////////////////////////////////////////////////////////////////////////////////
//
// MCF actual solver
//
////////////////////////////////////////////////////////////////////////////////

int run_mcf_solver(MCF *mcf_v)
{
    // it is assumed that the network was already created from file
    // or host application;
    // 假设网络已经从文件或主机应用程序创建；

    // (1) first, run of MCF solver with the latency constraint
    // relaxed to infinity L=1000000 (inf); this is basically
    // the "max commodity flow" problem;
    // Reminder on MCF flavors:
    // -- "max multicommodity flow": total flow summed over all commodities
    //    is to be maximized;
    // -- "max concurrent flow": each commodity si,ti has a demand di; 
    //    objective is to maximize the fraction of the demand that can be shipped
    //    simultaneously for all commodities;
    // -- "min-cost max concurrent flow";
    // (1) 首先，运行 MCF 求解器，延迟约束放宽至无穷大 L=1000000 (inf)； 这基本上是“最大商品流量”问题；
    // 关于MCF特点的提醒：
    // -- “最大多种商品流量”：所有商品的总流量要最大化；
    // -- “最大并发流量”：每种商品si,ti都有需求di； 目标是最大化所有商品可同时运输的需求比例；
    // -- “最小成本最大并发流”;

    // printf("\nPART 1 - MAX CONCURRENT FLOW (MCF):");

    // flag=0 means that this is a "max commodity flow" run; there is
    // no latency constraint/budget;
    // flag=0 表示这是一次“最大商品流量”运行； 没有延迟限制/预算；
    mcf_v->_lambda_max = mcf(mcf_v, mcf_v->_delta, mcf_v->_epsilon1, 0); // flag=0;
    //print_network_demands(true); // assert(0); // debug;

    // early exit if there is no "feasible" solution;
    // 如果没有“可行”的解决方案，则提前退出；
    if ( feasibility_check(mcf_v) == false) {
        my_printf("\nWarning: No feasible solution; some edges have capacity ");
        my_printf("\n         violation greater than 3*epsilon.\n");
        free_topology(mcf_v);
        assert(0);
    }

    // Note: at this time we could simply stop is we were not interested
    // in solving this problem such that the minimum latency is also achieved;
    // the minimum latency (stored in L) is found via binary search by
    // solving repeatedly the so called "min-cost max concurrent flow" problem;
    // also note that the solution we have now is most likely different
    // from the solution we'll have after the binary search;
    // so, if user wants a solution for the problem "max commodity flow" only,
    // then stop here;
    // 注意：此时我们可以简单地停止，因为我们对解决这个问题不感兴趣，这样也可以实现最小延迟；
    // 通过重复解决所谓的“最小成本最大并发流”问题，通过二分搜索找到最小延迟（存储在 L 中； 
    // 另请注意，我们现在的解决方案很可能与二分搜索后的解决方案不同；
    // 所以，如果用户只想解决“最大商品流量”问题，那么就到此为止；
    if (mcf_v->_problem_type == MCF_TYPE) {
        return 1;
    }


    // (2) second, "improved" binary search to refine L; basically we look 
    // for the minimum latency achievable; during this search mcf is run with 
    // flag=1, that is as a "min-cost max concurrent flow";
    // (2) 第二，“改进”二分查找以细化 L； 基本上我们寻找可实现的最小延迟； 
    // 在此搜索期间，mcf 以 flag=1 运行，即作为“最小成本最大并发流”；
    // printf("\n\nPART 2 - BINARY SEARCH FOR L - MIN-COST MAX CONCURRENT FLOW (MCMCF):");
    // maximum latency is as resulted after finding the solution of the
    // "max multicommodity flow" problem from PART 1;
    // 最大延迟是从第 1 部分找到“最大多种商品流”问题的解后的结果；
    mcf_v->_latency_max = mcf_v->_total_latency; // Hu: 1000000;
    mcf_v->LL = 0;
    mcf_v->UL = mcf_v->_total_latency; // Hu: _latency_max/_lambda_max;
    mcf_v->_s = -1;

    int counter = 0;
    while ( (mcf_v->UL - mcf_v->LL)/mcf_v->LL > 0.1) {
        // (a) set Latency as the middle point between LL and UL;
        // (a) 将 Latency 设置为 LL 和 UL 之间的中间点；
        mcf_v->L = (mcf_v->LL + mcf_v->UL) / 2;
        // (b) this call of MCF modifies LL and UL using the 
        // "interval estimation" technique proposed in Hu paper;
        // (b) MCF 的调用使用 Hu 论文中提出的“间隔估计”技术修改 LL 和 UL；
        mcf(mcf_v, mcf_v->_delta, mcf_v->_epsilon1, 1); // flag=1;

        // (c) now, if anything goes wrong for some pathological testcase, 
        // have a brutal exit; this will require debugging;
        // (c) 现在，如果某个病态测试用例出现任何问题，请残酷退出； 这将需要调试；
        counter++;
        if ( counter >= 512) {
            my_printf("\nError:  Binary search of MCMCF took more than 512 iterations.");
            my_printf("\n        This is an unusual testcase or the code has a bug.\n");
            free_topology(mcf_v);
            assert(0);
        }   
    }
    
    //printf("\nLL=%lf, UL=%lf", LL, UL);
    //printf("\nFinal latency L=%lf\n", UL);
    return 1;
}

double mcf(MCF *mcf_v, double delta, double epsilon, int flag)
{
    // flag:
    // 0 -- max concurrent flow;
    // 1 -- min-cost max concurrent flow;
    // 标志：
    // 0 -- 最大并发流量；
    // 1 -- 最小成本最大并发流；

    int i,j;
    int iter=0; // phase counter: number of iterations of the big main loop;    // 阶段计数器：大主循环的迭代次数；
    double lambda=1; // result to be returned;  // 返回结果；
    double D=1, alpha=1, dual=1;
    // used to find the amount of flow pushed in each step; // 用于查找每一步推入的流量；
    double usable_amount_cap, usable_amount_latency, routed_amount;
    // for tracking gap between lambda and dual;    // 用于跟踪 lambda 和对偶之间的差距；
    // double gap=0.0;
    // double old_gap=0.0; 
    // double old_old_gap=0.0;


    // () initialization of primal variables (i.e., flows thru all edges)
    // and dual valiables PHI_d, Y_e and "length function" l(e)
    // of all edges; also resets left_demand to demand for all commodities
    // as well as _total_latency;
    // () 初始化原始变量（即流经所有边）和对偶变量 PHI_d、Y_e 和所有边的“长度函数”l(e)；
    // 还将 left_demand 重置为所有商品的需求以及 _total_latency；
    initialize(mcf_v, delta, flag);
    mcf_v->_rd = 1;
    for ( i = 0; i < mcf_v->no_node; i++) {
        mcf_v->nodes[i].dij_visited = 0;
        mcf_v->nodes[i].dij_updated = 0;
        mcf_v->nodes[i].min_visited = 0;
    }
    

    // () the big loop, each run of this loop is a phase; each phase
    // has |S| iterations;
    // () 大循环，这个循环的每次运行都是一个阶段； 每个相都有|S| 迭代；
    while (1) {

        // () in every phase we start with the demand d_j for every commodity;
        // () 在每个阶段，我们都从每种商品的需求 d_j 开始；
        for ( j = 0; j < mcf_v->no_commodity; j++) {
            mcf_v->_commodities[j].left_demand = mcf_v->_commodities[j].demand;
        }
    

        // () next there are |S| iterations, one for each node that is a 
        // source for at least a commodity;
        // () 接下来是 |S| 迭代，每个节点迭代一次，该节点至少是一种商品的来源；
        for ( i = 0; i < mcf_v->no_node; i++) {
            if ( mcf_v->nodes[i].no_comm) { // if this node is source of "r" _commodities; // 如果该节点是“r”_commodities 的来源；
                
                int commodities_left = mcf_v->nodes[i].no_comm;
                int *dest_flag = (int*)bench_malloc((mcf_v->no_node)*sizeof(int));
                if ( dest_flag == NULL) {
                    my_printf("\nError:  Unable to bench_malloc <mcf>.\n"); assert(0);
                }
                memset((void*)dest_flag,0,(mcf_v->no_node)*sizeof(int));
                // dest_flag is set "1" for nodes that are destinations of _commodities;
                // 对于作为 _commodities 目的地的节点，dest_flag 设置为“1”；
                for ( j = 0; j < mcf_v->nodes[i].no_comm; j++) {
                    dest_flag[mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest] = 1;
                }


                // while there are left commodities to be routed for this node; 
                // there are a number of steps for current iteration;
                // 当该节点还有剩余商品需要发送时； 当前迭代有多个步骤；
                int step_count = 0;
                while ( commodities_left) {
                    step_count ++;

                    // () compute shortest PATHS tree, where edges have "length(e)";
                    // of all paths from this sink to all its destinations;
                    // () 计算最短路径树，其中边具有“length(e)”； 从该接收器到其所有目的地的所有路径；
                    //print_network_demands( true); // debug;
                    shortest_paths(mcf_v, mcf_v->nodes[i].id, commodities_left, dest_flag);
                    
                    // () reset left_capacities of edges in the tree to the
                    // initial capacities; u'(e) = u(e), any e in tree;
                    // () 将树中边的 left_capacities 重置为初始容量； u'(e) = u(e)，树中的任意 e；
                    reset_left_capacities_in_tree(mcf_v, mcf_v->nodes[i].id);

                    // () route "f = d(c_q)" units of flow of a given commodity
                    // and update the flow of each edge: f_e = f_e + f, along its 
                    // shortest path;
                    // () 路由给定商品的“f = d(c_q)”单位流量并更新每条边的流量：f_e = f_e + f，沿其最短路径；
                    bool flow_has_been_routed = false;
                    for ( j = 0; j < mcf_v->nodes[i].no_comm; j++) {

                        // the amount of commodity c_q that has not been routed yet
                        // at step "s";
                        // 在步骤“s”尚未路由的商品 c_q 的数量；
                        double left_demand = mcf_v->_commodities[mcf_v->nodes[i].comms[j]].left_demand;

                        if ( left_demand > 1e-3) {
                            flow_has_been_routed = true;
                            //print_backward_shortest_path(_commodities[nodes[i].comms[j]].dest);


                            // available flow amount from bottleneck-edge of shortest path;
                            // this "c" represents the available minimum capacity of the
                            // edges on shortest path of this commodity;
                            // 最短路径瓶颈边缘的可用流量； 这个“c”代表该商品最短路径上边的可用最小容量；
                            usable_amount_cap = min_capacity_this_commodity(mcf_v, mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest);
                                                                            

                            // available flow amount from latency constraint
                            // 延迟约束下的可用流量
                            if ( flag == 0) { // 0: "max concurrent flow"   // 0: “最大并发流量”
                                usable_amount_latency = 1000000.0; // inf;
                            } else { // 1: "min-cost max concurrent flow"   // 1: “最小成本最大并发流”
                                // this is L/c(P), where c(P) is is the cost of sending 
                                // one unit of flow along the shortest path:
                                // Sum_{e in P}{D(e)}, where D(e) is latency of each edge;
                                // 这是 L/c(P)，其中 c(P) 是沿最短路径发送一个单位流量的成本：
                                // Sum_{e in P}{D(e)}，其中 D(e) 是 每个边缘的延迟；
                                usable_amount_latency = check_latency_constraint(mcf_v, mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest);
                                                                                 
                            }
                            
                            // flow amount to be routed at step "s": f_{i,j,s}^{c_q};
                            // 在步骤“s”路由的流量：f_{i,j,s}^{c_q};
                            routed_amount = minimum(usable_amount_cap, left_demand, usable_amount_latency);
                            
                                                    

                            // update every "_temp_edge_flow" - from dest backward to src
                            // will be added routed_amount; also update left_capacities
                            // of edges along the shortest path of this commodity;
                            // 更新每个“_temp_edge_flow” - 从dest向后到src将添加routed_amount; 
                            // 还更新该商品沿最短路径的边的 left_capacities；
                            route_flow(mcf_v, mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest,
                                        routed_amount, mcf_v->nodes[i].comms[j]);

                            // update commodity amounts to be routed still (i.e., are left);
                            // 更新仍要传送的商品数量（即剩余的数量）；
                            mcf_v->_commodities[mcf_v->nodes[i].comms[j]].left_demand -= routed_amount;

                            if (mcf_v->_commodities[mcf_v->nodes[i].comms[j]].left_demand <= 1e-3) {
                                // this commodity is done, set its destination flag to 0;
                                // 该商品已完成，将其目的地标志设置为 0;
                                commodities_left --;
                                dest_flag[mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest] = 0;
                            }
                        }
                    }//for ( j = 0; j < nodes[i].no_comm; j++)

                    // () update dual variables: Y_e, phi_latency (or PHI_d), 
                    // () 更新 dual 变量：Y_e、phi_latency（或 PHI_d）、
                    // length(e);
                    update_dual_variables(mcf_v, mcf_v->nodes[i].id, epsilon, flag);

                    mcf_v->_rd++;
                    if ( !flow_has_been_routed) break;
                }//while ( commodities_left)


                bench_free( dest_flag);

            }//if ( nodes[i].no_comm)
        }//for ( i = 0; i < no_node; i++)


        // () increment phase counter; a phase is an iteration of the big main loop;
        // () 递增相位计数器； 阶段是大主循环的迭代；
        iter++;
        // additional stopping criterion;
        // 附加停止标准；
        if ( iter >= mcf_v->_scale) break;
        //if ( iter >= 80) break;

        // () compute dual and lambda and keep track of the gap between them;
        // -- compute dual=D/alpha;
        // () 计算 dual 和 lambda 并跟踪它们之间的差距；
        // -- 计算 dual=D/alpha;
        D = compute_D(mcf_v);
        alpha = compute_alpha(mcf_v);
        dual = D / alpha;

        // -- compute lambda;
        // Note1: the original code of Hu computed lambda differently;
        // this is not in fact lambda in the sense of Karakostas paper,
        // but rather an "artificial" variable to make easier its tracking
        // towards a value of 1;
        //lambda = L / (_total_latency/iter);
        // Note2: I now compute it as: lambda=MIN(actual flow/demand) among all commodities;
        // -- 计算 lambda;
        // 注1：Hu的原始代码计算lambda的方式不同； 这实际上不是 Karakostas 论文意义上的 lambda，而是一个“人工”变量，以便更容易地跟踪值 1；
        // lambda = L / (_total_latency/iter);
        // 注2：我现在计算为：所有商品中lambda=MIN(实际流量/需求)；
        lambda = compute_lambda(mcf_v);
        lambda /= iter; // consider effect of scaling;
        //printf("\n Lambda=%.8f, Dual=D/alpha=%.8f, D=%.8f",lambda,dual,D);
        
        // -- keep track of gap;
        // -- 跟踪gap；
        // old_old_gap = old_gap;
        // old_gap = gap;
        // gap = dual/lambda - 1;

         
        // () this implements the "interval estimation"; see Theorem 3 of Hu paper;
        // () 这实现了“区间估计”； 参见Hu论文的定理3；
        if ( flag == 1) {
            double UL1 = mcf_v->UL, LL1 = mcf_v->LL;
            double d = dual;
            //if (d < 1) d = 1;
            double s1 = (mcf_v->_latency_max - mcf_v->L)/(mcf_v->_lambda_max - d);
            if ( s1 > 0 && (mcf_v->_s < 0 || mcf_v->_s > s1)) { 
                mcf_v->_s = s1; 
            }
            if ( mcf_v->_s > 0) {
                if ( lambda < 1) {
                    UL1 = mcf_v->L + (1 - lambda) * mcf_v->_s;
                    if ( UL1 < mcf_v->UL) mcf_v->UL = UL1;
                }
                if ( dual > 1) {
                    LL1 = mcf_v->L - (dual - 1) * mcf_v->_s;
                    if ( LL1 > mcf_v->LL) mcf_v->LL = LL1;
                }
            }
            if ( lambda > 1) { mcf_v->UL = mcf_v->L; }
            if ( dual < 1) { mcf_v->LL = mcf_v->L; }
            if ( (mcf_v->UL-mcf_v->LL < 0) || (mcf_v->UL/mcf_v->LL - 1) < 0.01) { break; }
            if ( D >= 1) { break; }
        } else { // 0
            // for "max commodity flow" case, the stopping criterion is 
            // "D>=1"; see Karakostas paper;
            // Note1: original code of Hu used "dual/lambda-1<epsilon1";
            // 对于“最大商品流量”情况，停止标准为“D>=1”； 参见 Karakostas 论文； 
            // 注1：Hu的原始代码使用“dual/lambda-1<epsilon 1”；
            if ( D >= 1) { break; }
        }
    
    }//while (1)


    // () scale down the final flows so that the solution is feasible 
    // (that is, capacities are met);
    // () 缩小最终流量，使解决方案可行（即满足容量要求）；
    scale_down_flows(mcf_v, iter);
    // also, record final latency, which must consider scaling too;
    // 另外，记录最终延迟，这也必须考虑扩展；
    mcf_v->_total_latency = mcf_v->_total_latency / iter;

    
    // () entertain user;
    // printf("\nlambda = %lf, dual = %lf, [%lf, %lf], L=%lf, iter=%d",
    //        lambda, D/alpha, mcf_v->LL, mcf_v->UL, mcf_v->L, iter);

    return lambda;
}

////////////////////////////////////////////////////////////////////////////////
//
// MCF Dijkstra
//
////////////////////////////////////////////////////////////////////////////////

void shortest_paths(MCF *mcf_v, int s, int num_commodities, int *dest_flag) 
{
    // implements Dijkstra's all paths shortest path algorithm;
    // num_commodities is the number of commodities that still need
    // routing for this source; 
    // 实现Dijkstra的所有路径最短路径算法； num_commodities 是该来源仍需要路由的商品数量；

    int num_commodities_to_process = num_commodities;
    PQDATUM wf, wf1; // WAVEFRONTS;
    PQDATUM_init(&wf);
    PQDATUM_init(&wf1);

    PQUEUE pq;
    PQUEUE_init(&pq);
    int *pos = (int *)bench_malloc(sizeof(int) * (mcf_v->no_node));
    if ( pos == NULL) {
        my_printf("\nError: Unable to bench_malloc <shortest_path>.\n"); assert(0);
    }
    
    pqinit(&pq, 400); // 400 is just a constant; // 400只是一个常数；
    // reset dist of all nodes;
    // 重置所有节点的距离；
    for ( int i = 0; i < mcf_v->no_node; i++) {
        mcf_v->nodes[i].dist = DBL_MAX;
    }
    // source "s" resets;
    // 源“s”重置；
    mcf_v->nodes[s].pre = -1;
    mcf_v->nodes[s].pre_edge = -1;
    mcf_v->nodes[s].dist = 0.0;

    set_node(&wf, s); // sourse "s";
    set_dist(&wf, 0.0);

    pqinsert(&pq, wf, pos);

    while ( !pqempty(&pq)) {
        int v, w;
        
        // retreive the shortest non-visited node;
        // 检索最短的未访问节点；
        pqremove(&pq, &wf1, pos);
        v = node(&wf1);
        if ( dest_flag[v]) num_commodities_to_process--;
        // break when all shortest paths to all destinations from source "s"
        // have been found;
        // 当找到从源“s”到所有目的地的所有最短路径时中断；
        if ( num_commodities_to_process <= 0) break;
        
        mcf_v->nodes[v].dij_visited = mcf_v->_rd;
        for ( int i = 0; i < mcf_v->nodes[v].no_edge; i++) {
            w = mcf_v->edges[mcf_v->nodes[v].edges[i]].dest;
            if (mcf_v->nodes[w].dij_visited != mcf_v->_rd)
                if (mcf_v->nodes[w].dij_updated != mcf_v->_rd ||
                    mcf_v->nodes[w].dist > dist(&wf1) + mcf_v->edges[mcf_v->nodes[v].edges[i]].length) {
                    mcf_v->nodes[w].pre = v;
                    mcf_v->nodes[w].pre_edge = mcf_v->nodes[v].edges[i];
                    mcf_v->nodes[w].dist = dist(&wf1) + mcf_v->edges[mcf_v->nodes[v].edges[i]].length;
                    set_node(&wf, w);
                    set_dist(&wf, mcf_v->nodes[w].dist);
                    if (mcf_v->nodes[w].dij_updated != mcf_v->_rd) {
                        pqinsert(&pq, wf, pos);
                    } else {
                        pqdeckey(&pq, wf, pos);
                    }
                    mcf_v->nodes[w].dij_updated = mcf_v->_rd;
                }
        }
    }
    pqfree(&pq, pos); // clean up;
}

////////////////////////////////////////////////////////////////////////////////
//
// MCF network graph
//
////////////////////////////////////////////////////////////////////////////////

bool build_network_from_host_application(MCF *mcf_v)
{
    // used from inside the host application that hosts also the floorplanner
    // and the VNOC1 NoC simulator;
    // you should implement this based on how your host application looks like;
    // the idea is to populate the MCF object similarly to how I do it inside
    // read_network_topology_and_demands();
    // 从还托管布局规划器和 VNOC1 NoC 模拟器的主机应用程序内部使用； 
    // 您应该根据主机应用程序的外观来实现这一点； 
    // 这个想法是填充 MCF 对象，类似于我在 read_network_topology_and_demands() 中的操作方式；

    return true;
}

bool build_network_from_file(MCF *mcf_v, double latency_limit, double rate)
{
    // rate is the demand coefficient (injection rate): 0.05, 0.1, 0.15, 0.2, 0.25;
    // latency_limit and rate are not used;
    // rate为需求系数（注入率）：0.05, 0.1, 0.15, 0.2, 0.25;
    // 不使用latency_limit和rate；

    // (1) import the network topology and the demands;
    // (1)导入网络拓扑和需求；
    read_network_topology_and_demands(mcf_v, 1);

    // (3) one time initialization of parameters (of those not set by
    // user via command line arguments);
    // (3) 一次性初始化参数（用户未通过命令行参数设置的参数）;
    init_param(mcf_v);

    return true;
}

int demands_select = 0;

void read_network_topology_and_demands(MCF *mcf_v, double rate) 
{
    int id, x, y, src, dest;
    double delay, capacity;

    // (1) nodes
    mcf_v->no_node = nodes_num;
    mcf_v->nodes = (NODE*)bench_malloc(sizeof(NODE) * (mcf_v->no_node));
    if ( mcf_v->nodes == NULL) {
        my_printf("\nError: Unable to bench_malloc <nodes>.\n"); assert(0);
    }
    for ( int i = 0; i < mcf_v->no_node; i++) {
        id = node_buf[i].id;
        x  = node_buf[i].x;
        y  = node_buf[i].y;

        mcf_v->nodes[i].id = id;
        mcf_v->nodes[i].x = x;
        mcf_v->nodes[i].y = y;
        mcf_v->nodes[i].pre = -1;
        mcf_v->nodes[i].dist = DBL_MAX;
        mcf_v->nodes[i].no_comm = 0;
        mcf_v->nodes[i].comms = NULL;
        mcf_v->nodes[i].no_edge = 0;
        mcf_v->nodes[i].dij_visited = 0;
        mcf_v->nodes[i].dij_updated = 0;
        mcf_v->nodes[i].min_visited = 0;

        // here we work with a fixed pre-allocation; not optimal; we should
        // allocate only as much as needed; also in this way we have to make
        // sure there will be no nodes with a bigger degree than MAX_DEGREE=40;
        // TO DO: this must be fixed as it's ugly programming;
        // 这里我们使用固定的预分配；不是最佳的；我们应该只根据需要分配；同样，我们必须确保不会有度数大于 MAX_DEGREE=40 的节点；
        // 要做的事：必须修复这个问题，因为它是丑陋的编程；
        // mcf_v->nodes[i].edges = (int *)bench_malloc(sizeof(int) * MAX_DEGREE);
        mcf_v->nodes[i].edges = (int *)bench_malloc(sizeof(int) * node_buf[i].edge_num);
        assert(mcf_v->nodes[i].edges);
        if ( mcf_v->nodes[i].edges == NULL) {
            my_printf("\nError: Unable to bench_malloc <nodes.edges>.\n"); assert(0);
        }
    }

    // (2) edges
    mcf_v->no_edge = edges_num;
    mcf_v->edges = (EDGE *)bench_malloc(sizeof(EDGE) * (mcf_v->no_edge));
    if ( mcf_v->edges == NULL) {
        my_printf("\nError: Unable to bench_malloc <edges>.\n"); assert(0);
    }
    mcf_v->_temp_edge_flow = (double*)bench_malloc(sizeof(double) * (mcf_v->no_edge));
    if ( mcf_v->_temp_edge_flow == NULL) {
        my_printf("\nError: Unable to bench_malloc <_temp_edge_flow>.\n"); assert(0);
    }
    for ( int i = 0; i < mcf_v->no_edge; i++) {
        id       = edge_buf[i].id;       
        src      = edge_buf[i].src;    
        dest     = edge_buf[i].des;   
        capacity = edge_buf[i].capacity;   
        delay    = edge_buf[i].delay;   

        mcf_v->edges[i].id = id;
        mcf_v->edges[i].src = src;
        mcf_v->edges[i].dest = dest;
        mcf_v->edges[i].capacity = capacity;
        mcf_v->edges[i].left_capacity = capacity;
        mcf_v->edges[i].latency = delay;
        mcf_v->edges[i].length = 0.0;

        mcf_v->edges[i].flow = 0.0;
        mcf_v->edges[i]._flows = NULL;
    }

    // (3) record adjacent edges for each node;
    // (3) 记录每个节点的相邻边；
    for ( int i = 0; i < mcf_v->no_edge; i++) {
        int index = mcf_v->edges[i].src;
        mcf_v->nodes[index].edges[mcf_v->nodes[index].no_edge] = mcf_v->edges[i].id;
        mcf_v->nodes[index].no_edge++;
    }

    // (4) read demands/commodities;
    // (4) 读取需求/商品；
    double amount;
    mcf_v->no_commodity = 1; // demands_num;
    mcf_v->_commodities = (COMMODITY *)bench_malloc(sizeof(COMMODITY) * (mcf_v->no_commodity));
    if ( mcf_v->_commodities == NULL) {
        my_printf("\nError: Unable to bench_malloc <_commodities>.\n"); assert(0);
    }
    for ( int i = 0; i < mcf_v->no_commodity; i++) {
        id     = demands_buf[demands_select].id;
        src    = demands_buf[demands_select].src;
        dest   = demands_buf[demands_select].des;
        amount = demands_buf[demands_select].amount;

        mcf_v->_commodities[i].id = id;
        mcf_v->_commodities[i].src = src;
        mcf_v->_commodities[i].dest = dest;
        mcf_v->_commodities[i].demand = amount * rate; // rate = 1 by default;
        mcf_v->_commodities[i].left_demand = amount;

        if (mcf_v->nodes[src].comms == NULL) {
            mcf_v->nodes[src].comms = (int *)bench_malloc(sizeof(int) * mcf_v->no_node);
            if ( mcf_v->nodes[src].comms == NULL) {
                my_printf("\nError: Unable to bench_malloc <nodes[src].comms>.\n"); assert(0);
            }
        }
        mcf_v->nodes[src].comms[mcf_v->nodes[src].no_comm] = i;
        mcf_v->nodes[src].no_comm++;
    }

    // (5) reset;
    for ( int i = 0; i < mcf_v->no_edge; i++) {
        // Note1: I had to delay this allocation because no_commodity had 
        // not been set yet;
        // 注1：我不得不延迟这个分配，因为 no_commodity 还没有设置；
        mcf_v->edges[i]._flows = (double *)bench_malloc(sizeof(double) * (mcf_v->no_commodity));
        if ( mcf_v->edges[i]._flows == NULL) {
            my_printf("\nError: Unable to bench_malloc <edges._flows>.\n"); assert(0);
        }
        for ( int j = 0; j < mcf_v->no_commodity; j++) {
            mcf_v->edges[i]._flows[j] = 0.0;
        }
    }
    for ( int i = 0; i < mcf_v->no_node; i++) {
        // Note2: same as above;
        // 注2：同上；
        mcf_v->nodes[i]._preferred_path = (int *)bench_malloc(sizeof(int) * mcf_v->no_commodity);
        if ( mcf_v->nodes[i]._preferred_path == NULL) {
            my_printf("\nError: Unable to bench_malloc <_preferred_path>.\n"); assert(0);
        }
        for ( int j = 0; j < mcf_v->no_commodity; j++) {
            mcf_v->nodes[i]._preferred_path[j] = -1;           
        }
    }
    
    return;
}

void free_topology(MCF *mcf_v)
{
    int i=0;

    bench_free( mcf_v->_commodities);

    for ( i = 0; i < mcf_v->no_edge; i++) {
        bench_free( mcf_v->edges[i]._flows);
    }
    bench_free( mcf_v->edges);
    bench_free( mcf_v->_temp_edge_flow);

    for ( i = 0; i < mcf_v->no_node; i++) {
        bench_free( mcf_v->nodes[i].comms);
        bench_free( mcf_v->nodes[i].edges);
    }
    bench_free( mcf_v->nodes);

    return;
}

////////////////////////////////////////////////////////////////////////////////
//
// debug utils;
//
////////////////////////////////////////////////////////////////////////////////

void print_network_demands(MCF *mcf_v, bool print_only_edges)
{
    my_printf("\n\nNetwork and demands:");
    my_printf("\nNodes %d",mcf_v->no_node);
    if ( print_only_edges == false) {
        for ( int i = 0; i < mcf_v->no_node; i++) {
            my_printf("\n %d  (%d %d)", mcf_v->nodes[i].id, mcf_v->nodes[i].x, mcf_v->nodes[i].y);
            my_printf("  num_commodities=%d dist=%lf",mcf_v->nodes[i].no_comm,mcf_v->nodes[i].dist);
            my_printf("\n     ");
            for ( int k = 0; k < mcf_v->nodes[i].no_edge; k++) {
                my_printf(" %d", mcf_v->nodes[i].edges[k]);
            }
        }
    }
    my_printf("\nEdges %d",mcf_v->no_edge);
    if(mcf_v->no_node < 20){
        for ( int i = 0; i < mcf_v->no_edge; i++) {
            //printf("\n %d %d -> %d  cap: %.2lf  Y_e: %.2lf  len: %.2lf  flow: %.2lf  breakdown:",
            //  edges[i].id, edges[i].src, edges[i].dest,
            //  edges[i].capacity, edges[i]._Y_e,
            //  edges[i].length, edges[i].flow);
            my_printf("\n %2d %2d -> %-2d  cap: %.2lf  flow: %.2lf  breakdown:",
                mcf_v->edges[i].id, mcf_v->edges[i].src, mcf_v->edges[i].dest,
                mcf_v->edges[i].capacity, mcf_v->edges[i].flow);
            for ( int j = 0; j < mcf_v->no_commodity; j++) {
                my_printf(" %.2lf", mcf_v->edges[i]._flows[ j]);
            }
        }
    }
    if ( print_only_edges == false) {
        my_printf("\nDemands/commodities %d",mcf_v->no_commodity);
        for ( int i = 0; i < mcf_v->no_commodity; i++) {
            my_printf("\n %d  %d -> %d demand=%lf  portion_unsatisfied=%lf", mcf_v->_commodities[i].id,
                   mcf_v->_commodities[i].src, mcf_v->_commodities[i].dest,
                   mcf_v->_commodities[i].demand, // amount * rate
                   mcf_v->_commodities[i].left_demand); // amount
        }
    }
    my_printf("\n");
}

void print_routing_paths(MCF *mcf_v)
{
    // call only after a call of do_randomized_rounding();
    // 仅在调用 do_randomized_rounding() 之后调用；
    // printf("\nRandomized rounded paths:");

    for ( int i = 0; i < mcf_v->no_commodity; i++) {
        // printf("Commodity %d: %d -> %d: ", i, 
        //        mcf_v->_commodities[i].src, mcf_v->_commodities[i].dest);
        my_printf("Commodity %d: %d -> %d: ", demands_select, 
               mcf_v->_commodities[i].src, mcf_v->_commodities[i].dest);
        

        int src_id = mcf_v->_commodities[i].src;
        while ( src_id != mcf_v->_commodities[i].dest) {
            my_printf(" %d", src_id);
            src_id = mcf_v->nodes[src_id]._preferred_path[i];
        }
        my_printf(" %d", src_id); // dest;
    }
    my_printf("\n");
}

void print_backward_shortest_path(MCF *mcf_v, int dest)
{
    // debug only;
    int t = dest;
    my_printf("\n");
    while ( mcf_v->nodes[t].pre != -1) {
        my_printf(" %d ->", t);
        t = mcf_v->nodes[t].pre;
    } my_printf(" %d ", t);
}

////////////////////////////////////////////////////////////////////////////////
//
// MCF randomized rounding;
//
////////////////////////////////////////////////////////////////////////////////

bool do_randomized_rounding(MCF *mcf_v)
{
    // after mcf_solver finds a fractional flow solution, we do a 
    // randomized rounding to set only one path for each commodity;
    // otherwise the commodities would traverse multiple paths that
    // would translate in path splitting for packets which would require
    // router architecture modification too much and re-ordering of packets
    // at destination;
    // mcf_solver找到分数流解后，我们进行随机舍入，为每种商品仅设置一条路径；
    // 否则，商品将遍历多个路径，这将导致数据包的路径分裂，这将需要对路由器架
    // 构进行过多的修改并在目的地对数据包进行重新排序；

    for ( int i = 0; i < mcf_v->no_commodity; i++) {
        // () for each commodity we start from its source and traverse
        // downstream nodes; at each step we pick up the node that has
        // the largest fraction of this commodity as the preferred path;
        // record this preferred path in the preferred_path array;
        // () 对于每个商品，我们从其源头出发，遍历下游节点； 在每一步中，我们都会选择拥有
        // 该商品最大比例的节点作为首选路径； 将这个首选路径记录在preferred_path数组中；

        int src_id = mcf_v->_commodities[i].src;
        while ( src_id != mcf_v->_commodities[i].dest) {
            // recursively travel from src to dest searching for maximum
            // fractional flow;
            // 递归地从 src 到 dest 搜索最大分数流；
                
            int id_max_flow_fraction = -1;
            double max_flow_fraction = 0.0;
            for ( int k = 0; k < mcf_v->nodes[ src_id].no_edge; k++) {
                // for each adjacent edge look at the commodity index "i",
                // and seek the edge id with maximum flow fraction;
                // 对于每个相邻边，查看商品索引“i”，并寻找具有最大流量分数的边 id；

                int edge_id = mcf_v->nodes[ src_id].edges[k];
                if ( max_flow_fraction < mcf_v->edges[edge_id]._flows[ i]) {
                    max_flow_fraction = mcf_v->edges[edge_id]._flows[ i];
                    id_max_flow_fraction = edge_id;
                }
            }
            assert((id_max_flow_fraction >= 0) & (id_max_flow_fraction < mcf_v->no_edge));

            // () record the neighbor node id as the downstream node of the
            // preferred path for this commodity; that is, along the edge with
            // max fraction of flow from current node for this commodity;
            // ()记录邻居节点id作为该商品首选路径的下游节点； 也就是说，沿着该商品当前节点流量最大部分的边缘；
            mcf_v->nodes[src_id]._preferred_path[i] = mcf_v->edges[id_max_flow_fraction].dest;

            // prepare for next iter;
            // 为下一个iter做准备；
            src_id = mcf_v->nodes[src_id]._preferred_path[i];
        }
    }

    return true;
}
