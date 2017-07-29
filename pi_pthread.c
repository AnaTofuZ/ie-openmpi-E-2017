#include <stdio.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

void calc_pi(void *arg);

int main(void){

    time_t start,end;

    start = time(NULL);


    end = time(NULL);
    printf("%ld sec\n",end - start);

    return 0;
}


// TODO 実際の処理

void calc_pi(void *arg){
}
