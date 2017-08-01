//素数判定(試し割り法)並列化なし

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define N 10000000   //Nまでの素数を調べる

int main(){

    int i,j,n;
    time_t start,end;
    omp_set_num_threads(16);    //スレッド数を変更
    
    start = time(NULL);
    #pragma omp parallel for
    for(i = 2; i <= N; i++) {
        n = 0;  //約数の個数を初期化
        
        for(j = 1; j <= sqrt(i); j++) { //√iまでの数を試し割り
            if(i%j == 0) n++;   //√iまでの約数の個数のカウント
            if(n > 1) break;    //√iまでの約数の個数が2個だと試し割りを終了
        }
        //√iまでの約数の個数が1個の時(約数が1の時)素数である
        // if(n == 1) printf("%d\n",i);
    }

    end = time(NULL);
    printf("%ld sec\n",end - start);
}
