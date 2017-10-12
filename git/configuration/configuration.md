## Personal Configuration	[Back](./../git.md)

To record my preferred configuration of Git, I have made it in document.

```
[gui]
        encoding = utf-8
[i18n "commit"]
        encoding = utf-8
[i18n]
        logoutputencoding = utf-8

[alias]
        lg = log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%ai) %C(bold blue)<%an>%Creset' --abbrev-commit
        pick = cherry-pick

[rebase]
        autoSquash=true
        autoStash=true
```
