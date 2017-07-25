#include <stdio.h>
#include <omp.h>

int main(int argc, char const* argv[])
{
  int n;
  n = omp_get_max_threads(); // デフォルドのスレッド数を取得
  printf("max threads (default): %d\n",n);

  omp_set_num_threads(16);   // スレッド数を変更
  n = omp_get_max_threads(); // スレッド数を再取得
  printf("max threads (set): %d\n",n);

    
  // 並列処理  配列array[i]に i を入れる
  int a[10], i;
  #pragma omp parallel for
  for(i = 0; i < 10; i++)
  {
    a[i] = i;
    printf("parallel: %d\n", i);
  }

  // 配列に正しく入ったか表示
  printf("a[0]:%d a[1]:%d a[2]:%d a[9]:%d\n", a[0],a[1],a[2],a[9]);

  return 0;
}