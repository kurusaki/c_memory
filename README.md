# C言語の壁を越えよう！
## ～メモリの世界から理解するC言語～

このリポジトリは、YouTubeチャンネル **CodeBoost Labo** の

**「C言語の壁を越えよう！ ～メモリの世界から理解するC言語～」**

シリーズで使用しているサンプルコードを公開しています。

動画を見ながら実際にコードを動かし、
メモリの動きを確認しながら学習できる内容になっています。

---

## YouTube


📺 [CodeBoost Labo](https://www.youtube.com/@CodeBoostLabo)


**[「C言語の壁を越えよう！ ～メモリの世界から理解するC言語～」](https://www.youtube.com/watch?v=vXqfDO7bKtU&list=PLSStSwK3lbKXaxudKh_MMLw3cBzE1nJuf)**


---

## 目次

| No | テーマ | サンプルコード |
|----|------|----------------|
| #0 | MacでC言語の開発環境を作ろう | [00_HelloWorld](samples/00_HelloWorld/) |
| #1 | メモリの中はどうなっている？ メモリダンプ関数を作ろう | [01_memory_dump](samples/01_memory_dump/) |
| #2 | コンピュータのメモリって何？ | [02_memory](samples/02_memory/) |
| #3 | 変数はメモリにどう保存される？<br>char・short・int・longをダンプしてみよう | [03_endian](samples/03_endian/) |
| #4 | メモリの順番が逆！？ エンディアンとは何か | [04_endian](samples/04_endian/) |
| #5 | 配列はメモリ上でどう並ぶ？ | [05_array_memory](samples/05_array_memory) |
| #6 | C言語最大の壁「ポインタ」まずは正体を知ろう| [06_pointer_basic](samples/06_pointer_basic) |
| #7 | ポインタ演算とは？なぜ「+1」で4バイト進むのか| [07_pointer_arithmetic](samples/07_pointer_arithmetic) |
| #8 | 配列とポインタは同じ？実は「似ているけど違う」| [08_array_pointer](samples/08_array_pointer) |

---

## 共通ファイル

複数のサンプルで使用する共通ファイルです。

| ファイル | 説明 |
|----------|------|
| `samples/mdump.c` | メモリダンプ関数 |
| `samples/mdump.h` | `mdump` 関数のヘッダファイル |

---

## コンパイル方法

例えば、

`05_array_memory.c` をコンパイルする場合は、

```bash
clang samples/05_array_memory.c samples/mdump.c -o 05_array_memory
```

実行するには、

```bash
./05_array_memory
```

---

## 動作環境

このシリーズでは、以下の環境で動作を確認しています。

- macOS
- clang
- VS Code

---

## ライセンス

このリポジトリのサンプルコードは、
学習目的で自由にご利用いただけます。

動画や記事などで紹介していただける場合は、
YouTubeチャンネル **CodeBoost Labo** を紹介していただけると嬉しいです。

---

## CodeBoost Labo

CodeBoost Laboでは、

- C言語
- Ruby
- MySQL
- Docker
- AI駆動開発

など、

プログラミングやIT技術を楽しく学べるコンテンツを公開しています。

チャンネル登録もよろしくお願いします！