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
        source: "http://example.com/image.png"
      , title: "My image"
    }
});

/** This will console ![My image](http://example.com/image.png) */
console.log(myImg);
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
