# 第17回 mallocで配列を確保！初期化はどうする？

C言語の壁を越えよう！ 〜メモリの世界から理解するC言語〜

動画：制作中。公開URLは公開後に追記します。

## この回で学ぶこと

- 要素数 × 1要素のサイズで、配列として使う領域を確保する
- mallocの戻り値とNULLを確認する
- 初期化してから値を読む
- memsetとcallocの違いをメモリダンプで確認する
- 使い終わったらfreeで解放する（詳細は次回）

## サンプルコード

ファイル：`malloc_basic.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mdump.h"

int main(void)
{
    const size_t count = 3;
    int *values = malloc(count * sizeof *values);

    if (values == NULL) {
        fprintf(stderr, "malloc failed.\n");
        return 1;
    }

    memset(values, 0, count * sizeof *values);
    printf("after memset: %d %d %d\n",
           values[0], values[1], values[2]);
    mdump(values, count * sizeof *values);

    values[0] = 100;
    values[1] = 200;
    values[2] = 300;
    printf("malloc + assignment: %d %d %d\n",
           values[0], values[1], values[2]);
    mdump(values, count * sizeof *values);

    free(values);
    values = NULL;

    values = calloc(count, sizeof *values);
    if (values == NULL) {
        fprintf(stderr, "calloc failed.\n");
        return 1;
    }

    printf("calloc: %d %d %d\n",
           values[0], values[1], values[2]);
    mdump(values, count * sizeof *values);

    free(values);
    values = NULL;
    return 0;
}
```

要素数を3に固定し、基本操作が見える例にしています。実行時に決まる要素数にも応用できますが、その場合はサイズ計算のオーバーフローなども考慮します。

## コンパイルと実行

リポジトリのルートから移動：

```sh
cd samples/17_malloc
```

コンパイル：

```sh
clang -std=c17 -O0 -Wall -Wextra -Wpedantic malloc_basic.c ../mdump.c -o malloc_basic
```

実行（別のコマンド）：

```sh
./malloc_basic
```

共通のメモリダンプ関数 `../mdump.c` と `../mdump.h` を利用します。

## 実行結果（実測）

```text
after memset: 0 0 0
0x1014457f0 : 00 00 00 00 00 00 00 00 00 00 00 00              ............
malloc + assignment: 100 200 300
0x1014457f0 : 64 00 00 00 C8 00 00 00 2C 01 00 00              d.......,...
calloc: 0 0 0
0x1014457f0 : 00 00 00 00 00 00 00 00 00 00 00 00              ............
```

macOS上のclangでコンパイル・実行して確認した出力です。この環境では `sizeof(int)` は4で、リトルエンディアンです。アドレス・型のサイズ・バイト順は環境により異なります。この実行では解放後のcallocが同じアドレスを返しましたが、同じアドレスになる保証はありません。

## 必要なサイズは「個数 × 1個分」

`malloc(count * sizeof *values)` は、「要素数 × int型1個分のサイズ」を指定してメモリを確保します。

`values` はint型の値を指すポインタです。そのため、ここでの `sizeof *values` は `sizeof(int)` と同じ意味です。例えばint型が4バイトの環境なら、結果は4です。`*values` に100が入っていても200が入っていても、結果は変わりません。まだ値を入れていない場合も、型からサイズを求められます。

`values` は配列そのものではなく、確保した領域の先頭アドレスを保存するポインタ変数です。確保に成功した後、その領域を `values[0]` から `values[2]` までの3個のintとして使います。

`sizeof` の後に何を書くかで、調べる対象が変わります。

- `sizeof *values`：int型の値を1個保存するためのサイズ
- `sizeof values`：アドレスを保存するポインタ変数 `values` 自身のサイズ
- `count * sizeof *values`：今回確保したい、int型3個分のサイズ

例えば、intが4バイト、ポインタが8バイトの環境なら、それぞれ4バイト、8バイト、12バイトです。`sizeof values` を使っても、mallocで確保した12バイトという大きさは分かりません。確保した領域の大きさは、要素数と1個分のサイズから計算します。

