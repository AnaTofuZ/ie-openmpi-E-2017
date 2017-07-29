//素数判定(試し割り法)並列化なし
//実行時にOMP_CANCELLATION=trueを入れてね

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define N 10000000   //Nまでの素数を調べる

int main(){
    int i,j,n;
    struct timeval start,end;

    omp_set_num_threads(4);    //スレッド数を変更
    
    gettimeofday(&start, NULL); //測定開始

    #pragma omp parallel for private(n)
    for(i = 2; i <= N; i++){
        n = 0;  //約数の個数を初期化
        #pragma omp parallel for
        for(j = 1; j <= sqrt(i); j++){ //√iまでの数を試し割り
            if(i%j == 0) n++;   //√iまでの約数の個数のカウント
            // if (n > 1) break;   //√iまでの約数の個数が2個だと試し割りを終了
            #pragma omp cancel for if (n > 1)   //√iまでの約数の個数が2個だと試し割りを終了
        }
        //√iまでの約数の個数が1個の時(約数が1の時)素数である
        if(n == 1) printf("%d\n",i);
    }
    
    gettimeofday(&end, NULL);   //測定終了
    printf("%f sec\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)*1.0E-6);
}