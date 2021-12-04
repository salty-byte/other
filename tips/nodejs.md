# Nodejs tips

## Audit

```
$ npm audit
$ npm audit fix
```

## Dependencies アップデート

- [npm-check-updates](https://github.com/raineorshine/npm-check-updates)を使う。

```
# for npm
$ npm install -g npm-check-updates
$ ncu
$ ncu -u
$ npm install
```

```
# for npx
$ npx npm-check-updates
$ npx npm-check-updates -u
$ npm install
```
