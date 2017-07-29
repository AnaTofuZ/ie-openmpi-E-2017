#ifdef _OEPNMP
#include <omp.h>
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_DATA 100000000

static long temp[MAX_DATA];    /* 最小でも配列と同じサイズの領域が必要 */
static int log;

void MergeSort(long x[ ], long left, long right);

static unsigned long count=0;
static unsigned long count2=0;
static unsigned long count3=0;

  /* 配列 x[ ] の left から right の要素のマージソートを行う */
void MergeSort(long x[ ], long left, long right)
{
    long mid,  j, k;
	


//	printf("%d,%d,left=%d,right=%d\n",count,count2,left,right);
    if (left >= right){              /* 配列の要素がひとつなら */
        return;                     /* 何もしないで戻る */
	}

    mid = (left + right) / 2;       /* 中央の値より */

//	printf("mid=%d\n",mid);
	  MergeSort(x, left, mid);        /* 左を再帰呼び出し */
	  MergeSort(x, mid + 1, right);   /* 右を再帰呼び出し */

	#pragma omp sections
	{
	#pragma omp section
	{
      /* x[left] から x[mid] を作業領域にコピー */
	#pragma omp parallel for schedule(guided)
    for (long i  = left; i <= mid; i++)
        temp[i] = x[i];
	}


	#pragma omp section
	{
      /* x[mid + 1] から x[right] は逆順にコピー */
	j = right;
	#pragma omp parallel for schedule(guided)
    for (long i = mid + 1; i <= right; i++)
	{
        temp[i] = x[j];
	}
	}
	}

    long i = left;         /* i とj は作業領域のデーターを */
    j = right;        /* k は配列の要素を指している */

	#pragma omp parallel for schedule(guided)
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

    start = clock();
	MergeSort(x, (long)0, (long)MAX_DATA - 1);
    end = clock();

      /* ソート後のデータを表示 */
/*    printf("ソート後\n");
    for (i = 0; i < MAX_DATA; i++)
        printf("%d\t", x[i]);
*/

    printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}

