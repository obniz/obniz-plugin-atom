# obniz Plugin ATOM Matrix + ATOM Lite

このプラグインは[ATOM Matrix](https://www.switch-science.com/catalog/6260/)や[ATOM Lite](https://www.switch-science.com/catalog/6262/)をobnizとして簡単に扱えるようにするものです。

## ビルドについて

obniz Plugin をあらかじめインストールしておいてください。

このプラグインをビルドするためには、M5AtomのライブラリとFastLEDのライブラリが必要です。

こちらで動作確認を行ったライブラリと同様のものをlibraryフォルダに同封されています。
Arduino IDEの「スケッチ」→「ライブラリーをインクルード」→「ZIP形式のライブラリをインストール」から
library内のZIPファイルをそれぞれインストールさせてください。


## LEDの状態

<figure class="wp-block-table"><table><thead><tr><th>LEDの状態 色(点灯・点滅)</th><th>動作状態</th><th>するべきこと</th></tr></thead><tbody><tr><td>青(点灯)</td><td>obnizクラウドと接続済み</td><td>–</td></tr><tr><td>青(点滅)</td><td>Wi-Fi接続済み。obnizクラウドと接続中</td><td>この状態が続く場合、まずはネットワーク設定の見直しが必要です。<br>・Proxyの設定を忘れていないか<br>・何らかのアクセス制限がかかっていないか<br>またはクラウドで以下の確認が必要です。<br>・ライセンスが切れていないか<br>・ライセンスを無効化していないか</td></tr><tr><td>緑(点灯)</td><td>起動後すぐの状態です</td><td>Wi-Fiの情報がない場合は、この状態のままとなります。<br>Wi-Fi設定を行ってください。<br>また、この状態でボタンを数秒押すことでWi-Fi設定モードになります。</td></tr><tr><td>緑(点滅)</td><td>Wi-Fiに接続中</td><td>接続の場合接続の成功した場合は青（点滅または点灯）となり、失敗すると赤(点灯)となります。</td></tr><tr><td>赤(点滅)</td><td>Wi-Fi設定モード<br>または<br>obnizOS更新中</td><td>Wi-Fi設定を行ってください。<br>obnizOS更新中の場合は、完了後に再起動し緑色に戻ります。</td></tr><tr><td>赤(点灯)</td><td>Wi-Fiの接続エラー</td><td>Wi-Fiへの接続設定が間違っている場合があります。<br>・SSIDとパスワードが正しいか<br>ご確認ください。<br>場合によっては設定をリセットして再設定してください。<br>この状態は一定時間後に解消され再起動されることで緑色に戻ります</td></tr><tr><td>紫(点滅)</td><td>機器設定モード</td><td>デバイスに関する情報<br>・obnizOSのバージョン<br>・Macアドレス<br>を確認できます。<br>また、保存されているWi-Fiの全消去を行うことができます。</td></tr><tr><td>消灯</td><td>電源が入っていない</td><td>電源をご確認ください。<br>確認のために一度抜いて違う機器などを同じコンセントに接続し、再度obniz BLE差し込むことをおすすめいたします。</td></tr></tbody></table></figure>

## Button について

表のボタンを押しながら起動をさせると無線LANの設定を削除やMACアドレスを確認できる「機器設定モード」になります。

このモードではLEDが紫に点滅し、Webページで上記の情報を確認できます。

