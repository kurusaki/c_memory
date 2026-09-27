# C言語の壁を越えよう！
## ～メモリの世界から理解するC言語～

## 第14回 char配列とcharポインタ

同じHelloが表示されるのに、配列とポインタは何が違うのでしょうか。今回は `char name[] = "Hello";` と `const char *ptr = "Hello";` を比較し、変数自身に保存されるもの、サイズ、書き換えの違いをメモリから確認します。

動画リンク：https://youtu.be/iCJoNtPXQKc

## この回で学ぶこと

- char配列とcharポインタの違い
- `sizeof` と `strlen` が調べるもの
- ポインタ変数自身と指し先のメモリの違い
- 文字列リテラルと `const` の役割
- 文字を書き換える操作と指し先を変える操作の違い
- 書き換え可能な配列をcharポインタで扱う方法

## ファイル構成

```text
samples/
├── mdump.c
├── mdump.h
└── 14_char_array_pointer/
    ├── README.md
    ├── array_pointer.c
    └── pointer_to_array.c
```

- [array_pointer.c](array_pointer.c)：配列とポインタのサイズ、アドレス、メモリを比較する。
- [pointer_to_array.c](pointer_to_array.c)：配列を指すポインタから文字を書き換える。
- [mdump.c](../mdump.c)・[mdump.h](../mdump.h)：シリーズ共通のメモリダンプ関数。

## 1. 配列とポインタを比較する

ファイル名：`array_pointer.c`

```c
#include <stdio.h>
#include <string.h>
#include "../mdump.h"

int main(void)
{
    char name[] = "Hello";
    const char *ptr = "Hello";

    printf("name = %s\n", name);
    printf("ptr  = %s\n", ptr);
    printf("sizeof(name) = %zu\n", sizeof(name));
    printf("sizeof(ptr)  = %zu\n", sizeof(ptr));
    printf("strlen(name) = %zu\n", strlen(name));
    printf("strlen(ptr)  = %zu\n", strlen(ptr));

    printf("\nAddress:\n");
    printf("name = %p\n", (void *)name);
    printf("ptr  = %p\n", (void *)ptr);
    printf("&ptr = %p\n", (void *)&ptr);

    printf("\nArray memory:\n");
    mdump(name, sizeof(name));
    printf("\nPointer variable memory:\n");
    mdump(&ptr, sizeof(ptr));
    printf("\nString pointed to by ptr:\n");
    mdump(ptr, strlen(ptr) + 1);

    name[0] = 'h';
    ptr = "World";

    printf("\nAfter changes:\n");
    printf("name = %s\n", name);
    printf("ptr  = %s\n", ptr);

    return 0;
}
```

### コンパイルと実行

macOS・clangを使用する例です。リポジトリのルート（`c_memory`）から移動します。

```sh
cd samples/14_char_array_pointer
```

サンプルと1つ上の階層にある共通の `mdump.c` を一緒にコンパイルします。

```sh
clang -std=c17 -Wall -Wextra -Wpedantic array_pointer.c ../mdump.c -o array_pointer
./array_pointer
```

実行結果の例：

```text
name = Hello
ptr  = Hello
sizeof(name) = 6
sizeof(ptr)  = 8
strlen(name) = 5
strlen(ptr)  = 5

Address:
name = 0x16da22a74
ptr  = 0x1023dc850
&ptr = 0x16da22a68

Array memory:
0x16da22a74 : 48 65 6C 6C 6F 00                                Hello.

Pointer variable memory:
0x16da22a68 : 50 C8 3D 02 01 00 00 00                          P.=.....

String pointed to by ptr:
0x1023dc850 : 48 65 6C 6C 6F 00                                Hello.

After changes:
name = hello
ptr  = World
```

アドレスは実行例で、実行環境や実行のたびに変わる場合があります。ポインタのサイズや表現は環境に依存します。以下の説明は、ASCIIと互換性のある文字コードと、8バイトのポインタを使用する今回のmacOS環境に基づきます。

### 配列には文字、ポインタ変数にはアドレスが入る

ファイル名：`array_pointer.c`（抜粋）

```c
char name[] = "Hello";
const char *ptr = "Hello";
```

nameはchar型の配列です。要素数を省略した今回の初期化では、Helloの5文字と終端のヌル文字を格納する、6要素の配列になります。文字の並びを配列自身が持ちます。

一方、ptrは文字を指すポインタ変数です。`"Hello"` のようにダブルクォートで囲まれた表記を文字列リテラルと呼びます。ptrは、その文字列リテラルの先頭を指します。ptr自身にHelloの6バイトが入るわけではありません。

