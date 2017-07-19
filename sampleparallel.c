#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(){

    int i,j,n;
    omp_set_num_threads(16);
    time_t start,end;
    
    start = time(NULL);

    #pragma omp parallel
    {
        // #pragma omp parallel for
        for(i = 2; i <= 1000000; i++) {
            n = 0; //約数の個数を初期化
            #pragma omp parallel for
            for(j = 1; j <= i; j++) {
                //約数の個数のカウント
                if(i%j == 0) {
                    n++;
                }
            }
            //約数の個数が2個のとき素数である
            if(n == 2) {
                printf("%d\n",i);
            }
        }
    }

    end = time(NULL);
    printf("%ld s\n",end - start);
}