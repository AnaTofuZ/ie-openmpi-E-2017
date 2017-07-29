#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>

#define DATA_SIZE 100
#define MAX_DIV 2

typedef struct _thread_arg_t{
    int *pn;
    int length;
    int divided_count;
} thread_arg_t;

/* 結果を表示する関数 */
void printnum(int *data, int size) {
    int i;
    for (i = 0; i < size; i++) 
        printf("%d ", data[i]);
    printf("\n");
    return;
}

/*　swap　*/
void swap(int *pn1, int *pn2) {
    int tmp = *pn1; *pn1 = *pn2; *pn2 = tmp;
}

/* quick sortをpnに対して行う */
void quick_sort(int *pn, int left, int right) {
    int i, j;

    if (left >= right) return;

    j = left;
    for (i = left + 1; i <= right; i++) {
        if (*(pn + i) < *(pn + left)) 
            swap(pn + (++j), pn + i);
    }
    swap(pn + left, pn + j);

    /* 再帰的に quick sort */
    quick_sort(pn, left, j - 1);
    quick_sort(pn, j + 1, right);

}

/* mergesortをqn1、qn2に対して行い、qnを返す */
void merge(int *pn1, int len1, int *pn2, int len2, int *pn) {
    int u1 = 0, u2 = 0;

    while (u1 < len1 || u2 < len2)
    {
        if ((u2 >= len2) || ((u1 < len1) && (pn1[u1] < pn2[u2]))) {
            pn[u1 + u2] = pn1[u1]; u1++;
        } else {
            pn[u1 + u2] = pn2[u2]; u2++;
        }
    }
}

/*---------------------------------
 * thread_merge_func
 * もし分解できれば子スレッドを生成し仕事を分解
 * 終了後、結果を統合して親に返す。
 *---------------------------------*/
void thread_merge_func(void *arg) {
    thread_arg_t *targ = (thread_arg_t *)arg;
    pthread_t handle[2];
    int len1, len2;
    thread_arg_t c_targ[2];

    if (targ->length <= 1) {
        /* これ以上分割できない場合は処理しない*/
    }else if (targ->divided_count >= MAX_DIV) {
        /* 分割条件Over */
        quick_sort(targ->pn, 0, targ->length - 1); 
    } else {
        /* 配列の分解 */
        len1 = targ->length / 2;
        len2 = targ->length - len1;

        /* create child args */
        c_targ[0].pn = (int *)malloc(sizeof(int) * len1);
        c_targ[1].pn = (int *)malloc(sizeof(int) * len2);
        memcpy(c_targ[0].pn, targ->pn, len1 * sizeof(int));
        memcpy(c_targ[1].pn, targ->pn + len1, len2 * sizeof(int));

        c_targ[0].length = len1;
        c_targ[0].divided_count = targ->divided_count + 1;

        c_targ[1].length = len2;
        c_targ[1].divided_count = targ->divided_count + 1;

        /* 子スレッドの生成 */
        pthread_create(&handle[0], NULL, (void *)thread_merge_func,
                (void *)&c_targ[0]);
        pthread_create(&handle[1], NULL, (void *)thread_merge_func,
                (void *)&c_targ[1]);

        /* 子スレッドの終了を待つ */
        pthread_join(handle[0], NULL);
        pthread_join(handle[1], NULL);

        /* 結果をマージする */
        merge(c_targ[0].pn, len1, c_targ[1].pn, len2, targ->pn);

        free(c_targ[0].pn);
        free(c_targ[1].pn);
    }
    return;
}


/*---------------------------------
 * main
 *---------------------------------*/
int main() {
    int i;
    thread_arg_t targ;

    /* ランダムな数列を初期化 */
    targ.pn = (int *)malloc(sizeof(int) * DATA_SIZE);
    srand((unsigned int)time(NULL));
    for (i = 0; i < DATA_SIZE; i++)
        targ.pn[i] = rand();

    /* ソート前の数列の表示 */
    printf("before\n");
    printnum(targ.pn, DATA_SIZE);

    /* パラメータの設定 */
    targ.divided_count = 0;         /* 分割数 */
    targ.length = DATA_SIZE;        /* データの個数 */

    /* merge-sort */
    thread_merge_func(&targ);

    /* ソート後の数列の表示 */
    printf("after\n");
    printnum(targ.pn, DATA_SIZE);

    return 0;
}

