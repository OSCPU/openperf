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

    //TODO: calculate the memory size.
    double * A = (double*)malloc(m*k*sizeof(double));
    double * B = (double*)malloc(k*n*sizeof(double));
    double * C = (double*)malloc(m*n*sizeof(double));
    assert(A);
    assert(B);
    assert(C);

    memset(A,0,m*k*sizeof(double));
    memset(B,0,k*n*sizeof(double));
    memset(C,0,m*n*sizeof(double));

    uint64_t start_time, finish_time;
    //srand((unsigned)time(NULL));

    random_init(m,k,A,m);
    random_init(k,n,B,k);

    start_time = uptime();
    matmul(m,n,k,A,m,B,k,C,m);
    finish_time = uptime();

    if(m<=8){
        printf("Matrix A : \n");
        display(A,m,k);

        printf("Matrix B : \n");
        display(B,k,n);

        printf("Dot Product Result : \n");
        display(C,m,n);
    }
    
    printf("time: %s ms \n", format_time(finish_time - start_time));
    return 0;
}
