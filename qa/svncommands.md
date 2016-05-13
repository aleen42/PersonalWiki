## Some commands of SVN [Back](./qa.md)

#### 1. Locate file `*.js` or `*.css`

```bash
svn ls -R <repo_svn_url>/trunk/ | grep .js

# locate with a whole path
# Linux
svn ls -R <repo_svn_url> | egrep "*.js$|" | xargs -n1 -i echo <repo_svn_url>/trunk/{} | awk "{print $1$2}"
# Mac OS
svn ls -R <repo_svn_url> | egrep "*.js$" | xargs -n1 -i echo <repo_svn_url>/trunk/{} | awk "{print $1$2}"
```

#### 2. Cat file

```bash
svn cat <repo_svn_url>
```

#### 3. Statistic Code Line for GitHub like JavaScript

```bash
svn ls -R <repo_svn_url>/trunk/ | egrep "*.js$|*.jsx$" | xargs -n1 -i echo <repo_svn_url>/trunk/{} | awk "{print $1$2}" | xargs svn cat | grep -v ^$ | wc -l
```