## Patch [Back](./../git.md)

Patches formatted under Git has provided us with a way to apply commits from one repository to another, even if their structures are different.

The usage is quite simple:

1. To generate patch files first:

    ```bash
    git format-patch -1 <commit_sha>
    ```

    If you want to create patches of several commits, you may need to change the parameter:

    ```bash
    git format-patch -n <commit_sha> 
    ```

    Then, Git will generate some `*.patch` files under the current workspace

2. Apply generated patches:

    ```bash
    git apply *.patch --directory='<relative_path>'  
    ```
