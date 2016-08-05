## How to convert JSON to Markdown [Back](./qa.md)

<img src="./json2md.png">

**json2md** is a tool built by [Ionică Bizău](https://github.com/IonicaBizau) for converting json to markdown without really writing markdown any more when building node module for npm, because npm modules should have a file named `package.json`.

#### Installation

```bash
npm i jso2md
```

#### Usage

```js
const json2md = require('json2md');
const myImg = json2md({
    img: {
        source: "http://example.com/image.png",
        title: "My image"
    }
});

/** This will console ![My image](http://example.com/image.png) */
console.log(myImg);
```

```js
const json2md = require('json2md');
const docs = json2md([
    {
        h1: "JSON To Markdown"
    },
    {
        blockquote: "A JSON to Markdown converter."
    },
    {
        img: [
            {
                title: "Some image",
                source: "https://example.com/some-image.png"
            },
            {
                title: "Another image",
                source: "https://example.com/some-image1.png"
            },
            {
                title: "Yet another image",
                source: "https://example.com/some-image2.png"
            },
        ]
    },
    {
        h2: "Features"
    },
    {
        ul: [
            "Easy to use",
            "You can programatically generate Markdown content",
            "..."
        ]
    },
    {
        h2: "How to contribute"
    },
    {
        ol: [
            "Fork the project",
            "Create your branch",
            "Raise a pull request"
        ]
    }
]);

/**
 * docs will be:
 *
 * # JSON To Markdown
 * > A JSON to Markdown converter.

 * ![Some image](https://example.com/some-image.png)

 * ![Another image](https://example.com/some-image1.png)

 * ![Yet another image](https://example.com/some-image2.png)

 * ## Features

 * - Easy to use
 * - You can programatically generate Markdown content
 * - ...

 * ## How to contribute

 * 1. Fork the project
 * 2. Create your branch
 * 3. Raise a pull request
 */
```
