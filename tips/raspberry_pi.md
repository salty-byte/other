# raspberry pi tips

## ドライバ

### PC 上でクロスコンパイル

**作業環境**

- OS: Ubuntu 18.04 LTS on Virtual box (on Windows 10)
- 導入先: Raspberry Pi 4 (32-bit)

**カーネルビルド** (on Ubuntu)

公式手順: https://www.raspberrypi.org/documentation/linux/kernel/building.md

- 依存パッケージインストール

```
sudo apt install git bc bison flex libssl-dev make libc6-dev libncurses5-dev
```

- ツールチェインインストール

32-bit カーネル用のツールチェインをインストールする。

```
sudo apt install crossbuild-essential-armhf
```

- カーネルビルド

作業場所: ~/rasp-dev

```
cd
mkdir rasp-dev
cd rasp-dev
```

ソースコードをクローンする。

```
git clone --depth=1 https://github.com/raspberrypi/linux
```

Raspberry Pi 4 (32-bit) 用に設定ファイルを作成する。

```
cd linux
KERNEL=kernel7l
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2711_defconfig
```

カーネルをビルドする。

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs
```

**ドライバビルド** (on Ubuntu)

- 導入ドライバ: RTL88x2BU  
  https://github.com/RinCat/RTL88x2BU-Linux-Driver

```
git clone https://github.com/RinCat/RTL88x2BU-Linux-Driver
```

- ビルド

```
cd RTL88x2BU-Linux-Driver
make clean
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- KSRC=~/rasp-dev/linux
```

ビルドが完了していれば、`88x2bu.ko`ファイルが作成される。

```
file 88x2bu.ko
modinfo 88x2bu.ko
```

**ドライバインストール** (on Raspberry Pi 4)

SD カードのマウントや SCP コマンドなどで `88x2bu.ko` ファイルを Raspberry Pi 側に転送しておく。

- ロード

```
insmod 88x2bu.ko
```

- アンロード

```
rmmod 88x2bu.ko
```

**ドライバ自動起動** (on Raspberry Pi 4)

- ビルドしたドライバの配置

```
cp 88x2bu.ko /lib/modules/$(uname -r)/kernel/drivers/.
```

- 依存関係の更新

現在のカーネルの依存関係を更新する。

```
depmod
```

`/lib/modules` 内の別バージョンのカーネルの依存関係を更新する。  
※Raspberry Pi 4 で Raspberry Pi 3, Zero 等の他のバージョンに対して変更を加えたい場合に利用する。

```
depmod 5.10.11-v7+
```

- 自動起動の設定

```
bash -c 'echo "88x2bu" >> /etc/modules-load.d/modules.conf'
```

## 参考文献

- https://www.raspberrypi.org/documentation/linux/kernel/building.md
- https://nw-electric.way-nifty.com/blog/2020/02/post-d872db.html
- https://qiita.com/iwatake2222/items/b9dd02724e83e36dabc3
