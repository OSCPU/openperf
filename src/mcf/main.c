#include <am.h>
#include <klib-macros.h>
#include <bench_debug.h>
#include <mcf.h>
#include <input.h>

extern int demands_select;

////////////////////////////////////////////////////////////////////////////////
//
// launching point;
//
////////////////////////////////////////////////////////////////////////////////

int main(char *args)
{
    bench_malloc_init();
    uint64_t start_time, end_time;
    start_time = uptime();

    BENCH_LOG(DEBUG, "\nRandomized rounded paths: size: %d", sizeof(size_t));
    for(demands_select = 0; demands_select < demands_num; demands_select++)
    {
        // (1) run MCF solver;
        MCF mcf;
        MCF_init(&mcf);
        // here you should build your network either by reading it from a
        // file (network examples are in /tests) or by populating the
        // mcf object directly from the host application (the one inside
        // which you plan to call MCF solver possibly multiple times);
        // parse_options(&mcf, argc, argv);
        parse_options(&mcf, "MCF", 0.1);
        build_network_from_file(&mcf, 1000000, 1);
        run_mcf_solver(&mcf);

        // (2) entertain user;
        // printf("\n\nFINAL RESULT:");
        // if ( problem_type(&mcf) == MCMCF_TYPE) {
        //     printf("\nFinal latency L=%lf", get_L(&mcf));
        // }
        // print_network_demands(&mcf, true); // print_only_edges;
        // Note: rounding is not required; you may want or not to use this 
        // in your application; in my case I do it so that one commodity
        // is shipped only via one path (in the context of NoCs I want to 
        // avoid packet (re)ordering at destinations); be aware: randomization
        // "damages" optimality and may violate capacities;
        do_randomized_rounding(&mcf);
        print_routing_paths(&mcf);


        // (3) clean up
        free_topology(&mcf);
    }
    end_time = uptime();
    BENCH_LOG(INFO, "time: %s", format_time(end_time - start_time));

    return 0;
}
