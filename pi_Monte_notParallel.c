#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define N 10

int main(){
    double start,end,time_f;
    time_t timer;
     int r = 0;

    start = time(&timer);
    
        for(unsigned long long i = 0;i<N;i++){            
            double x = (double)rand()/(RAND_MAX);
            double y = (double)rand()/(RAND_MAX);
            if( x*x+y*y <= 1){
                r++;
            }
        }
        
    end = time(&timer);
    time_f = end - start;
    printf("時間:%f秒\n",time_f);    
    printf("1以下の数r(並列化の外に記述):%d\n",r);
    printf("全ての試行n:%d\n",N);
    double final = 4.0*r / N;
    printf("円周率:%f\n",final);
}
