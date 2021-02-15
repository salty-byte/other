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
