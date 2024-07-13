#include <am.h>
#include <klib-macros.h>
#include <printf.h>
#include <mcf.h>
#include <test.h>

extern int demands_select;

////////////////////////////////////////////////////////////////////////////////
//
// launching point;
//
////////////////////////////////////////////////////////////////////////////////

int main( int argc, char **argv)
{
    uint64_t start_time, end_time;
    start_time = uptime();

    printf("\nRandomized rounded paths: size: %d\n", sizeof(size_t));
    for(demands_select = 0; demands_select < demands_num; demands_select++)
    {
        // (1) run MCF solver;
        //（1）运行 MCF 求解
        MCF mcf;
        MCF_init(&mcf);
        // here you should build your network either by reading it from a
        // file (network examples are in /tests) or by populating the
        // mcf object directly from the host application (the one inside
        // which you plan to call MCF solver possibly multiple times);
        // 在这里，您应该通过从文件中读取网络（网络示例位于 /tests 中）或直接从主机应
        // 用程序（您计划在其中可能多次调用 MCF 求解器的对象）填充 mcf 对象来构建网络；
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
    printf("time: %s ms \n", format_time(end_time - start_time));

    return 0;
}
