## Configuration [Back](./../eslint.md)

After installation of ESLint, you may have to set up a configuration file by typing:

```bash
eslint --init
```

Once running this command, a file named `.eslintrc` will be automatically created in the directory, in which you will see some rules like the following snippet:

```js
{
    "rules": {
        "semi": ["error", "always"],
        "quotes": ["error", "double"]
    }
}
```
