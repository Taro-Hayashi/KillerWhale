# Killer Whale ビルドガイド

1. スタートページ（このページ）
2. [ベースユニットの組み立て](左手用/ベースユニット.md)
3. [追加ユニットの組み立て](左手用/追加ユニット.md)
5. [側面ユニットの組み立て](左手用/側面ユニット.md)
6. [天面ユニットの組み立て](左手用/天面ユニット.md)
7. [カスタマイズ](左手用/カスタマイズ.md)

## キット以外に必要なもの
|部品名|数||
|-|-|-|
|[キースイッチ](https://shop.yushakobo.jp/search?sort_by=relevance&q=Cherry+MX&type=product&options%5Bprefix%5D=last&options%5Bunavailable_products%5D=last&filter.v.price.gte=&filter.v.price.lte=&filter.v.m.my_fields.switch_type=Clicky&filter.v.m.my_fields.switch_type=Linear&filter.v.m.my_fields.switch_type=Silent+Linear&filter.v.m.my_fields.switch_type=Silent+Tactile&filter.v.m.my_fields.switch_type=Tactile)|27|Cherry MX互換|
|[キーキャップ](https://shop.yushakobo.jp/collections/keycaps?sort_by=best-selling&filter.v.availability=1&filter.v.m.my_fields.keycaps_profile=ASA+Profile&filter.v.m.my_fields.keycaps_profile=ASA-Low+Profile&filter.v.m.my_fields.keycaps_profile=CXA+Profile&filter.v.m.my_fields.keycaps_profile=Cherry+Profile&filter.v.m.my_fields.keycaps_profile=DCS+Profile&filter.v.m.my_fields.keycaps_profile=DSA+Profile&filter.v.m.my_fields.keycaps_profile=JDA+Profile&filter.v.m.my_fields.keycaps_profile=KAT+Profile&filter.v.m.my_fields.keycaps_profile=MA+Profile&filter.v.m.my_fields.keycaps_profile=MDA+Profile&filter.v.m.my_fields.keycaps_profile=NP+Profile&filter.v.m.my_fields.keycaps_profile=OEM+Profile&filter.v.m.my_fields.keycaps_profile=OSA+Profile&filter.v.m.my_fields.keycaps_profile=PG+Profile&filter.v.m.my_fields.keycaps_profile=SA+Profile&filter.v.m.my_fields.keycaps_profile=SAL+Profile&filter.v.m.my_fields.keycaps_profile=Tai-Hao+Cubic+Profile&filter.v.m.my_fields.keycaps_profile=XDA+Profile&filter.v.m.my_fields.keycaps_profile=特殊&filter.v.price.gte=&filter.v.price.lte=)|27|Cherry MX互換|

|Raspberry Pi Pico|1|W、Type-C版も可|
|USBケーブル|1||

### オプション
|部品名|数||
|-|-|-|
|LED（SK6812MINI-E）|32|発光しますが難易度が上がります|
|コンスルー20ピン|2|Raspberry Pi Picoをつけ外しできるようになります|
|TRSケーブル、TRRSケーブル|1||2台を接続できます|

### 必要な工具
|工具名|
|-|
|はんだごて|
|はんだ|
|ニッパー|
|カッター（デザインナイフ）|
|やすり（棒、紙）|
|+の精密ドライバー|
|ナットをしめるもの（ラジオペンチ、M2スパナ）|

## 準備
### ファームウェアを書き込む
こちらのファイルをダウンロードしてください。  
 - []

Raspberry Pi Picoを、BOOTSELボタン押しながらUSBケーブルでPCと接続すると、RPI-RP2というUSBメモリとして認識されます。  
![](img/IMG_3493.jpeg)   
![](img/rpi.jpg)   
ここにダウンロードしたuf2ファイルを書き込むと、Raspberry Pi Picoをキーボードとして使えるようになります。 

書き込みが終わったら一旦USBケーブルは外します。  

### 左右
このキットは左右を選んで組み立てることができます。左右のビルドガイドの違いは写真だけです。

- [左手用]()
- [右手用]()
