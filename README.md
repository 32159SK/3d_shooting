# 3d_Shooting
3Dゲーム用サンプル

# 内容
* サンプルプロジェクトシューティング
* クレジット.txt
* README.md

# 制作環境
* 開発言語
  * C++
* ライブラリ
  * aqua(学校配布の独自ライブラリ)
* OS
  * Windows 10
* IDE
  * Visual Studio 2019
* 制作期間
  * 4年次前期制作
  * 5ヶ月
* 制作人数
  * 1人(個人製作)
    
# 作品紹介
* C++を用いて制作した3Dゲーム
* 初めてC++で3Dゲームを制作するにあたって、複雑なモデルやモーションを扱うのは困難と思い、簡素なモデルを使用しても違和感のない見下ろし型のシューティングゲームが良いと考えて制作した作品。
* キーボードで移動、マウスで射撃と弾種切り替え、さらに向きを変えられる簡単な操作となっています。また、UIからは基本的に文字を出さないように徹底し、画面の情報量を減らしました。この為、直感的に操作できるシューティングゲームに仕上げることが出来ました。
  
# アピールポイント
 * 学校配布ライブラリに処理追加
 * レイキャスト処理
 * 行列の活用
 * オールレンジ攻撃
 * チュートリアル

## 学校配布ライブラリに処理追加
* 学校配布のライブラリの「aqua」内に三次元空間の処理を行えるクラスがなかった為以下を追加
  * [三次元ベクトルクラス](サンプルプロジェクトシューティング/aqua/src/mathematics/vector/vector3)
  * [行列計算クラス](サンプルプロジェクトシューティング/aqua/src/mathematics/matrix)
  * [カメラクラス](サンプルプロジェクトシューティング/aqua/src/graphics/camera)
  * 
