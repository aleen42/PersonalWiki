## Git Commit Message Convention [Back](../git.md)

An extension based on [**kazupon/git-commit-message-convention**](https://github.com/kazupon/git-commit-message-convention), which is actually an extension edition from angular style. This document mainly aims to give out a convention of git commit messages of mine and help reuse by others. Why is a convention required? Because it should result in a more elegant history, which the future contributors can trace back one day.

All Commit Messages **MUST** be formatted like this:

```
<Type>[(<Scope>)]: <Subject> [#<Issue>] [!<MR/PR>]
[<BLANK LINE>]
[<Message Body>]
```

- **Type**: mainly used to describe what kind of your message is around this commit.

|        Type | Description                                                  |
|------------:|:-------------------------------------------------------------|
|     feature | for new feature implementing commits                         |
|         fix | for bug fix commits                                          |
| improvement | for backwards-compatible enhancement commits                 |
|    breaking | for backwards-incompatible enhancement commits               |
|    refactor | for refactoring commits                                      |
|    docs/doc | for documentation commits                                    |
|    examples | for examples commits                                         |
|        test | for testing commits                                          |
|        lint | for linting commits                                          |
|        typo | for typo fixing                                              |
|  dependency | for dependencies commits like upgrading or eliminating       |
|       build | for packaging or bundling commits                            |
|     release | for publishing commits (tag here in most cases)              |
|         wip | for work in progress commits (deprecated to avoid conflicts) |
|      revert | for reverting commits                                        |
|       chore | for any other commits without specified type                 |


- **Scope**: mainly used to describe which parts you have modified, similar to namespaces. For instance, `login/Confirmbox` can be a scope standing for the `ConfirmBox` component in the login module.
- **Subject**: a laconic subject to describe what your code has done.
    - **DO NOT** capitalize the first letter.
    - **DO NOT** add trailing dot (`.`) at the end.
- **Issue**: identification of issues related to commits, like GitHub Issue ID or JIRA Issue ID.
- **MR/PR**: identification of merge requests, or pull requests, related to commits.
- **Message Body**: a more detailed description after a subject.

In addition, we can use some helpful tools to lint our commit messages before committing or even integrate with CI to handle unconventional commit messages. [**husky**](https://github.com/typicode/husky) is one of my choices for registering git hooks so that we can lint messages before committing. In addition, [**commitlint**](https://github.com/marionebl/commitlint) is one of the best tools for checking messages with the format above.
