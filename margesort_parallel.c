#ifdef _OEPNMP
#include <omp.h>
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_DATA 1000

static long temp[MAX_DATA];    /* 最小でも配列と同じサイズの領域が必要 */

void MergeSort(long x[ ], long left, long right, long depth);

static long depth=0;

  /* 配列 x[ ] の left から right の要素のマージソートを行う */
void MergeSort(long x[ ], long left, long right, long depth)
{
    long mid, i, j, k;
	


//	printf("%d,%d,left=%d,right=%d\n",count,count2,left,right);
    if (left >= right){              /* 配列の要素がひとつなら */
        return;                     /* 何もしないで戻る */
	}

    mid = (left + right) / 2;       /* 中央の値より */

//	printf("mid=%d\n",mid);


/*	  #pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right)
	  {
		#pragma omp sections
		{
		  #pragma omp section
		  MergeSort(x, left, mid);        // 左を再帰呼び出し
		  #pragma omp section
		  MergeSort(x, mid + 1, right);   // 右を再帰呼び出し
		}
	  }
*/

/*		#pragma omp parallel sections
		{
		  #pragma omp section
		  MergeSort(x, left, mid);        // 左を再帰呼び出し
		  #pragma omp section
		  MergeSort(x, mid + 1, right);   // 右を再帰呼び出し
		}
*/


/*

	  if(isCreateTreadL == 0 && isCreateTreadR == 0){
		#pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right)
		{
		  MergeSort(x, left, mid,1,0);        // 左を再帰呼び出し
		  MergeSort(x, mid + 1, right,0,1);   // 右を再帰呼び出し
		}
	  }else if(isCreateTreadL == 0 && isCreateTreadR == 1){
		MergeSort(x, mid + 1, right,0,1);   // 右を再帰呼び出し
		#pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right)
		{
		  MergeSort(x, left, mid,1,0);        // 左を再帰呼び出し
		}
	  }else if(isCreateTreadL == 1 && isCreateTreadR == 0){
		MergeSort(x, left, mid,1,0);        // 左を再帰呼び出し
		#pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right)
		{
		  MergeSort(x, mid + 1, right,0,1);   // 右を再帰呼び出し
		}
	  }
*/


/*
	  if(isCreateTreadL == 0 && isCreateTreadR == 0){
		#pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right)
		{
		  #pragma omp sections
		  {
			#pragma omp section
			MergeSort(x, left, mid,1,0);        // 左を再帰呼び出し
			#pragma omp section
			MergeSort(x, mid + 1, right,0,1);   // 右を再帰呼び出し
		  }
		}
	  }else if(isCreateTreadL == 0 && isCreateTreadR == 1){
		#pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right)
		{
		  #pragma omp sections
		  {
			#pragma omp section
			MergeSort(x, left, mid,1,1);        // 左を再帰呼び出し
			#pragma omp section
			MergeSort(x, mid + 1, right,0,1);   // 右を再帰呼び出し
		  }
		}
	  }else if(isCreateTreadL == 1 && isCreateTreadR == 0){
		#pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right)
		{
		  #pragma omp sections
		  {
			#pragma omp section
			MergeSort(x, mid + 1, right,1,1);   // 右を再帰呼び出し
			#pragma omp section
			MergeSort(x, left, mid,1,0);        // 左を再帰呼び出し
		  }
		}
	  }else if(isCreateTreadL == 1 && isCreateTreadR == 1){
		MergeSort(x, left, mid,1,1);        // 左を再帰呼び出し
		MergeSort(x, mid + 1, right,1,1);   // 右を再帰呼び出し
	  }


*/


	if((omp_get_thread_num() == (omp_get_max_threads()-1)) && (omp_get_max_threads() < (2^depth))){
	  #pragma omp parallel num_threads(1) shared(x),firstprivate(left,mid,right,depth)
	  {
		#pragma omp sections
		{
		  #pragma omp section
		  MergeSort(x, left, mid,depth+1);        // 左を再帰呼び出し
		  #pragma omp section
		  MergeSort(x, mid + 1, right,depth+1);   // 右を再帰呼び出し
		}
	  }

	}else{
	  MergeSort(x, left, mid,depth+1);        // 左を再帰呼び出し
	  MergeSort(x, mid + 1, right,depth+1);   // 右を再帰呼び出し

	}


      /* x[left] から x[mid] を作業領域にコピー */
    for (i  = left; i <= mid; i++)
        temp[i] = x[i];


      /* x[mid + 1] から x[right] は逆順にコピー */
	j = right;
    for (i = mid + 1; i <= right; i++)
	{
        temp[i] = x[j];
		j--;
	}


    i = left;         /* i とj は作業領域のデーターを */
    j = right;        /* k は配列の要素を指している */


    for (k = left; k <= right; k++){    /* 小さい方から配列に戻す */
        if (temp[i] <= temp[j])        /* ここでソートされる */
            x[k] = temp[i++];
        else
            x[k] = temp[j--];
	}


}



int main(void)
{

	static long x[MAX_DATA] = {0};
	static long y[10] = {3,6,8,9,0,2,1,4,5,7};
	fprintf(stderr, "exe1\n");
    int i;
    clock_t start,end;
      /* ソートされるデータ */

    srand((unsigned)time(NULL));

    for (long j=0; j<MAX_DATA; j++) {
      x[j] = rand();

    }

      /* ソート前のデータを表示 */
/*    printf("ソート前\n");
    for (i = 0; i < MAX_DATA; i++)
        printf("%d\t", x[i]);

*/



      /* ソート前のデータを表示 */
    printf("ソート前\n");
    for (i = 0; i < 10; i++)
        printf("%d\t", y[i]);
	printf("\n");

    start = clock();
	
	MergeSort(y, (long)0, (long)10 - 1,0);
    end = clock();
    printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);

      /* ソート後のデータを表示 */
    fprintf(stderr,"ソート後\n");
    for (i = 0; i < 10; i++)
        fprintf(stderr,"%d\t", y[i]);
	printf("\n");

    start = clock();
	MergeSort(x, (long)0, (long)MAX_DATA - 1,0);
    end = clock();
    printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);



      /* ソート後のデータを表示 */
/*    printf("ソート後\n");
    for (i = 0; i < MAX_DATA; i++)
        printf("%d\t", x[i]);
*/

	return 0;
}

