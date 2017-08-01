#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

#define MAX_DATA 100000000

void simple_merge(long a[],long low,long mid,long high);
void merge_sort(long a[],long low,long high);

int main()
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
    fprintf(stderr, "exe2\n");

    start = clock();
    merge_sort(y,1,10);
    end = clock();
    printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);

    printf("ソート前\n");
    for (i = 0; i < 10; i++)
        printf("%d\t", y[i]);


    start = clock();
    merge_sort(y,1,MAX_DATA);
    end = clock();
    printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);

}
 
void simple_merge(long a[],long low,long mid,long high)
{
    long i=low,j=mid+1,k=low;
	static long c[MAX_DATA];
    while(i<=mid && j<=high)
    {
        if(a[i]<a[j])
        {
            c[k]=a[i];
            i++;
            k++;
        }
        else
        {
            c[k]=a[j];
            j++;
            k++;
        }
    }
    while(i<=mid)
        c[k+1]=a[i++];
    while(j<=high)
        c[k++]=a[j++];
    for(i=low;i<=high;i++)
        a[i]=c[i];
}
void merge_sort(long a[],long low,long high)
{
    long mid;
    if(low<high)
    {
        mid=(low+high)/2;
//        #pragma omp parallel sections
//        {
//            #pragma omp section
            merge_sort(a,low,mid);    
//            #pragma omp section
            merge_sort(a,mid+1,high);
//       }
        simple_merge(a,low,mid,high);
    }
}        
