# C言語の壁を越えよう！
## ～メモリの世界から理解するC言語～

このリポジトリは、YouTubeチャンネル **CodeBoost Labo** の

**「C言語の壁を越えよう！ ～メモリの世界から理解するC言語～」**

シリーズで使用しているサンプルコードを公開しています。

動画を見ながら実際にコードを動かし、
メモリの動きを確認しながら学習できる内容になっています。

---

## YouTube

📺 CodeBoost Labo

https://www.youtube.com/@CodeBoostLabo

---

## サンプルコード

| No | 動画 | サンプルコード |
|----|------|----------------|
| #0 | MacでC言語の開発環境を作ろう | `samples/00_HelloWorld/` |
| #1 | メモリの中はどうなっている？ メモリダンプ関数を作ろう | `samples/01_memory_dump/` |
| #2 | コンピュータのメモリって何？ | `samples/02_memory/` |
| #3 | 変数はメモリにどう保存される？<br>char・short・int・longをダンプしてみよう | `samples/03_endian/` |
| #4 | メモリの順番が逆！？ エンディアンとは何か | `samples/03_endian/` |
| #5 | 配列はメモリ上でどう並ぶ？ | `samples/05_array_memory.c` |

※ #5以降は、サンプルコードを `samples` フォルダ直下に追加していく予定です。

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