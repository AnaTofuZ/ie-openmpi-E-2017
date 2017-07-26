//素数判定(試し割り法)並列化なし

#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#define N 10000000   //N以下を調べる

int main(){

    int i,j,n;
    // time_t start,end;
    struct timeval start,end;
    
    // start = time(NULL);
    gettimeofday(&start, NULL); //測定開始

    for(i = 2; i <= N; i++){
        n = 0;  //約数の個数を初期化
        
        for (j = 1; j <= sqrt(i); j++) { //√iまでの数を試し割り
            if(i%j == 0) n++;   //√iまでの約数の個数のカウント
            if(n > 1) break;    //√iまでの約数の個数が2個だと試し割りを終了
        }
        //√iまでの約数の個数が1個の時(約数が1の時)素数である
        // if(n == 1) printf("%d\n",i);
    }

    // end = time(NULL);
    gettimeofday(&end, NULL);   //測定終了
    printf("%f sec\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)*1.0E-6);
}