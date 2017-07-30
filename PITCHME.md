# 並列分散処理 E班

## OpenMP


 [Github](https://github.com/AnaTofuZ/ie-openmpi-E-2017)


---
## 内容

- OpenMPについて
- Pthreadとの比較実験
  - 素数判定
  - マージソート
  - 円周率
- まとめ

---

## OpenMPについて

+++
- OpenMP は非営利団体 
OpenMP Architecture Review Board（ARB）によって規定されている業界標準規格です。
- **共有メモリ型** 並列計算機用のプログラムの並列化を記述するための指示文、ライブラリ関数、環境変数などが規定されています。

+++

### 特徴

- Pthreadなどと比較して簡易な記述
- 基本のC言語のソースコードにあまり手をつけずに作る事が可能
- 最近のコンパイラに標準搭載され始めている
    - Macでも動くぞ!!

+++

### サンプルコード

``` C
#include<stdio.h>
#include<omp.h>

int main(){
    int a[1000];
    int b[1000];
    int c[1000];
    int i;

    #pragma omp parallel for
    for(i=0;i<1000;i++){
        a[i] = i;
        b[i] = 1;
        c[i] = a[i] + b[i];
    }

    for(i=0;i<1000;i++){
        printf("%d\n",c[i]);
    }

  return 0;
}
```
@[10](指示子を使うことで簡単に並列化出来る)

---

## 素数を求める

+++

### 単一処理

---?code=Prime.c

10000000 以下の素数を求めている
素数を求めるアルゴリズムは,エラトステネスの篩を参考にしている

---

# 参考資料

- [今回のリポジトリ](https://github.com/AnaTofuZ/ie-openmpi-E-2017)
- [POSIX THREADS AND OPENMP(SHARED MEMORY PARADIGM)](https://www.cs.uic.edu/~ajayk/c567/Presentation_POSIX_OpenMP.pdf)
- [An Overview of OpenMP](http://www.openmp.org/wp-content/uploads/ntu-vanderpas.pdf)
- [Sun Studio 12: OpenMP API ユーザーズガイド](https://docs.oracle.com/cd/E19205-01/820-1217/index.html)
- [OpenMPの基礎](http://www.cms-initiative.jp/ja/events/20130425katagiri.pdf)
- [OpenMPで多重forループを並列化して配列に格納する方法](http://auewe.hatenablog.com/entry/2013/10/16/054345)
- [マルチコアCPUのための並列プログラミング](https://www.amazon.co.jp/%E3%83%9E%E3%83%AB%E3%83%81%E3%82%B3%E3%82%A2CPU%E3%81%AE%E3%81%9F%E3%82%81%E3%81%AE%E4%B8%A6%E5%88%97%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0-%E5%AE%89%E7%94%B0-%E7%B5%B9%E5%AD%90/dp/4798014621)
