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

The names `semi` and `quotes` are the names of [rules](http://eslint.org/docs/rules) in ESLint. The first value is the error level of the rule and can be one of these values:

- **off** or **0**: turn the rule off
- **warn** or **1**: turn the rule on as a warning
- **error** or **2**: turn the rule on as an error

Despite of the property of `rules`, it will also included the property of `extends` like the following snippet:

```js
{
    "extends": "eslint:recommended"
}
```

With this property set by default, all the rules maked with ticks notation (`√`) will be set.
