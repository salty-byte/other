# ubuntu tips

## ELF

64-bit Ubuntu で以下のようなプログラムが動かない場合

- ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.32

```
chmod -x program
./program
# => bash: ./program: No such file or directory
```

原因: /lib/ld-linux.so.2 が無い

```
sudo apt update
sudo apt install libc6-i386 -y
```

## SSH

SSHトンネル経由のポートフォワーディング設定(~/.ssh/config)

```
Host humidai
    HostName xxx.xxx.xxx.xxx
    Port 22
    User userXXX
    ForwardAgent yes

Host target
    Hostname 192.168.0.1
    Port 22
    User userYYY
    ProxyCommand ssh -W %h:%p -L 80:localhost:80 humidai
    LocalForward 80 localhost:80
```
