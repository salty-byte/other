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
