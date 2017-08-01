
#ifdef _OEPNMP
#include <omp.h>
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_DATA 1000

static long temp[MAX_DATA];    /* 最小でも配列と同じサイズの領域が必要 */

void MergeSort(long x[ ], long left, long right);
void main(void);

  /* 配列 x[ ] の left から right の要素のマージソートを行う */
void MergeSort(long x[ ], long left, long right)
{
    long mid, i, j, k;
	
    if (left >= right)              /* 配列の要素がひとつなら */
        return;                     /* 何もしないで戻る */

                                    /* ここでは分割しているだけ */
    mid = (left + right) / 2;       /* 中央の値より */
    MergeSort(x, left, mid);        /* 左を再帰呼び出し */
    MergeSort(x, mid + 1, right);   /* 右を再帰呼び出し */

      /* x[left] から x[mid] を作業領域にコピー */
    for (i = left; i <= mid; i++)
        temp[i] = x[i];

      /* x[mid + 1] から x[right] は逆順にコピー */
    for (i = mid + 1, j = right; i <= right; i++, j--)
        temp[i] = x[j];

    i = left;         /* i とj は作業領域のデーターを */
    j = right;        /* k は配列の要素を指している */

    for (k = left; k <= right; k++)    /* 小さい方から配列に戻す */
        if (temp[i] <= temp[j])        /* ここでソートされる */
            x[k] = temp[i++];
        else
            x[k] = temp[j--];
}



void main(void)
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

    start = clock();
    MergeSort(x, 0, MAX_DATA - 1);
    end = clock();


    printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
}

