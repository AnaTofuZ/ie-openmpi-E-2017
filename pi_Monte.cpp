#include<stdio.h>
#include<omp.h>
#include<math.h>
#include<time.h>
#include <string.h>
#include <stdlib.h>
#define N 100000

int main(int argc, char *argv[]){
    time_t timer;
    double start,end;
    unsigned long long r = 0;
    unsigned long long n = atof(argv[2]);
    int t = atof(argv[1]);
    
    srand(time(&timer));    
    omp_set_num_threads(t);
    start = omp_get_wtime();
    
#pragma omp parallel reduction(+:r)
    {
#pragma omp for 
        for(unsigned long long i = 0;i<n;i++){
            double x = (double)rand()/(RAND_MAX+omp_get_thread_num());
            double y = (double)rand()/(RAND_MAX+omp_get_thread_num());
            if( (x*x+y*y) <= 1){
                r++;
            }
        }
    }
    
    end = omp_get_wtime();
    printf("時間:%.5f秒\n",end - start);
    printf("スレッド数:%d\n",omp_get_max_threads());
    printf("1以下の数r(並列化の外に記述):%llu\n",r);
    printf("全ての試行n:%llu\n",n);
    double final = 4.0*r/n;
    printf("円周率:%f\n",final);
}
