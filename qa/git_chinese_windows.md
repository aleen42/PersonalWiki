## How to support Chinese for Git in Windows [Back](./qa.md)

Firstly, find out the root path of Git installed in Windows.

Then, change some configuration files in the folder `etc`:

- `/etc/gitconfig`:

    add the following snippet right behind the file
    ```
    [gui]
        encoding = utf-8
    [i18n]
        commitencoding = gbk
    [svn]
        pathnameencoding = gbk
    ```

