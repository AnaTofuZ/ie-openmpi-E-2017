//素数判定(エラトステネスの篩)並列化なし

#include <stdio.h>
#include <time.h>
#include <math.h>

#define N 100000   //Nまでの素数を調べる

int main(){
    int i,j;
    int array[N-1];
    time_t start,end;

    start = time(NULL);

    for(i = 2; i <= N; i++) {   //2からNまでの数を配列に格納
        array[i] = i;
    }

    for(i = 2; i < sqrt(N); i++) {  //エラトステネスの篩(なんか腑に落ちていない)
        for(j = 2*i; j <= N; j = j + i) {
            array[j] = 0;
        }
    }
    
    for(i = 0; i <= N; i++) {   //素数を表示
        if(array[i] != 0) printf("%d\n",array[i]);
    }

    end = time(NULL);
    printf("%ld sec\n",end - start);
}