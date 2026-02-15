## Record updates (檢測更新)	[Back](./../git.md)

### 1. Files' Status

<img src="./file_status.png">

### 2. Check the status of files

```git
$ git status
```
```
On branch master
nothing to commit, working directory clean
```

- 當前分支: master
- 沒有文件需要提交

```
On branch master
Untracked files:
  (use "git add <file>..." to include in what will be committed)

        README

nothing added to commit but untracked files present (use "git add" to track)
```

- README沒有被跟蹤

```
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   benchmarks.rb
```

- benchmarks.rb已進行修改, 但沒進入緩存區

### 3. Add files into staged area

```git
$ git add benchmarks.rb
```

### 4. Ignore some files

```git
$ cat .gitignore
```

### 5. Find the differences of a modified file

```git
$ git diff
```

### 6. Commit the update

- 提交前要確保所有新建或修改過的文件都```git add```過

```git
git commit
```

### 7. Skip the staged area and commit

- 跳過緩存, Git自動把所有已跟蹤過的文件暫存起來一起提交

```git
$ git add -a -m 'added new benchmarks'
```

### 8. Delete a file

```git
$ git rm README
```

### 9. Rename a file

```git
$ git mv README README.txt
```

