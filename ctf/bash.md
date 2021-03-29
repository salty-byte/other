# bash tips(HTB/CTF 用)

## locate

ファイル名検索

```
# 通常
locate .config

# 大文字小文字区別なし
locate -i .config
```

## BASE64

Encode

```
echo test123 | base64
```

Decode

```
echo dGVzdDEyMwo= | base64 -d
```

## adb

ab ファイル展開

```
(printf "\x1f\x8b\x08\x00\x00\x00\x00\x00"; tail -c +25 backup.ab) | tar xfvz -
```

参考: https://stackoverflow.com/questions/18533567/how-to-extract-or-unpack-an-ab-file-android-backup-file
