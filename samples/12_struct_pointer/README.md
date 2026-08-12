
C言語の壁を越えよう！
## ～メモリの世界から理解するC言語～

#12 構造体ポインタと ->とは？ メモリから理解するアロー演算子

## この動画について

📺 **[動画はこちら](https://youtu.be/sEPobJQVBdI)**

構造体を使い始めると必ず登場する「->（アロー演算子）」。

「. と何が違うの？」
「なぜ -> を使うの？」

そんな疑問を、メモリの視点から分かりやすく解説します。

この動画では、構造体そのものと構造体ポインタの違いを確認しながら、`.` と `->` の使い分けや、`(*ptr).member` と `ptr->member` が同じ意味になる理由を学びます。

後半ではメモリダンプを使って、構造体のデータとポインタに保存されているアドレスを実際に確認します。

📚 この動画で学べること
・構造体ポインタとは何か
・`.` と `->` の違い
・`(*ptr).member` と `ptr->member` の関係
・構造体とポインタのメモリ構造
・mallocを使う前に知っておきたい基礎知識

📚 GitHub（サンプルコード）
https://github.com/kurusaki/c_memory/tree/develop/samples/12_struct_pointer

---

## この動画で学べること

- 構造体ポインタとは何か
- `.` と `->` の違い
- `(*ptr).member` と `ptr->member` の関係
- 構造体とポインタのメモリ構造
- mallocを使う前に知っておきたい基礎知識

---

## サンプルコード

この動画で使用したサンプルコードです。

- [sample1.c](sample1.c)
- [sample2.c](sample2.c)
- [sample3.c](sample4.c)

---

## 動画シナリオ

こんにちは、CodeBoost Laboです。

「C言語の壁を越えよう！
～メモリの世界から理解するC言語～」

今回は第12回です。

前回は、構造体がメモリ上にどのように配置されるのか、
そしてパディングやアライメントについて学びました。

今回は、その続きとして **構造体ポインタ** について学びます。

そして、多くの人が最初につまずく

```c
person.age
```

と

```c
ptr->age
```

の違いを、

今回もメモリダンプを見ながら理解していきます。

最後には構造体配列とポインタ演算も確認します。

それでは始めていきましょう。

---

### 今回使用するプログラム

【画面】

```text
samples/

├── mdump.c
├── mdump.h
│
└── 12_struct_pointer
    ├── sample1.c
    ├── sample2.c
    └── sample3.c
```

---

今回使用するディレクトリはこちらです。

今回も、メモリダンプ関数を定義している **mdump.c**、**mdump.h** は、

シリーズ共通で使用するため、一つ上のディレクトリに配置しています。

今回は

* sample1.c
* sample2.c
* sample3.c

の3つのプログラムを使って説明します。

まずは **sample1.c** から見ていきましょう。

---

### sample1.c

**sample1.c**

```c
#include <stdio.h>
#include "../mdump.h"

typedef struct
{
    int age;
    char grade;
} Person;

int main(void)
{
    Person person = {20, 'A'};

    printf("sizeof(Person) = %zu\n", sizeof(Person));
    printf("&person        = %p\n", (void *)&person);
    printf("&person.age    = %p\n", (void *)&person.age);
    printf("&person.grade  = %p\n", (void *)&person.grade);

    printf("\nPerson memory:\n");
    mdump(&person, sizeof(Person));

    return 0;
}
```

---

このプログラムでは、Person構造体を1つ作成しています。

```c
Person person = {20, 'A'};
```

そして、構造体全体のサイズ、構造体のアドレス、各メンバーのアドレスを表示し、

最後にmdump関数で構造体のメモリをダンプします。

前回学んだ構造体のメモリ配置を、もう一度確認するためのプログラムです。

---

### sample1.cをコンパイル

まずは、サンプルがあるディレクトリへ移動します。

```bash
cd 12_struct_pointer
```

コンパイルします。

```bash
clang sample1.c ../mdump.c -o sample1
```

今回も sample1.c と 一つ上のディレクトリにある mdump.c を一緒にコンパイルしています。

エラーが表示されなければ、コンパイル成功です。

---

### sample1を実行

続いて、プログラムを実行します。

```bash
./sample1
```


---

### sample1の実行結果

実行結果がこちらです。

```text
sizeof(Person) = 8
&person        = 0x16d39ade0
&person.age    = 0x16d39ade0
&person.grade  = 0x16d39ade4

Person memory:
0x16d39ade0 : 14 00 00 00 41 00 00 00                          ....A...
```

まず、Person構造体のサイズは 8バイトになっています。

これは前回学んだように、パディングが入るためです。

続いて、構造体全体のアドレスを見てみます。

```text
&person
```

そして、

ageのアドレス。

```text
&person.age
```

さらに、

gradeのアドレスです。

```text
&person.grade
```

ageは、構造体の先頭から配置されています。

gradeは、その4バイト後ろに配置されています。

---

### メモリ解析①

【画面】

```text
0x16d39ade0:
14 00 00 00
41 00 00 00
```

---

【ナレーション】

続いて、

メモリダンプを見てみましょう。

先頭の

```text
14 00 00 00
```

これは

16進数の

14です。

10進数にすると

20になります。

つまり、

ageの値です。

---

【画面】

```text
14 00 00 00

↓

20
```

---


リトルエンディアンなので、

下位バイトから保存されています。

---

### メモリ解析②

【画面】

```text
41
```

---

【ナレーション】

続いて、

41です。

16進数の41は

ASCIIコードで

'A'

です。

つまり、

gradeの値になります。

---

### メモリ解析③

【画面】

```text
14 00 00 00
41
00 00 00
```

---

【ナレーション】

その後ろには、3バイトの 00 が並んでいます。

これはパディングです。

構造体全体を8バイト境界に揃えるため、コンパイラが自動的に挿入しています。

前回学んだ内容と同じ結果になっています。

---

### メモリ図で整理

【画面】

```text
アドレス

0x16d39ade0
┌────┬────┬────┬────┐
│      age = 20      │
└────┴────┴────┴────┘

0x16d39ade4
┌────┬────┬────┬────┐
│ 'A' │ pad│ pad│ pad│
└────┴────┴────┴────┘
```

図にすると、このようになります。

先頭4バイトにage。

その次の1バイトにgrade。

最後の3バイトはパディングです。

このメモリ配置を理解しておくことが、

今回学ぶ構造体ポインタの理解にもつながります。

---

### 次へ

ここまでは、構造体そのものを見てきました。

次は、この構造体を**ポインタで扱う**場合を見ていきます。

構造体ポインタの中には、何が保存されているのでしょうか。

そして、なぜ

```c
ptr->age
```

と書けるのでしょうか。

次は、sample2.c を使って確認していきます。

---

## 第2部 sample2.c ～構造体ポインタとアロー演算子～

---

### sample2.c

**sample2.c**

```c
#include <stdio.h>
#include "../mdump.h"

typedef struct
{
    int age;
    char grade;
} Person;

int main(void)
{
    Person person = {20, 'A'};
    Person *ptr = &person;

    printf("sizeof(Person) = %zu\n", sizeof(Person));
    printf("sizeof(ptr)    = %zu\n", sizeof(ptr));

    printf("\nAddress:\n");
    printf("&person = %p\n", (void *)&person);
    printf("ptr     = %p\n", (void *)ptr);
    printf("&ptr    = %p\n", (void *)&ptr);

    printf("\nPerson memory:\n");
    mdump(&person, sizeof(Person));

    printf("\nPointer variable memory:\n");
    mdump(&ptr, sizeof(ptr));

    printf("\nMember access:\n");
    printf("person.age    = %d\n", person.age);
    printf("(*ptr).age    = %d\n", (*ptr).age);
    printf("ptr->age      = %d\n", ptr->age);

    printf("person.grade  = %c\n", person.grade);
    printf("(*ptr).grade  = %c\n", (*ptr).grade);
    printf("ptr->grade    = %c\n", ptr->grade);

    return 0;
}
```

---

このプログラムでは、先ほどと同じPerson構造体を作成しています。

そして今回は、

```c
Person *ptr = &person;
```

という1行が追加されています。

ここが今回のポイントです。

このコードは、**personのアドレスをptrへ代入する**という意味です。

つまり、ptrは構造体ではありません。

**構造体が保存されている場所を覚えているポインタ変数**です。

この違いを、実際のメモリを見ながら確認していきます。

---

### sample2.cをコンパイル

それでは、sample2.cをコンパイルします。

```bash
clang sample2.c ../mdump.c -o sample2
```

今回も sample2.cと一つ上のディレクトリにある mdump.c を一緒にコンパイルします。

エラーが表示されなければ成功です。

---

### sample2を実行

それでは実行します。

```bash
./sample2
```


---

### sample2の実行結果

実行結果がこちらです。

```text
sizeof(Person) = 8
sizeof(ptr)    = 8

Address:
&person = 0x16d48ede0
ptr     = 0x16d48ede0
&ptr    = 0x16d48edd8

Person memory:
0x16d48ede0 : 14 00 00 00 41 00 00 00                          ....A...

Pointer variable memory:
0x16d48edd8 : E0 ED 48 6D 01 00 00 00                          ..Hm....

Member access:
person.age    = 20
(*ptr).age    = 20
ptr->age      = 20
person.grade  = A
(*ptr).grade  = A
ptr->grade    = A
```

---

### アドレスを確認しよう

```text
Address:
&person = 0x16d48ede0
ptr     = 0x16d48ede0
&ptr    = 0x16d48edd8
```

まずは、この3つのアドレスに注目してください。

一番上は、person自身のアドレスです。

その下のptrを見ると、まったく同じアドレスになっています。

つまり、ptrの中にはpersonのアドレスが保存されています。

一方、&ptrはptr自身のアドレスです。

つまり、ptrという変数も、メモリ上に保存されています。

---

### メモリ図で整理

図にするとこのようになります。

```text
person

0x16d48ede0
┌─────────────────────┐
│ age = 20            │
│ grade = 'A'         │
│ padding             │
└─────────────────────┘


ptr

0x16d48edd8
┌─────────────────────┐
│ 0x16d48ede0         │
└─────────────────────┘
```

personには、構造体のデータそのものが保存されています。

一方、ptrには構造体ではなく、**構造体が保存されているアドレス**が保存されています。

ここが構造体と構造体ポインタの違いです。

---

### メモリダンプ

まず、personのメモリです。

```text
Person memory:
0x16d48ede0 : 14 00 00 00 41 00 00 00                          ....A...
```

これは前回と同じですね。

20と'A'が保存されています。

---

こちらは、ptr自身のメモリです。

```text
Pointer variable memory:
0x16d48edd8 : E0 ED 48 6D 01 00 00 00                          ..Hm....
```

先ほどは、構造体のデータが保存されていました。

しかし今回は違います。

保存されているのは**personのアドレス**です。

ポインタ変数はデータそのものではなく、**アドレスを保存する変数**であることが分かります。

---

### ドット演算子

それでは、メンバーへアクセスしてみます。

構造体そのものにはドット演算子を使います。

```c
person.age
```

これは、personという構造体のageを取り出す、という意味です。

---

### ptr.ageは？

では、こちらはどうでしょう。

```c
ptr.age
```

これは、コンパイルエラーになります。

なぜでしょうか。

ptrは、構造体ではありません。

ポインタだからです。

つまり、ptr自身にはageというメンバーは存在しません。

---

### (*ptr).age


正しくはこちらです。

```c
(*ptr).age
```

まず、

```c
*ptr
```

でポインタが指している構造体を取り出します。

そのあと、

```text
.
```

でageへアクセスしています。

つまり、処理の流れは

```text
ptr
↓
*ptr
↓
構造体
↓
.age
```

という順番になります。

---

### アロー演算子

しかし、毎回

```c
(*ptr).age
```

と書くのは大変です。

そこで、C言語ではアロー演算子が用意されています。

```c
ptr->age
```

これは、内部的には

```c
(*ptr).age
```

とまったく同じ意味です。

---

つまり、アロー演算子は**ポインタが指している構造体のメンバーへアクセスするための演算子**です。

```text
ptr->age

↓

(*ptr).age
```

---

### 実行結果を確認

実際の結果を見てみると、3つとも同じ値になっています。

```text
person.age    = 20
(*ptr).age    = 20
ptr->age      = 20

person.grade  = A
(*ptr).grade  = A
ptr->grade    = A
```

つまり、

```c
person.age
```

は、構造体そのものへアクセスしています。

一方、

```c
(*ptr).age
```

と

```c
ptr->age
```

は、どちらもポインタの先にある構造体へアクセスしています。

違うのは**書き方だけ**です。

---

### 次へ

ここまでで、構造体ポインタとアロー演算子の基本が理解できました。

次は、構造体配列を使って、ポインタを移動しながら

`ptr->age`

がどのように変化するのかを確認していきます。

第7回で学んだポインタ演算も復習しながら、構造体ポインタをさらに深く理解していきましょう。

---

## sample3.c ～構造体配列とポインタ演算～

---

### sample3.c


**sample3.c**

```c
#include <stdio.h>
#include "../mdump.h"

typedef struct
{
    int age;
    char grade;
} Person;

int main(void)
{
    Person people[3] = {
        {20, 'A'},
        {30, 'B'},
        {40, 'C'}
    };

    Person *ptr = people;

    printf("sizeof(Person) = %zu\n", sizeof(Person));
    printf("sizeof(people) = %zu\n", sizeof(people));

    printf("\nArray address:\n");
    printf("people     = %p\n", (void *)people);
    printf("&people[0] = %p\n", (void *)&people[0]);
    printf("&people[1] = %p\n", (void *)&people[1]);
    printf("&people[2] = %p\n", (void *)&people[2]);

    printf("\nPeople memory:\n");
    mdump(people, sizeof(people));

    printf("\nPointer access:\n");

    printf("ptr = %p, age = %d, grade = %c\n",
           (void *)ptr, ptr->age, ptr->grade);

    ptr++;

    printf("ptr = %p, age = %d, grade = %c\n",
           (void *)ptr, ptr->age, ptr->grade);

    ptr++;

    printf("ptr = %p, age = %d, grade = %c\n",
           (void *)ptr, ptr->age, ptr->grade);

    return 0;
}
```

---

### プログラムの説明

ここまでで、構造体ポインタとアロー演算子について学びました。

最後は、構造体配列を使って、ポインタがどのように移動するのかを確認します。

今回は、Person構造体を3つ持つ配列を作成しています。

```c
Person people[3]
```

そして、

```c
Person *ptr = people;
```

として、

ポインタを配列の先頭へ設定しています。

このあと、

```c
ptr++;
```

を実行すると、

ポインタがどのように移動するのかを見ていきます。

---

### sample3.cをコンパイル

それではコンパイルします。

```bash
clang sample3.c ../mdump.c -o sample3
```

今回も sample3.c と一つ上の階層にある mdump.c を一緒にコンパイルしています。

---

### Sample3を実行

それでは実行します。

```bash
./sample3
```

---

### Sample3の実行結果


```text
sizeof(Person) = 8
sizeof(people) = 24

Array address:
people     = 0x16b0cedd0
&people[0] = 0x16b0cedd0
&people[1] = 0x16b0cedd8
&people[2] = 0x16b0cede0

People memory:
0x16b0cedd0 : 14 00 00 00 41 00 00 00 1E 00 00 00 42 00 00 00  ....A.......B...
0x16b0cede0 : 28 00 00 00 43 00 00 00                          (...C...

Pointer access:
ptr = 0x16b0cedd0, age = 20, grade = A
ptr = 0x16b0cedd8, age = 30, grade = B
ptr = 0x16b0cede0, age = 40, grade = C
```

---

### 構造体配列

まず、構造体配列を見てみましょう。

```text
people

┌──────────────┐
│ people[0]    │
├──────────────┤
│ people[1]    │
├──────────────┤
│ people[2]    │
└──────────────┘
```

今回は、Person構造体が3つ連続してメモリ上へ配置されています。

配列なので、要素は隙間なく並んでいます。

---

### アドレスを確認

実際のアドレスを見ると、8バイトずつ増えていることが分かります。

```text
people[0]

0x16b0cedd0

people[1]

0x16b0cedd8

people[2]

0x16b0cede0
```

これは、

```c
sizeof(Person)
```

が 8バイトだからです。

---

### メモリダンプ

メモリダンプを見ると、Person構造体が3つ連続して保存されています。

```text
People memory:
0x16b0cedd0 : 14 00 00 00 41 00 00 00 1E 00 00 00 42 00 00 00  ....A.......B...
0x16b0cede0 : 28 00 00 00 43 00 00 00                          (...C...
```

最初は、20と'A'。

次は、30と'B'。

最後は、40と'C'。

構造体が、連続したメモリに配置されていることが分かります。

---

### ptr の初期状態

ここで

```c
Person *ptr = people;
```

としています。

つまり、ptrは配列の先頭、people[0]を指しています。

---

```text
ptr

↓

people[0]
```

---

### ptr++

ここで

```c
ptr++;
```

を実行します。

ポインタ演算では、1バイト進むのではありません。

型のサイズ分だけ進みます。

今回はPerson型なので、8バイト進みます。

---

```text
ptr

↓

people[0]

↓

ptr++

↓

people[1]
```

---

つまり、people[1]を指すようになります。

さらに

```c
ptr++;
```

すると、

people[2]

へ移動します。


---

### アドレスの変化


```text
Pointer access:
ptr = 0x16b0cedd0, age = 20, grade = A
ptr = 0x16b0cedd8, age = 30, grade = B
ptr = 0x16b0cede0, age = 40, grade = C
```

アドレスも8バイトずつ増えています。

これは、第7回で学んだポインタ演算とまったく同じ仕組みです。

構造体でも、ポインタは型のサイズ分だけ移動します。

---

### ->演算子

ポインタが移動したあとも、メンバーへアクセスする方法は変わりません。

```c
ptr->age
```

や

```c
ptr->grade
```

と書くだけで、

現在、ptrが指している構造体のメンバーへアクセスできます。

---

つまり、アロー演算子は「現在ポインタが指している構造体」に対してメンバーへアクセスする演算子です。

```text
ptr

↓

people[1]

↓

age
```

---

### 実行結果を確認


```text
Pointer access:
ptr = 0x16b0cedd0, age = 20, grade = A
ptr = 0x16b0cedd8, age = 30, grade = B
ptr = 0x16b0cede0, age = 40, grade = C
```


```text
ptr = 0x16b0cedd0
age = 20

↓

ptr++

↓

ptr = 0x16b0cedd8
age = 30

↓

ptr++

↓

ptr = 0x16b0cede0
age = 40
```

実行結果を見ると、ポインタが移動するたびに、取得できるageとgradeも変わっています。

ポインタが指している構造体が変わると、アロー演算子で取得できる値も自動的に変わることが分かります。

---

# まとめ

今回は、構造体ポインタとアロー演算子について学びました。

```text
今回のポイント

- 構造体配列は連続して配置される
- ptr++で sizeof(Person)分だけ移動する
- ptr->memberで 現在指している構造体へアクセスできる
- -> は (*ptr).member の省略形

