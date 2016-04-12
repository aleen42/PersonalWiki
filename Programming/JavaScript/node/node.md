## NodeJs [Back](./../JavaScript.md)

### Basic

##### **i.** Update the version of `Node`

- check the version

```sh
npm -v
```

- get the `n`

```sh
sudo npm install -g n
```

- get the stable version

```sh
sudo n stable
```

##### **ii.** Require models

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

##### **iii.** Run the script

```sh
node script.js
```

### Menu

- [**Create and publish a node.js module**](./npm.md)

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>