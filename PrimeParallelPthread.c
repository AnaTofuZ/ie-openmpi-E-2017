//素数判定(試し割り法)並列化なし

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define N 10000000   //Nまでの素数を調べる
#define THREAD_NUM 16 //スレッド数

void thread_func(void *arg);

int main(){

    int i,j,n;
    time_t start,end;
    pthread_t handle[THREAD_NUM];
    int targ[THREAD_NUM];

    start = time(NULL);

    for (int i = 0; i < THREAD_NUM; i++) {
       targ[i]=i;
       pthread_create(&handle[i],NULL,(void*)thread_func,(void*)&targ[i]); //thread作成
    }


    for (int i = 0; i < THREAD_NUM; i++) {
        pthread_join(handle[i],NULL);
    }

    end = time(NULL);
    printf("%ld sec\n",end - start);

    return 0;
}


void thread_func(void *arg){

    int* targ = (int *)arg;

    int c_start,c_end,range,limit;

    range = (N -2)/THREAD_NUM +1;
    c_start = 2+(*targ)*range;
    c_end = 2+ ((*targ)+1) *range;

    if (c_end > N){
        c_end = N;
    }

    for(int i = c_start; i <= c_end; i++) {
            int n = 0;  //約数の個数を初期化
            
            for(int j = 1; j <= sqrt(i); j++) { //√iまでの数を試し割り
                if(i%j == 0) n++;   //√iまでの約数の個数のカウント
                if(n > 1) break;    //√iまでの約数の個数が2個だと試し割りを終了
            }
            //√iまでの約数の個数が1個の時(約数が1の時)素数である
            if(n == 1) printf("%d\n",i);
        }
}
