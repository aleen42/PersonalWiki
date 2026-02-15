## A useful collection of Git commands [Back](../git.md)

1. List all authors inside a project:

    ```bash
    git shortlog --summary --numbered --email 
    ```

    ```bash
    git shortlog -sne 
    ```

    To show all branches:

    ```bash
    git shortlog -sne -all 
    ```

2. List logs with a colourful graph:

    ```bash
    git log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%ai) %C(bold blue)<%an>%Creset' --abbrev-commit
    ```

3. Squash all commits into one:

    ```bash
    !f(){ git reset $(git commit-tree HEAD^{tree} -m \"${1:-A new start}\");};f "commmit message" 
    ```

4. Show lines of differences between two commits:

    ```bash
    git diff --shortstat 
    ```
