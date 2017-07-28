# 並列分散処理 E班

## OpenMP


 [このへん](http://paiza.hatenablog.com/entry/2017/06/22/GitHub%E3%81%A0%E3%81%91%E3%81%A7%E8%B6%85%E9%AB%98%E6%A9%9F%E8%83%BD%E3%81%AA%E3%82%B9%E3%83%A9%E3%82%A4%E3%83%89%E8%B3%87%E6%96%99%E3%81%8C%E4%BD%9C%E3%82%8C%E3%82%8B%E3%80%8CGitPitch%E3%80%8D%E3%81%AE)


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

---

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

