## Use Node to write a command line tool [Back](./../node.md)

#### First step is to add bin attributes in package.json

In the following case, this comand line is named `cls`

```json
{
    "bin": {
        "cls": "lib/start.js"
    }
}
```

#### Then create a script `start.js` for this

```js
#! /usr/bin/env/node

console.log('cls command');
```

#### Run `npm link` to install script on the OS

```bash
sudo npm link
```

#### Uninstall

```bash
sudo npm rm --global cls
```