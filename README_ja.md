# GlassPlotter

![MDI](image/Screenshot_MDI.png)

[English README](README.md)

## 概要
GlassPlotterはガラスマップを表示するためのデスクトップアプリケーションです。アッベ特性図、分散式、透過率プロットに対応しています。光学設計者が誰でも使用できるよう開発されています。

## 特徴
- MDIインターフェースを採用し、柔軟な表示を実現します
- 美しいグラフィックを備え、マウスで直感的に操作できます
- 各プロットは複数のガラス（またはカタログ）のデータをオーバーレイして表示することができ、用意に比較検討できます

## 使い方
1. Windows/Mac用の実行ファイルは[Release](https://github.com/heterophyllus/glassplotter/releases)からダウンロードできます
2. AGFファイル読み込み
  本アプリ起動後、File->load AGFから必要なZemax AGFファイルを読み込みます（複数選択可）
3. Toolsメニューの各項目をクリックするとサブウインドウが表示されます
4. あわせて[こちらのGIF](image/demo.gif)をご確認ください

## 必要ファイル
本アプリはZemax AGFファイルから各ガラスデータを抽出しています。AGFはガラスメーカーのサイトからダウンロードできます。もしZemaxがインストールされていれば適当なフォルダに同梱されています。

## 開発
本アプリは下記のライブラリを用いて開発されています。
- [Qt and QtCreator](https://www.qt.io) 
- [QCustomPlot](https://www.qcustomplot.com) 
- [spline](https://github.com/ttk592/spline) 
  
## ライセンス
本プロジェクトはGPLライセンスです。詳しくは[ライセンスファイル](LICENSE.md)をご確認ください。

## プロジェクトへの参加
プロジェクトへの参加およびアプリのフィードバックを受け付けています。

