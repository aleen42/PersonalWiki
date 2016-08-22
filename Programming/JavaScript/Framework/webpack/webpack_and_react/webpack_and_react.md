## Webpack + React [Back](./../webpack.md)

For my familiarity, I'll build up with react projects with the following file structure:

> project

>> src

>>> components

>>> *_entry.js

>> build

> *.html

Files of sites like (`*.html`) will be placed in the root of this project or if using Laravel, the place will be other one outside this project. Files emitted by webpack will be in `/build`, and imported by sites. Then, here I would like to use a case for teaching how to use webpack to bundle  files with different dependencies in a React project.

#### 1. Init a npm project

```bash
npm init # (answer the questions)
```

#### 2. Install webpack as a development dependency, and global as well

```bash
npm install webpack --save-dev
```

```bash
sudo npm install webpack -g
```