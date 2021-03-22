# PowerShell tips(HTB/CTF 用)

## File

- 一覧表示

```
dir
dir user\
dir -Force
```

`ls` も可能。

- 中身を見る

```
type target.txt
```

- 検索

```
type target.txt | Select-String "AAA"
```

- 検索: 正規表現

```
type target.txt | Select-String -Pattern "^A"
```

## WinRC

- 接続

```
$uname = "user_name"
$pass = ConvertTo-SecureString "passABC123$" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential ($uname, $pass)
Enter-PSSession -Computer 192.168.x.x -Credential $cred -Authentication Negotiate
```

- 特定のセッションのユーザとして接続

```
Enter-PSSession -Computer 192.168.x.x -Credential $cred -ConfigurationName other_session -Authentication Negotiate
```

参考: https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/enter-pssession?view=powershell-7.1
