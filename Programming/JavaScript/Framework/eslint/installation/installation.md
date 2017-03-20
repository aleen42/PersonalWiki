## Installation [Back](./../eslint.md)

According to official documents of ESLint, it can be installed through two ways: **globally and locally**.

So when should we install it globally or locally? It depends on the case whether you want it to be part of all projects or a single project.

### Locally

If you want it to be installed in a single project, it's recommended to install locally:

```bash
npm install eslint --save-dev
```

Then set up a configuration file:

```bash
./node_modules/.bin/eslint --init
```

Then check the report of a JavaScript file with running:

```bash
./node_modules/.bin/eslint file.js
```