## Pjax + React [Back](./../react.md)

As we all known, Pjax was a jQuery plugin before, and now it has been a well known technology to easily enable fast Ajax navigation on any website (using **pushState** and **XMLHttpRequest**). It exactly allows us to build standard websites with complicated user experience, which make users feel like browsing an app.

Under the hood, it actually uses **Ajax** to load resources from server sides, and re-renders them in the same page, by replacing some elements we want without breaking down the whole structure. After that, Pjax will update the browser's current url using **pushState**. With the process of re-rendering, we can easily implement any animation between sites' switching.

For some reasons, I have written this document to talk about how to use **Pjax** combined with **React**. However, as we mentioned above, **Pjax** was originally a jQuery plugin, but what if I don't want to import the library jQuery in React?

Thanks to [MoOx](https://github.com/MoOx), he has provided [another project](https://github.com/MoOx/pjax) for us to complete it without using jQuery. Before using that standalone JavaScript module, it's recommended to read more about it in its document. If you have done your job, here is the main points when combining with React.

### Installation

Since I have always used **Webpack** to bundle my project, CommonJS is the style which I prefer to use. Before importing the module, we should firstly install it by using npm:

```bash
$ npm install pjax
```

Or using bower:

```bash
$ bower install pjax
```

### Initialization

After completing the installation, we're going to find out which sites should be the main entrance of our web applications. It also means that you should find out your main component which will be mounted at the begining.

Then, initialize the Pjax module in the function `componentDidMount`:

```js
var Pjax = require('pjax');

var MainComponent = React.createClass({
    /** ... */
    componentDidMount: function () {
        /** new the Pjax object */
		new Pjax({
			selectors: ['.container']
		});
    },
    /** ... */
});
```

As we can see in the snippet, the constructor accepts an object, which aims to specifies options of Pjax. In the member `selectors`, you have to initiate it with an array, in order to tell Pjax which elements to switch between sites. In other words, we will swap all elements with the class name `container`, and all elements within them, when loading another sites. Therefore, you're supposed to ensure that any document file of sites should have at least one element with `container` as its 