## ポインタ自身と確保した領域

```mermaid
flowchart LR
    subgraph local[mainのローカル変数]
        values["values：先頭を指すポインタ"]
    end
    subgraph heap[ヒープ領域：代入後]
        array["values[0]：100 ｜ values[1]：200 ｜ values[2]：300"]
    end
    values --> array
```

mallocが確保する領域は一般的にヒープに置かれます。C規格そのものが「ヒープ」という配置を必須にしているわけではありません。ローカル変数 `values` 自身と、その指し先を区別します。mallocの戻り値は `void *` で、Cでは `int *` へキャストなしで代入できます。失敗時はNULLなので、指し先を使う前に確認します。

## mallocは初期化しない

確保しただけでは、各要素が0になる保証はありません。今回のサンプルは、まずmemsetでゼロに初期化し、その状態を表示・メモリダンプで確認します。その後、100、200、300を代入して、変更後の状態を確認します。初期化前のint値を読み出す実験は行いません。

## memset：確保済みの領域をバイト単位で埋める

```c
memset(values, 0, count * sizeof *values);
```

先頭から指定したバイト数を0で埋めます。int型では全ビット0が整数の0を表すため、この例の各要素は0になります。memset自体はメモリを確保しません。

このサンプルの流れは「mallocで確保 → memsetでゼロに初期化 → ゼロになった状態を確認 → 100・200・300を代入 → 代入後の状態を確認」です。

ゼロにする処理は、初期状態を確認するために入れています。今回のように後ですべての要素へ値を代入し、その後だけ読み出すプログラムなら、先にゼロにする処理は必須ではありません。

次のコードは各要素へ整数200を代入する処理ではありません（説明用。サンプルでは実行しません）。

```c
memset(values, 200, count * sizeof *values);
```

この処理は各バイトを `0xC8` で埋めます。4バイトのintなら `C8 C8 C8 C8` となり、整数200の表現とは異なります。各要素を200にしたい場合は、それぞれへ200を代入します。

## calloc：確保とゼロ埋め

```c
values = calloc(count, sizeof *values);
```

要素数と1要素のサイズを別々に渡し、確保した領域の全ビットを0にします。今回のint配列では、成功直後の各要素が0になります。callocでも失敗時のNULL確認が必要です。

今回のint型では、すべてのビットを0にすると、整数の0になります。ただし、double型の0.0も同じ形で保存されるとは限りません。double型の値を0.0にしたい場合は、`0.0` を代入します。

ポインタを初期化するときは、ゼロ埋めに頼らずNULLを代入します。

## free：使い終わった領域を解放する

```c
free(values);
values = NULL;
```

free後にその領域を読み書きしてはいけません。また、freeが変数を自動的にNULLへ変更するわけではありません。次の代入文でNULLを設定しています。サンプルではmallocで確保した領域を解放してから、callocで確保し直します。freeの詳細と注意点は次回に扱います。

## まとめ

| 操作 | メモリの確保 | 中身 |
|---|---|---|
| malloc | する | 初期化しない |
| memset | しない | 確保済みの領域をバイト単位で埋める |
| calloc | する | 全ビットを0にする |

確保・初期化・使用・解放を分けて考えましょう。

## シリーズ

- [第16回 スタックとヒープの違い](../16_stack_heap/)（[公開動画](https://youtu.be/OvsssrBBGe0)）
- 第17回 本ページ（動画制作中）
- 次回：freeの詳細（制作予定）
- [シリーズ一覧](../../README.md)

## 参考資料

- [GNU C Library：Basic Allocation](https://sourceware.org/glibc/manual/2.34/html_node/Basic-Allocation.html)
- [WG14 N1570：C11委員会草案](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)（6.5.3.4、6.2.6.2、7.22.3.2、7.22.3.4、7.24.6.1）
