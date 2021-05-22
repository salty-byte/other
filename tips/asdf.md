# asdf tips

## コマンド

**基本**

commands: https://asdf-vm.com/#/core-commands

```
asdf plugin list all
asdf plugin add <:name>
asdf list all <:name>
asdf install <:name> <:version>
asdf global <:name> <:version>
asdf current
```

**Node.js**

```
asdf plugin add nodejs
bash -c '${ASDF_DATA_DIR:=$HOME/.asdf}/plugins/nodejs/bin/import-release-team-keyring'
asdf install nodejs 14.15.4
asdf global nodejs 14.15.4
```

**Java+Gradle**

```
asdf plugin add java
asdf install java openjdk-15.0.1
asdf global java openjdk-15.0.1

asdf plugin add gradle
asdf install gradle 6.8
asdf global gradle 6.8
```

**Python**

```
asdf plugin add python
asdf install python 3.8.7
asdf global python 3.8.7
```

**PHP**

Install dependencies:

```
apt install -y autoconf bison re2c libcurl4-openssl-dev libgd-dev libonig-dev libpq-dev libzip-dev
```

Install PHP:

```
asdf plugin add php
asdf install php 8.0.2
asdf global php 8.0.2
```

## インストール

**システムワイドインストール**

依存ツールのインストール

```
sudo apt install curl git
```

GitHub から asdf (v0.8.1) のクローン

```
sudo git clone https://github.com/asdf-vm/asdf.git /usr/local/asdf --branch v0.8.1
```

管理グループの設定

```
sudo groupadd asdf
sudo chgrp -R asdf /usr/local/asdf
sudo chmod -R g+rwXs /usr/local/asdf
sudo gpasswd -a foo asdf
```

環境変数の設定

```
sudo vi /etc/profile.d/asdf.sh
```

`/etc/profile.d/asdf.sh`:

```
export ASDF_DIR=/usr/local/asdf
export ASDF_DATA_DIR=$ASDF_DIR

ASDF_BIN="${ASDF_DIR}/bin"
ASDF_USER_SHIMS="${ASDF_DATA_DIR}/shims"
PATH="${ASDF_BIN}:${ASDF_USER_SHIMS}:${PATH}"

. "${ASDF_DIR}/lib/asdf.sh"
. "${ASDF_DIR}/completions/asdf.bash"
```

```
source /etc/profile.d/asdf.sh
```

確認

```
asdf --version
```
