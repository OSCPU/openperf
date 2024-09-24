#include <klib.h>
#include <bench_debug.h>
#include <stdio.h>
#include <pqueue.h>
#include <mcf.h>
#include <input.h>


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
    int i=0;

    // init dual variables
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
        BENCH_LOG(ERROR, "Error:  -problem_type must be MCF or MCMCF.\n");
        assert(0);
    }

    mcf->_epsilon1 = epsilon;
    if (mcf->_epsilon1 <= 0 || mcf->_epsilon1 >= 1) {
        BENCH_LOG(ERROR, "Error:  -epsilon option requires a float in (0,1).\n");
        assert(0);
    }

    return true;
}

void init_param(MCF *mcf)
{
    // called one time only from inside build_network_from_file() because
    // we need the number of edges of the graph for delta calculation;
    // () set latency budget to infinity (inf);
    mcf->L = 1000000.0;
    // () epsilon is now set to default _epsilon1 = 0.1 inside parse_options();
    // or it could be set by user via command line argument;
    // () delta is set according to equation 3 from Karakostas paper;
    double epsilon = mcf->_epsilon1;
    mcf->_delta = (1/pow(1+epsilon, (1-epsilon)/epsilon))*(pow((1-epsilon)/mcf->no_edge, 1/epsilon));
    // () expected number of iterations (or phases) of the outer loop;
    // currently it is not used for any purpose;
    mcf->_scale = log((1+epsilon)/mcf->_delta) / log(1+epsilon);
    //printf("\nepsilon=%e delta=%e _scale=%e\n",_epsilon1,_delta,_scale); // assert(0);
}

