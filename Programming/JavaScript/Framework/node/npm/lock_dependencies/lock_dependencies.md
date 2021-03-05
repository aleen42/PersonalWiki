## Lock all dependencies? [Back](../npm.md)

As projects become larger and larger, we will always import so many dependencies, especially when what we need actually need more other sub-dependencies of `npm` modules. As a library, much JavaScript library won't lock their dependencies with specifying version, for more upper choice. It is mainly based their trust on other libraries. However, as a private project, it is sometimes **NOT** a truth for trusting others, as some little break changes of dependencies will suddenly break up the building process of our projects.

Therefore, how can I lock all versions of the dependencies tree? `npm` has provided us `package-lock.json` and `npm-shrinkwrap.json`. In most cases, they are both the same thing, except that most important thing where `npm-shrinkwrap.json` will be transferred from your project to others when someone use your project as a library.

Since `npm@5.x`, we can construct `package-lock.json` by `npm i` directly, and if we want to construct `npm-shrinkwrap.json`, we can just execute the command `npm shrinkwrap`.

In addition, `npm ci` is a recommended command for installing dependencies during building as it can guarantee that `node_modules` should be cleared before installing.

##### **References**

- https://stackoverflow.com/a/46132512
- https://docs.npmjs.com/cli/ci
