## Configurations [Back](./../TypeScript.md)

TypeScript uses a file called `tsconfig.json` for managing projects' options, where you can specify how to compile Typescript into JavaScript, like which files you want to include or exclude, or whether target files belongs to ES6 syntax, etc. For example, the following configuration file has specified a few things:

```json
{
    "compilerOptions": {
        "outDir": "./build",
        "allowJs": true,
        "target": "es5"
    },
    "include": [
        "./src/**/*"
    ]
}
```

- using `include` to specify reading in any "understandable" files in the `src` folder.
- using `allowJs` option to mark JavaScript files as "understandable".
- using `outDir` to specify where to output files.
- using `target` to specify compiler to translate files down to an older version like ECMAScript 5.

Actually, with setting configurations for compilers to know about your project, you can also earn more early benefits like catching certain bugs with some options, like linting.

- `noImplicitReturns`: which prevents you from forgetting to return at the end of a function.
- `noFallthroughCasesInSwitch`: which is helpful if you never want to forget a break statement between `cases` in a `switch` block.

For more options to check wha we can do, please visit official documents [**here**](https://www.typescriptlang.org/docs/handbook/compiler-options.html).
