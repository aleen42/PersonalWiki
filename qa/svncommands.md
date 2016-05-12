## Some commands of SVN [Back](./qa.md)

#### 1. Locate file `*.js`

```bash
svn ls -R <repo_svn_url>/trunk/ | grep .js

# locate with a whole path
svn ls -R https://github.com/aleen42/cookie.js/trunk/ |grep .js | xargs -n1 -i echo https://github.com/aleen42/cookie.js/trunk/{} | awk "{print $1$2}"
```

#### 2. Cat file

```bash
svn cat <repo_svn_url>
```