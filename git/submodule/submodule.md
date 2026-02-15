## Submodule	[Back](./../git.md)

- Submodule is what you can use to add sub project of other git repository to your project.

```bash
git submodule add <git url> [name]
```

- If a project have a submodule, you should clone this project by using the following command:

```bash
git clone --recursive <git url>
```