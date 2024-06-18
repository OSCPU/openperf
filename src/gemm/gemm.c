#include "gemm.h"

#define A(i,j) a[(j)*lda + (i)]

long time()
{
	return (io_read(AM_TIMER_UPTIME).us);
}

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

void display(double * matrix, int m, int n){
    for(int j=0;j<n;j++){
        for(int i=0;i<m;i++){
            printf("%f ",matrix[j*m+i]);
        }
        printf("\n");
    }
    return;
}

int main(){

    int m = 100;
    int n = 100;
    int k = 100;

    double * A = (double*)malloc(m*k*sizeof(double));
    double * B = (double*)malloc(k*n*sizeof(double));
    double * C = (double*)malloc(m*n*sizeof(double));

    memset(A,0,m*k*sizeof(double));
    memset(B,0,k*n*sizeof(double));
    memset(C,0,m*n*sizeof(double));

    long start,finish;
    double gflops = 2.0 * m*n*k * 1.0e-09;
    srand((unsigned)time(NULL));

    random_init(m,k,A,m);
    random_init(k,n,B,k);

    start = time();
    matmul(m,n,k,A,m,B,k,C,m);
    finish = time();

    double duration =  (double)(finish-start) / 100000;

    if(m<=8){
        printf("Matrix A : \n");
        display(A,m,k);

        printf("Matrix B : \n");
        display(B,k,n);

        printf("Dot Product Result : \n");
        display(C,m,n);
    }
    
    printf("Dot product took %f seconds GFLOPS : %f\n",duration,gflops/duration);
    return 0;
}
