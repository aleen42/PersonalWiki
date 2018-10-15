## Try to shrink sizes of large Git repository [Back](../git.md)

Wow, recently I have found that the size of this project has become so large, which is upper than 300 Mb. That's terrible as it means that a lot of time has been cost when cloning, especially when I need to build this as a site with CI.

After some checking, I found that `.git/objects/pack` was so large, which was a file used for recording any commit objects in the repository. Why so large? I have checked the 10 biggest commits I have committed before by running the following command:

```bash
git verify-pack -v .git/objects/pack/pack-xxx.idx | sort -k 3 -n | tail -10
```

And see what files are corresponding to this commit, by pasting SHA hash:

```bash
git rev-list --objects --all | grep xxx
```

Finally find that I have committed some large files and delete after, which should be recorded as a large object here. It is very dirty but Git has to record so that it can know the history. However, we do not really need those objects. How to shrink such sizes?

In a common way, we will use `git filter-branch` to remove cache and garbage collect them by Git:

```bash
git filter-branch --index-filter 'git rm --cached --ignore-unmatch *.mov' -- --all
rm -Rf .git/refs/original
rm -Rf .git/logs/
git gc --aggressive --prune=now
```

However, it is **SLOW**. Fortunately, [**bfg-repo-cleaner**](https://rtyley.github.io/bfg-repo-cleaner/) has worked great for this situation, which specify claim that it is **10~740x** faster than using `git filter-branch`.
