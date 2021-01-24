# Tips

## asdf

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
