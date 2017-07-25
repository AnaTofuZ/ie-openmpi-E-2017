#include <iostream>
#include <omp.h>

int main() {
  #pragma omp parallel
  {
    // ここがコア数分だけ並列に実行される。１コアだと１つです。
    printf("Hello, World ! %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
  }
  return 0;
}