bool feasibility_check(MCF *mcf)
{
    // check and see if the routed flows violate capacities; if so,
    // then return false: no feasible solution; this is a "stretch";
    // feasibility should be checked differently;
    double threshold, violation;
    bool printed_warning = false;
    for ( int i = 0; i < mcf->no_edge; i++) {
        if (mcf->edges[i].flow > mcf->edges[i].capacity) {
            // consider only violations that are greater than 3 * epsilon;
            threshold = 3 * mcf->_epsilon1 * mcf->edges[i].capacity;
            violation = (mcf->edges[i].flow - mcf->edges[i].capacity);
            if ( violation > threshold) {
                return false;
            } else {
                // print once only a warning;
                if ( !printed_warning) {
                    bench_printf("\nWarning:  Some edges have capacity violation within 3*epsilon");
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
    double lambda = DBL_MAX;

    for ( int comm_i = 0; comm_i < mcf->no_commodity; comm_i++) {
        // for each commodity we take its source node and look
        // at its outgoing edges to sum all flow pushed/routed 
        // for this commodity;
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
    int t = dest;
    double cost_to_send_unit_flow = 0.0; // along the shortest path to this dest;
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
    int t = 0;
    double min_capacity = 1000000.0;

    mcf->_min_rd++;
    // start from all dest nodes, traverse shortest path tree;
    for ( int i = 0; i < mcf->nodes[s].no_comm; i++) {
        if ( mcf->_commodities[mcf->nodes[s].comms[i]].left_demand > 1e-3) {
            // pick up this destination and walk backward to sourse "s";
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
    int t = 0;
    // start from all dest nodes, traverse shortest path tree;
    for ( int i = 0; i < mcf->nodes[s].no_comm; i++) {
        if ( mcf->_commodities[mcf->nodes[s].comms[i]].left_demand > 1e-3) {
            // pick up this destination and walk backward to sourse "s";
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
    while ( mcf->nodes[t].pre != -1) {
        int edge_id = mcf->nodes[t].pre_edge;
        mcf->_temp_edge_flow[edge_id] += routed_amount;
        mcf->edges[edge_id].left_capacity -= routed_amount;
        
        // record this routed_amount for this commodity id on the 
        // corresponding edge also;
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
    int i, t;
    double old_phi_latency;
    double temp_latency = 0.0;

    // (1) accumulate temp_latency along the shortest paths for the
    // shortest paths tree for the commodities of this source node;
    mcf->_min_rd++;
    for ( i = 0; i < mcf->nodes[s].no_comm; i++) {
        t = mcf->_commodities[mcf->nodes[s].comms[i]].dest;
        while ( (mcf->nodes[t].pre != -1) && (mcf->nodes[t].min_visited != mcf->_min_rd)) {
            int edge_id = mcf->nodes[t].pre_edge;
            mcf->nodes[t].min_visited = mcf->_min_rd;
            
            temp_latency += mcf->_temp_edge_flow[edge_id] * mcf->edges[edge_id].latency;

            // update the dual variable Y_e;
            mcf->edges[edge_id]._old_Y_e = mcf->edges[edge_id]._Y_e;
            // Note: _temp_edge_flow[edge_id] represents the amount of total
            // flow of all commodities that have the same source "s", which is
            // pushed thru this edge during this step "s";
            mcf->edges[edge_id]._Y_e *= 
                (1 + epsilon * mcf->_temp_edge_flow[edge_id] / mcf->edges[edge_id].capacity);

            // walk upstream on shortest path;
            t = mcf->nodes[t].pre;
        }
    }
    mcf->_min_rd++;
    // record latency contributed due to total flow pushed thru during
    // this step "s";
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
        if ( flag != 0) { // 1
            mcf->edges[i].length += mcf->edges[i].latency * (mcf->_phi_latency - old_phi_latency);
        }
    }

    // (4) add to the flow recorded for each edge the accumulated 
    // amounts (as sum of f_{i,j,s}^{c_q}) for each commodity routed during
    // this iteration, amounts which are reflected by _temp_edge_flow (which
    // has values != zero) for edges of shortest path of this iter;
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->edges[i].flow += mcf->_temp_edge_flow[i];
    }

    // (5) reset temp storage of pushed flow during this iter; prepare it
    // for the next push/iteration;
    for ( i = 0; i < mcf->no_edge; i++) {
        mcf->_temp_edge_flow[i] = 0.0;
    }

    return;
}

void scale_down_linear(MCF *mcf, float times) 
{
    // Note: currently not used;
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

    // printf("\nPART 1 - MAX CONCURRENT FLOW (MCF):");

    // flag=0 means that this is a "max commodity flow" run; there is
    // no latency constraint/budget;
    mcf_v->_lambda_max = mcf(mcf_v, mcf_v->_delta, mcf_v->_epsilon1, 0); // flag=0;
    //print_network_demands(true); // assert(0); // debug;

    // early exit if there is no "feasible" solution;
    if ( feasibility_check(mcf_v) == false) {
        bench_printf("\nWarning: No feasible solution; some edges have capacity ");
        bench_printf("\n         violation greater than 3*epsilon.\n");
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
    if (mcf_v->_problem_type == MCF_TYPE) {
        return 1;
    }


    // (2) second, "improved" binary search to refine L; basically we look 
    // for the minimum latency achievable; during this search mcf is run with 
    // flag=1, that is as a "min-cost max concurrent flow";
    // printf("\n\nPART 2 - BINARY SEARCH FOR L - MIN-COST MAX CONCURRENT FLOW (MCMCF):");
    // maximum latency is as resulted after finding the solution of the
    // "max multicommodity flow" problem from PART 1;
    mcf_v->_latency_max = mcf_v->_total_latency; // Hu: 1000000;
    mcf_v->LL = 0;
    mcf_v->UL = mcf_v->_total_latency; // Hu: _latency_max/_lambda_max;
    mcf_v->_s = -1;

    int counter = 0;
    while ( (mcf_v->UL - mcf_v->LL)/mcf_v->LL > 0.1) {
        // (a) set Latency as the middle point between LL and UL;
        mcf_v->L = (mcf_v->LL + mcf_v->UL) / 2;
        // (b) this call of MCF modifies LL and UL using the 
        // "interval estimation" technique proposed in Hu paper;
        mcf(mcf_v, mcf_v->_delta, mcf_v->_epsilon1, 1); // flag=1;

        // (c) now, if anything goes wrong for some pathological testcase, 
        // have a brutal exit; this will require debugging;
        counter++;
        if ( counter >= 512) {
            bench_printf("\nError:  Binary search of MCMCF took more than 512 iterations.");
            bench_printf("\n        This is an unusual testcase or the code has a bug.\n");
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

    int i,j;
    int iter=0; // phase counter: number of iterations of the big main loop
    double lambda=1; // result to be returned;
    double D=1, alpha=1, dual=1;
    // used to find the amount of flow pushed in each step;
    double usable_amount_cap, usable_amount_latency, routed_amount;
    // for tracking gap between lambda and dual;
    // double gap=0.0;
    // double old_gap=0.0; 
    // double old_old_gap=0.0;


    // () initialization of primal variables (i.e., flows thru all edges)
    // and dual valiables PHI_d, Y_e and "length function" l(e)
    // of all edges; also resets left_demand to demand for all commodities
    // as well as _total_latency;
    initialize(mcf_v, delta, flag);
    mcf_v->_rd = 1;
    for ( i = 0; i < mcf_v->no_node; i++) {
        mcf_v->nodes[i].dij_visited = 0;
        mcf_v->nodes[i].dij_updated = 0;
        mcf_v->nodes[i].min_visited = 0;
    }
    

    // () the big loop, each run of this loop is a phase; each phase
    // has |S| iterations;
    while (1) {

        // () in every phase we start with the demand d_j for every commodity;
        for ( j = 0; j < mcf_v->no_commodity; j++) {
            mcf_v->_commodities[j].left_demand = mcf_v->_commodities[j].demand;
        }
    

        // () next there are |S| iterations, one for each node that is a 
        // source for at least a commodity;
        for ( i = 0; i < mcf_v->no_node; i++) {
            if ( mcf_v->nodes[i].no_comm) { // if this node is source of "r" _commodities;
                
                int commodities_left = mcf_v->nodes[i].no_comm;
                int *dest_flag = (int*)bench_malloc((mcf_v->no_node)*sizeof(int));
                if ( dest_flag == NULL) {
                    bench_printf("\nError:  Unable to bench_malloc <mcf>.\n"); assert(0);
                }
                memset((void*)dest_flag,0,(mcf_v->no_node)*sizeof(int));
                // dest_flag is set "1" for nodes that are destinations of _commodities;
                for ( j = 0; j < mcf_v->nodes[i].no_comm; j++) {
                    dest_flag[mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest] = 1;
                }


                // while there are left commodities to be routed for this node; 
                // there are a number of steps for current iteration;
                int step_count = 0;
                while ( commodities_left) {
                    step_count ++;

                    // () compute shortest PATHS tree, where edges have "length(e)";
                    // of all paths from this sink to all its destinations;
                    //print_network_demands( true); // debug;
                    shortest_paths(mcf_v, mcf_v->nodes[i].id, commodities_left, dest_flag);
                    
                    // () reset left_capacities of edges in the tree to the
                    // initial capacities; u'(e) = u(e), any e in tree;
                    reset_left_capacities_in_tree(mcf_v, mcf_v->nodes[i].id);

                    // () route "f = d(c_q)" units of flow of a given commodity
                    // and update the flow of each edge: f_e = f_e + f, along its 
                    // shortest path;
                    bool flow_has_been_routed = false;
                    for ( j = 0; j < mcf_v->nodes[i].no_comm; j++) {

                        // the amount of commodity c_q that has not been routed yet
                        // at step "s";
                        double left_demand = mcf_v->_commodities[mcf_v->nodes[i].comms[j]].left_demand;

                        if ( left_demand > 1e-3) {
                            flow_has_been_routed = true;
                            //print_backward_shortest_path(_commodities[nodes[i].comms[j]].dest);


                            // available flow amount from bottleneck-edge of shortest path;
                            // this "c" represents the available minimum capacity of the
                            // edges on shortest path of this commodity;
                            usable_amount_cap = min_capacity_this_commodity(mcf_v, mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest);
                                                                            

                            // available flow amount from latency constraint
                            if ( flag == 0) { // 0: "max concurrent flow"   // 0: “最大并发流量”
                                usable_amount_latency = 1000000.0; // inf;
                            } else { // 1: "min-cost max concurrent flow"   // 1: “最小成本最大并发流”
                                // this is L/c(P), where c(P) is is the cost of sending 
                                // one unit of flow along the shortest path:
                                // Sum_{e in P}{D(e)}, where D(e) is latency of each edge;
                                usable_amount_latency = check_latency_constraint(mcf_v, mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest);
                                                                                 
                            }
                            
                            // flow amount to be routed at step "s": f_{i,j,s}^{c_q};
                            routed_amount = minimum(usable_amount_cap, left_demand, usable_amount_latency);
                            
                                                    

                            // update every "_temp_edge_flow" - from dest backward to src
                            // will be added routed_amount; also update left_capacities
                            // of edges along the shortest path of this commodity;
                            route_flow(mcf_v, mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest,
                                        routed_amount, mcf_v->nodes[i].comms[j]);

                            // update commodity amounts to be routed still (i.e., are left);
                            mcf_v->_commodities[mcf_v->nodes[i].comms[j]].left_demand -= routed_amount;

                            if (mcf_v->_commodities[mcf_v->nodes[i].comms[j]].left_demand <= 1e-3) {
                                // this commodity is done, set its destination flag to 0;
                                commodities_left --;
                                dest_flag[mcf_v->_commodities[mcf_v->nodes[i].comms[j]].dest] = 0;
                            }
                        }
                    }//for ( j = 0; j < nodes[i].no_comm; j++)

                    // () update dual variables: Y_e, phi_latency (or PHI_d), 
                    // length(e);
                    update_dual_variables(mcf_v, mcf_v->nodes[i].id, epsilon, flag);

                    mcf_v->_rd++;
                    if ( !flow_has_been_routed) break;
                }//while ( commodities_left)


                bench_free( dest_flag);

            }//if ( nodes[i].no_comm)
        }//for ( i = 0; i < no_node; i++)


        // () increment phase counter; a phase is an iteration of the big main loop;
        iter++;
        // additional stopping criterion;
        if ( iter >= mcf_v->_scale) break;
        //if ( iter >= 80) break;

        // () compute dual and lambda and keep track of the gap between them;
        // -- compute dual=D/alpha;
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
        // lambda = L / (_total_latency/iter);
        lambda = compute_lambda(mcf_v);
        lambda /= iter; // consider effect of scaling;
        //printf("\n Lambda=%.8f, Dual=D/alpha=%.8f, D=%.8f",lambda,dual,D);
        
        // -- keep track of gap;
        // old_old_gap = old_gap;
        // old_gap = gap;
        // gap = dual/lambda - 1;

         
        // () this implements the "interval estimation"; see Theorem 3 of Hu paper;
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
            if ( D >= 1) { break; }
        }
    
    }//while (1)


    // () scale down the final flows so that the solution is feasible 
    // (that is, capacities are met);
    scale_down_flows(mcf_v, iter);
    // also, record final latency, which must consider scaling too;
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

    int num_commodities_to_process = num_commodities;
    PQDATUM wf, wf1; // WAVEFRONTS;
    PQDATUM_init(&wf);
    PQDATUM_init(&wf1);

    PQUEUE pq;
    PQUEUE_init(&pq);
    int *pos = (int *)bench_malloc(sizeof(int) * (mcf_v->no_node));
    if ( pos == NULL) {
        bench_printf("\nError: Unable to bench_malloc <shortest_path>.\n"); assert(0);
    }
    
    pqinit(&pq, 400); // 400 is just a constant;
    // reset dist of all nodes;
    for ( int i = 0; i < mcf_v->no_node; i++) {
        mcf_v->nodes[i].dist = DBL_MAX;
    }
    // source "s" resets;
    mcf_v->nodes[s].pre = -1;
    mcf_v->nodes[s].pre_edge = -1;
    mcf_v->nodes[s].dist = 0.0;

    set_node(&wf, s); // sourse "s";
    set_dist(&wf, 0.0);

    pqinsert(&pq, wf, pos);

    while ( !pqempty(&pq)) {
        int v, w;
        
        // retreive the shortest non-visited node;
        pqremove(&pq, &wf1, pos);
        v = node(&wf1);
        if ( dest_flag[v]) num_commodities_to_process--;
        // break when all shortest paths to all destinations from source "s"
        // have been found;
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

    return true;
}

bool build_network_from_file(MCF *mcf_v, double latency_limit, double rate)
{
    // rate is the demand coefficient (injection rate): 0.05, 0.1, 0.15, 0.2, 0.25;
    // latency_limit and rate are not used;

    // (1) import the network topology and the demands;
    read_network_topology_and_demands(mcf_v, 1);

    // (3) one time initialization of parameters (of those not set by
    // user via command line arguments);
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
        bench_printf("\nError: Unable to bench_malloc <nodes>.\n"); assert(0);
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
        // mcf_v->nodes[i].edges = (int *)bench_malloc(sizeof(int) * MAX_DEGREE);
        mcf_v->nodes[i].edges = (int *)bench_malloc(sizeof(int) * node_buf[i].edge_num);
        assert(mcf_v->nodes[i].edges);
        if ( mcf_v->nodes[i].edges == NULL) {
            bench_printf("\nError: Unable to bench_malloc <nodes.edges>.\n"); assert(0);
        }
    }

    // (2) edges
    mcf_v->no_edge = edges_num;
    mcf_v->edges = (EDGE *)bench_malloc(sizeof(EDGE) * (mcf_v->no_edge));
    if ( mcf_v->edges == NULL) {
        bench_printf("\nError: Unable to bench_malloc <edges>.\n"); assert(0);
    }
    mcf_v->_temp_edge_flow = (double*)bench_malloc(sizeof(double) * (mcf_v->no_edge));
    if ( mcf_v->_temp_edge_flow == NULL) {
        bench_printf("\nError: Unable to bench_malloc <_temp_edge_flow>.\n"); assert(0);
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
    for ( int i = 0; i < mcf_v->no_edge; i++) {
        int index = mcf_v->edges[i].src;
        mcf_v->nodes[index].edges[mcf_v->nodes[index].no_edge] = mcf_v->edges[i].id;
        mcf_v->nodes[index].no_edge++;
    }

    // (4) read demands/commodities;
    double amount;
    mcf_v->no_commodity = 1; // demands_num;
    mcf_v->_commodities = (COMMODITY *)bench_malloc(sizeof(COMMODITY) * (mcf_v->no_commodity));
    if ( mcf_v->_commodities == NULL) {
        bench_printf("\nError: Unable to bench_malloc <_commodities>.\n"); assert(0);
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
                bench_printf("\nError: Unable to bench_malloc <nodes[src].comms>.\n"); assert(0);
            }
        }
        mcf_v->nodes[src].comms[mcf_v->nodes[src].no_comm] = i;
        mcf_v->nodes[src].no_comm++;
    }

    // (5) reset;
    for ( int i = 0; i < mcf_v->no_edge; i++) {
        // Note1: I had to delay this allocation because no_commodity had 
        // not been set yet;
        mcf_v->edges[i]._flows = (double *)bench_malloc(sizeof(double) * (mcf_v->no_commodity));
        if ( mcf_v->edges[i]._flows == NULL) {
            bench_printf("\nError: Unable to bench_malloc <edges._flows>.\n"); assert(0);
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
            bench_printf("\nError: Unable to bench_malloc <_preferred_path>.\n"); assert(0);
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
    bench_printf("\n\nNetwork and demands:");
    bench_printf("\nNodes %d",mcf_v->no_node);
    if ( print_only_edges == false) {
        for ( int i = 0; i < mcf_v->no_node; i++) {
            bench_printf("\n %d  (%d %d)", mcf_v->nodes[i].id, mcf_v->nodes[i].x, mcf_v->nodes[i].y);
            bench_printf("  num_commodities=%d dist=%lf",mcf_v->nodes[i].no_comm,mcf_v->nodes[i].dist);
            bench_printf("\n     ");
            for ( int k = 0; k < mcf_v->nodes[i].no_edge; k++) {
                bench_printf(" %d", mcf_v->nodes[i].edges[k]);
            }
        }
    }
    bench_printf("\nEdges %d",mcf_v->no_edge);
    if(mcf_v->no_node < 20){
        for ( int i = 0; i < mcf_v->no_edge; i++) {
            //printf("\n %d %d -> %d  cap: %.2lf  Y_e: %.2lf  len: %.2lf  flow: %.2lf  breakdown:",
            //  edges[i].id, edges[i].src, edges[i].dest,
            //  edges[i].capacity, edges[i]._Y_e,
            //  edges[i].length, edges[i].flow);
            bench_printf("\n %2d %2d -> %-2d  cap: %.2lf  flow: %.2lf  breakdown:",
                mcf_v->edges[i].id, mcf_v->edges[i].src, mcf_v->edges[i].dest,
                mcf_v->edges[i].capacity, mcf_v->edges[i].flow);
            for ( int j = 0; j < mcf_v->no_commodity; j++) {
                bench_printf(" %.2lf", mcf_v->edges[i]._flows[ j]);
            }
        }
    }
    if ( print_only_edges == false) {
        bench_printf("\nDemands/commodities %d",mcf_v->no_commodity);
        for ( int i = 0; i < mcf_v->no_commodity; i++) {
            bench_printf("\n %d  %d -> %d demand=%lf  portion_unsatisfied=%lf", mcf_v->_commodities[i].id,
                   mcf_v->_commodities[i].src, mcf_v->_commodities[i].dest,
                   mcf_v->_commodities[i].demand, // amount * rate
                   mcf_v->_commodities[i].left_demand); // amount
        }
    }
    bench_printf("\n");
}

void print_routing_paths(MCF *mcf_v)
{
    // call only after a call of do_randomized_rounding();
    // printf("\nRandomized rounded paths:");

    for ( int i = 0; i < mcf_v->no_commodity; i++) {
        // printf("Commodity %d: %d -> %d: ", i, 
        //        mcf_v->_commodities[i].src, mcf_v->_commodities[i].dest);
        BENCH_LOG(DEBUG, "Commodity %d: %d -> %d: ", demands_select, 
               mcf_v->_commodities[i].src, mcf_v->_commodities[i].dest);
        

        int src_id = mcf_v->_commodities[i].src;
        while ( src_id != mcf_v->_commodities[i].dest) {
            bench_printf(" %d", src_id);
            src_id = mcf_v->nodes[src_id]._preferred_path[i];
        }
        bench_printf(" %d", src_id); // dest;
    }
    bench_printf("\n");
}

void print_backward_shortest_path(MCF *mcf_v, int dest)
{
    // debug only;
    int t = dest;
    bench_printf("\n");
    while ( mcf_v->nodes[t].pre != -1) {
        bench_printf(" %d ->", t);
        t = mcf_v->nodes[t].pre;
    } bench_printf(" %d ", t);
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

    for ( int i = 0; i < mcf_v->no_commodity; i++) {
        // () for each commodity we start from its source and traverse
        // downstream nodes; at each step we pick up the node that has
        // the largest fraction of this commodity as the preferred path;
        // record this preferred path in the preferred_path array;

        int src_id = mcf_v->_commodities[i].src;
        while ( src_id != mcf_v->_commodities[i].dest) {
            // recursively travel from src to dest searching for maximum
            // fractional flow;
                
            int id_max_flow_fraction = -1;
            double max_flow_fraction = 0.0;
            for ( int k = 0; k < mcf_v->nodes[ src_id].no_edge; k++) {
                // for each adjacent edge look at the commodity index "i",
                // and seek the edge id with maximum flow fraction;

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
            mcf_v->nodes[src_id]._preferred_path[i] = mcf_v->edges[id_max_flow_fraction].dest;

            // prepare for next iter;
            src_id = mcf_v->nodes[src_id]._preferred_path[i];
        }
    }

    return true;
}