```text
配列name
[ H ][ e ][ l ][ l ][ o ][ \0 ]

ポインタ変数ptr           文字列リテラル
[ アドレス ] ─────────→ [ H ][ e ][ l ][ l ][ o ][ \0 ]
```

ここでの `const char *` は、ptrを通して指し先の文字を書き換えないことを型で表しています。文字列リテラルへの書き込みを避けるため、今回はこちらの宣言を使っています。

### sizeofとstrlenは別のものを調べる

`sizeof(name)` は配列全体のサイズで、終端を含めて6バイトです。一方、`sizeof(ptr)` はポインタ変数自身のサイズです。今回の環境では8バイトですが、これは指し先の文字列のサイズではありません。

`strlen` は `<string.h>` で宣言される関数です。最初のヌル文字までのバイト数を、終端を含めずに数えます。初期状態ではどちらもHelloなので、`strlen(name)` と `strlen(ptr)` はともに5です。戻り値や `sizeof` の結果を表示するために `%zu` を使っています。

```text
sizeof(name) = 6  配列全体
sizeof(ptr)  = 8  ポインタ変数自身（今回の環境）
strlen(name) = 5  終端を含めない文字列のバイト数
strlen(ptr)  = 5  終端を含めない文字列のバイト数
```

今回の英字では文字数とバイト数が一致します。UTF-8の日本語などでは、`strlen` の値と見た目の文字数が一致しない場合があります。また、`strlen` は有効なヌル終端文字列を渡すことが前提です。

### name、ptr、&ptrを区別する

アドレスを表示する際、nameは先頭要素を指すポインタに変換されます。ptrは、ポインタ変数が持つ値そのものです。そして `&ptr` は、ポインタ変数自身が置かれているアドレスです。

- name：この式では配列の先頭要素を指すポインタに変換される。
- ptr：文字列リテラルの先頭を指すポインタ値。
- `&ptr`：ポインタ変数ptr自身のアドレス。

`%p` に渡す引数は、表示用に `(void *)` へ変換しています。

配列名は多くの式で先頭要素を指すポインタに変換されますが、配列そのものがポインタ変数になるわけではありません。例えば `sizeof(name)` では配列からポインタへの変換は起きず、配列全体のサイズを求めます。

### 3つのメモリダンプが見ているもの

ファイル名：`array_pointer.c`（抜粋）

```c
mdump(name, sizeof(name));
mdump(&ptr, sizeof(ptr));
mdump(ptr, strlen(ptr) + 1);
```

最初の呼び出しは、配列の先頭から6バイトを表示します。結果は `48 65 6C 6C 6F 00` で、Helloと終端のヌル文字です。

2つ目はポインタ変数自身のメモリです。`&ptr` から `sizeof(ptr)` バイトを表示するので、今回の環境では8バイトのアドレス表現が見えます。文字コードのHelloが入っているわけではありません。

3つ目はptrの指し先です。`strlen(ptr) + 1` を指定し、終端を含む6バイトを表示します。こちらではHelloの文字コードが見えます。

**ポインタの指し先のサイズを、`sizeof(ptr)` で調べることはできません。** ここで `mdump(ptr, sizeof(ptr))` とすると、今回の環境では6バイトの文字列リテラルに対して8バイトを読もうとし、領域外への読み取りになります。

### ポインタ変数のダンプを読む

今回の実行例でptrが指すアドレスは `0x1023dc850` です。ポインタ変数のメモリには、次のバイト列が保存されています。

```text
50 C8 3D 02 01 00 00 00
```

今回の環境では8バイトのリトルエンディアンで表現されるため、アドレスの低い桁のバイトから並びます。ポインタ値とダンプの内容は、同じ実行の結果を組み合わせて確認してください。

なお、mdumpの右側にある点は、表示できないバイトを点に置き換えたものです。点そのものが保存されているとは限りません。

## 2. 文字を書き換える操作と、指し先を変える操作

ファイル名：`array_pointer.c`（抜粋）

```c
name[0] = 'h';
ptr = "World";
```

`name[0] = 'h';` は、配列の最初の要素を書き換えます。nameは書き換え可能な配列なので、Helloはhelloになります。

`ptr = "World";` は、ポインタ変数の値を別のアドレスに変更する操作です。Helloの文字列リテラルを書き換えたのではなく、Worldの先頭を指すようになっています。

```text
name[0] = 'h';  → 保存されている文字が変わる
ptr = "World"; → 指し先が変わる
```

`const char *ptr` のconstが制限するのは、ptrを通した文字の書き換えです。ptr自身の指し先を変更することはできます。

一方、配列に対して、宣言後に `name = "World";` と代入することはできません。配列を文字列で初期化することと、配列へ後から代入することは別です。配列に別の文字列を格納するには、十分な領域を確保したうえで各要素へ文字と終端を書き込む必要があります。

