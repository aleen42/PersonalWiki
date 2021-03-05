## What's the difference between tilde(`~`) and caret(`^`) in package.json? [Back](./qa.md)

Sometimes, we will construct our `package.json` to set up dependencies which will be used in projects, but when specifying versions, we should always see two notation: **tilde (`~`)**, and **caret (`^`)**. So, what is the difference between them?

- tilde (`~`):

    this notation matches the most recent minor version. For example, `~1.2.3` matches all `1.2.x` versions, but not `1.3.0`.

- caret (`^`):

    this notation matches the most recent major version. For instance, `^1.2.3` matches all `1.x.x` versions, but not `2.0.0`.
