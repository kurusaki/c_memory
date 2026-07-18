# C言語の壁を越えよう！
## ～メモリの世界から理解するC言語～

#0 MacでC言語の開発環境を作ろう

---

## この動画について

📺 **[動画はこちら](https://youtu.be/sDIPV_R0Msg)**

この動画では、これからシリーズで使用するC言語の開発環境を準備し、
最初のプログラム「Hello, World!」を実行するまでを解説します。

また、

- VS Codeの役割
- clang（コンパイラ）の役割
- コンパイルとは何か
- 実行ファイルとは何か

についても紹介します。

このシリーズでは、すべてMac環境で解説しますが、
C言語そのものの内容はWindowsやLinuxでも共通して学習できます。


---

## この動画で学べること

- C言語の開発に必要な環境
- Xcode Command Line Tools
- clangとは何か
- コンパイルの流れ
- Hello, World! の実行方法

---
## サンプルコード

この動画で使用したサンプルコードです。

- [hello.c](hello.c)

---
## 目次

- このシリーズで使う環境
- Xcode Command Line Tools を確認しよう
- clangとは？
- なぜ gcc ではなく clang を使うの？
- clang が使えることを確認しよう
- 最初のプログラムを書いてみよう
- コンパイルしてみよう
- 実行してみよう
- まとめ

---
## 動画シナリオ

今回は第0回。
まずは、これから使う開発環境を確認して、
最初のC言語のプログラムを動かしてみましょう。

---

### このシリーズで使う環境

このシリーズでは、エディタに VS Code、コンパイラに clang を使用します。

コマンドの実行にはターミナルを使って進めていきます。

Mac のターミナルでも、VS Code のターミナルでも大丈夫です。

今回はできるだけシンプルな構成で進めていきます。

---
### Xcode Command Line Tools を確認しよう

Macでは、
Xcode Command Line Tools をインストールすると、
clang が使えるようになります。

ターミナルで、下記のコマンドを実行して下さい。

```bash
xcode-select --install
```

C言語のコンパイラである clang など、
開発に必要なツールが利用できるようになります。

すでにインストールされている場合は、「すでにインストールされています」というメッセージが表示されます。


実行結果

```text
xcode-select: note: Command line tools are already installed. Use "Software Update" in System Settings or the softwareupdate command line interface to install updates
```

---
### clangとは？

ここで、今回のシリーズで何度も登場する「clang」について説明しておきます。

私たちが書くC言語のコードは、
人間には読めますが、
コンピュータはそのままでは理解できません。

そこで登場するのが clang です。

clang は、人間が書いた C言語のソースコードを、
コンピュータが実行できるプログラムへ変換してくれるソフトです。

このようなソフトを「コンパイラ」と呼びます。

コンパイルの流れは次のようになります。

```mermaid
flowchart LR
    A[人間]
    B[C言語のソースコード]
    C[clang]
    D[実行ファイル]
    E[コンピュータが実行]

    A --> B
    B --> C
    C --> D
    D --> E
```

今後のシリーズでは、
コードを書いたら、
まず clang でコンパイルして、
そのあとプログラムを実行する、
という流れで進めていきます。

---
### なぜ gcc ではなく clang を使うの？

C言語のコンパイラといえば、gcc を思い浮かべる方もいるかもしれません。

もちろん gcc でも C言語を開発できます。

ただ、このシリーズでは clang を使用します。

理由はシンプルです。

Mac に Xcode Command Line Tools をインストールすると、
最初から clang が利用できるからです。

特別な設定や追加のインストールをしなくても、
すぐに C言語の開発を始めることができます。

そのため、このシリーズでは、
VS Code と clang を使って進めていきます。


---
### clang が使えることを確認しよう

まずは、clang が使えることを確認してみます。

下記のコマンドを実行します。

```bash
clang --version
```

このようにバージョン情報が表示されれば、準備完了です。


実行結果

```text
Apple clang version 21.0.0 (clang-2100.0.123.102)
Target: arm64-apple-darwin25.5.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

---
### 最初のプログラムを書いてみよう

それでは、
最初のプログラムを書いてみましょう。
VS Codeで
hello.c
というファイルを作成します。


次のコードを入力します。

```c
#include <stdio.h>

int main(void) 
{
    printf("Hello, World!\n");

    return 0;
}
```

---
### コンパイルしてみよう

それでは、このコードをコンピュータが実行できる形に変換してみましょう。

ターミナルで、下記のコマンドを実行します。

```bash
clang hello.c -o hello
```

これは、hello.c というソースコードから、hello という実行ファイルを作るという意味です。

この処理を「コンパイル」と呼びます。

---
### 実行してみよう

続いて、下記のコマンドを実行します。

```bash
./hello
```

Hello, World! と表示されました。

実行結果

```text
Hello, World!
```

無事に C言語のプログラムを実行することができました。

---
### まとめ

今回は、
これから使う開発環境を確認して、
最初の C言語のプログラムを実行してみました。

#### 今回学んだこと

- VS Codeでコードを書く
- clang がソースコードを実行ファイルへ変換する
- コンパイルとは何か
- プログラムを実行する方法


次回からは、
いよいよメモリの世界に入っていきます。