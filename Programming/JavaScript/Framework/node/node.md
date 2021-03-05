## node.js [Back](./../Framework.md)

<p align="center">
    <img src="./node.png" />
</p>

![node](https://aleen42.github.io/badges/src/node.svg)

### Basic

##### i. Update the version of `node` and `npm`

- check the version

```sh
npm -v
```

- get the `n`

```sh
sudo npm install -g n
```

- get the stable version of node.js

```sh
sudo n stable
```

- update npm

```sh
sudo npm install -g npm@latest
sudo npm install -g npm@lts
```

##### ii. Require models

- install models

```sh
# install it in the local directory
npm install <model_name>
```
or

```sh
# install it in the global environment
sudo npm install -g <model_name>
```

- use the models (eg. **request**)

```js
var request = require('request');
```

##### iii. Run the script

```sh
node script.js
```

### Menu

- [**Create and publish a node.js module**](./npm/npm.md)
- [**Create a static server with node.js**](./static_server/static_server.md)
- [**Use Node to write a command line tool**](./cmd/cmd.md)
- [**Differences between spawn and exec of child_process**](./child_process/child_process.md)