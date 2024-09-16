#include <gemm.h>

#define A(i,j) a[(j)*lda + (i)]

void serial_init(int m, int n, double * a, int lda){
    int count = 1;
    for(int j=0;j<n;j++){
        for(int i=0;i<m;i++)
            A(i,j) = count++;
    }
}

void random_init(int m, int n, double * a, int lda){
    for(int j=0;j<n;j++){
        for(int i=0;i<m;i++)
            A(i,j) = 2.0 * rand() - 1.0;
    }
}

extern bench_gemm_config config;

int main(){

    bench_malloc_init();
    int m = config.m;
    int n = config.n;
    int k = config.k;

    //TODO: calculate the memory size.
    double * A = (double*)bench_malloc(m*k*sizeof(double));
    double * B = (double*)bench_malloc(k*n*sizeof(double));
    double * C = (double*)bench_malloc(m*n*sizeof(double));
    assert(A);
    assert(B);
    assert(C);

    memset(A,0,m*k*sizeof(double));
    memset(B,0,k*n*sizeof(double));
    memset(C,0,m*n*sizeof(double));

    uint64_t start_time, end_time;
    srand(1556);

    random_init(m,k,A,m);
    random_init(k,n,B,k);

    start_time = uptime();
    matmul(m,n,k,A,m,B,k,C,m);
    end_time = uptime();

    bench_free(A);
    bench_free(B);
    bench_free(C);
    
    printf("time: %s ms \n", format_time(end_time - start_time));
    return 0;
}
