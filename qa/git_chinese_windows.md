## How to support Chinese for Git in Windows [Back](./qa.md)

Firstly, find out the root path of Git installed in Windows.

Run some commands on the client:

```bash
$ git config --global core.quotepath false # Show encoding status
$ git config --global gui.encoding utf-8 # GUI encoding
$ git config --global i18n.commit.encoding utf-8 # Commit encoding
$ git config --global i18n.logoutputencoding utf-8 # Log encoding
$ export LESSCHARSET=utf-8 # git log will use `less` to paginate information, which should be encoded in UTF-8
```

Then, change some configuration files in the folder `etc`, and add some lines right behind files as the following guide:

- `/etc/gitconfig`:

    ```
    [gui]
        encoding = utf-8
    [i18n]
        commitencoding = utf-8
    [svn]
        pathnameencoding = utf-8
    ```
- `/etc/git-completion.bash`:
    
    ```
    alias ls="ls --show-control-chars --color"
    ```
