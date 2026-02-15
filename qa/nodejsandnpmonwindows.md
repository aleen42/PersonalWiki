## How to build up Node.js and npm on Windows [Back](./qa.md)

1. download from the website: [http://nodejs.org/#download](http://nodejs.org/#download), and install for windows.
- push `...\nodejs` to the system path.
- clone `npm` from github using: `git clone https://github.com/npm/npm.git`
- install it with `node cli.js install -gf` in the directory.

If you want to upgrade npm, you can install `npm-windows-upgrade` to upgrade it automatically:

```bash
npm install -g npm-windows-upgrade
npm-windows-upgrade
```

And then, remember not to run the following snippet directly:

```bash
npm install -g npm
```

If you want to upgrade Node.js, you may just have to redownload a new installer from https://nodejs.org/en/download to override it.
