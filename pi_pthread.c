#include <stdio.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define THREAD 10
#define ITERATION 1000

void calc_pi(void *arg);

int main(void){

    time_t start,end;
    int targ[THREAD];
    pthread_t handle[THREAD];

    start = time(NULL);

    for (int  i = 0; i < THREAD; i++) {
        targ[i]=i;
        pthread_create(&handle[i],NULL,(void*)calc_pi,(void*)&targ[i]); //thread作成
    }

    for (int i = 0; i < THREAD; i++) {
        pthread_join(handle[i],NULL);
    }

    end = time(NULL);
    printf("%ld sec\n",end - start);

    return 0;
}


// TODO 実際の処理

void calc_pi(void *arg){

    int* targ = (int *)arg;

    int c_start,c_end,range,limit;

    range = ITERATION/THREAD;
    c_start = (*targ)*range;
    c_end = ((*targ)+1)*range;

    if ( c_end >ITERATION) c_end = ITERATION;

    for (int i = 0; i < ITERATION; i++) {

    }

}