## 3. ポインタから配列の文字を書き換える

「ポインタからは文字を書き換えられない」というわけではありません。書き換え可能な配列を `char *` で指す例を確認しましょう。

ファイル名：`pointer_to_array.c`

```c
#include <stdio.h>

int main(void)
{
    char name[] = "Hello";
    char *ptr = name;

    ptr[0] = 'h';

    printf("name = %s\n", name);
    printf("ptr  = %s\n", ptr);

    return 0;
}
```

こちらはmdumpを使用しないため、単独でコンパイルできます。同じ `samples/14_char_array_pointer` ディレクトリで実行します。

```sh
clang -std=c17 -Wall -Wextra -Wpedantic pointer_to_array.c -o pointer_to_array
./pointer_to_array
```

実行結果：

```text
name = hello
ptr  = hello
```

`char *ptr = name;` では、ptrは配列nameの先頭を指します。`ptr[0] = 'h';` はその配列の最初の要素を変更するので、nameから表示してもptrから表示してもhelloになります。

```text
ptr ───→ name
         [ h ][ e ][ l ][ l ][ o ][ \0 ]
```

ptr専用の文字列が別に作られるわけではありません。同じ配列に、ポインタを通してアクセスしています。

## 4. 文字列リテラルは書き換えない

ここからは、配列nameを指す例から、文字列リテラルを直接指す例へ切り替えます。以下の説明用コードは `pointer_to_array.c` への追記ではありません。

### 文字列リテラルを直接指す場合

説明用コード：

```c
char *ptr = "Hello";
```

この宣言はCでは書けます。ただし、先ほどの `char *ptr = name;` と違い、ptrが指しているのは書き換え可能な配列nameではなく、文字列リテラルです。

```text
ptr ───→ 文字列リテラル
         [ H ][ e ][ l ][ l ][ o ][ \0 ]
```

### 書き換えてはいけない例

説明用コード（未定義動作を含むため実行しない例）：

```c
char *ptr = "Hello";
ptr[0] = 'h';  // 未定義動作：実行しない
```

文字列リテラルを変更する操作は未定義動作です。コンパイルできても正しい操作とは限りません。異常終了する場合もありますが、必ず異常終了するという保証もなく、動作は保証されません。

一方、`pointer_to_array.c` の `ptr[0] = 'h';` は、書き換え可能な配列nameを対象にしているため正しい操作です。同じ代入の形でも、指し先が異なります。

### constで誤った書き込みを防ぐ

ファイル名：`array_pointer.c`（宣言部分の抜粋）

```c
const char *ptr = "Hello";
```

今回のサンプルでは、文字列リテラルを指す変数を `const char *ptr` と宣言しています。これにより、`ptr[0] = 'h';` のような書き込みをコンパイラが診断できます。constを付けたから文字列リテラルが書き換え禁止になったのではなく、もともと変更してはいけない対象を指していることを、型でも表しています。

`ptr = "World";` は指し先を変更する操作なので、この宣言でも可能です。文字を書き換えたい場合は、2つ目のサンプルのように書き換え可能な配列を用意します。判断するのは「ポインタかどうか」だけではなく、**指し先が書き換え可能か、ポインタの型が書き換えを許しているか**です。

## 自分でも確かめてみよう

1. `array_pointer.c` の配列の初期値だけを `"Hi"` に変えると、`sizeof(name)` は3、`strlen(name)` は2になります。ptr側のHelloやポインタ変数のサイズは変わりません。
2. `pointer_to_array.c` の代入を `ptr[1] = 'a';` に変えると、両方の表示がHalloになります。元の配列の2番目の要素が変わるためです。

## まとめ

- 配列自身には文字列の各文字と終端を保存する。
- ポインタ変数には指し先のアドレスを保存する。
- `sizeof(name)` は配列全体、`sizeof(ptr)` はポインタ変数自身のサイズ。
- `strlen` は終端を含めない文字列のバイト数を求める。
- 配列の文字を書き換えることと、ポインタの指し先を変えることは別の操作。
- 書き換え可能な配列はcharポインタを通して変更できるが、文字列リテラルは変更してはいけない。

## シリーズ・関連リンク

- [シリーズ一覧](../../README.md#目次)
- [前回：第13回 文字列の正体](../13_string_memory/README.md)
- [前回のYouTube動画](https://youtu.be/j8L0b21zwKU)
- [第8回：配列とポインタは同じ？](../08_array_pointer/README.md)
- [第12回：構造体ポインタとアロー演算子](../12_struct_pointer/README.md)
- [CodeBoost Labo（YouTube）](https://www.youtube.com/@CodeBoostLabo)

