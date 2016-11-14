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

As we can see in the snippet, the constructor accepts an object, which aims to specifies options of Pjax. In the member `selectors`, you have to initiate it with an array, in order to tell Pjax which elements to switch between sites. In other words, we will swap all elements with the class name `container`, and all elements within them, when loading another sites. Therefore, you're supposed to ensure that any document file of sites should include at least one element with `container` as its class name, or it will have thrown an error.


It may still have some problems in using the code above, in the case when you try to re-render your main component. As the method `componentDidMount` being triggered several times, the application will create more than one Pjax object, resulting in re-executing previous code each time you load the page. Due to the terrible reason, you have to control it relying on a new flag named `window._isPjaxSet`. Certainly, you can name your flag with other names.

```js
var Pjax = require('pjax');

var MainComponent = React.createClass({
    /** ... */
    componentDidMount: function () {
        /** check whether Pjax has been already initiated */
        if (!window._isPjaxSet) {
			/** new the Pjax object */
			new Pjax({
				selectors: ['.container'],
				cacheBust: false
			});

			window._isPjaxSet = true;
		}
    },
    /** ... */
});
```

### Trigger links

The integrated module will only listen to every click on links, so if we want to load other sites within the bound `click` events on an element, we may have to find another way.

For me, I have tried the way of creating `a` tags and triggering it as followed:

```js
var link = document.createElementById('a');
link.attr = 'direct.html';
link.click();
```

However, it does not work, because Pjax module will only listen to link elements rendered on the DOM tree. Therefore, I will render a hidden link element firstly, and trigger it with click listener:

```js
var Pjax = require('pjax');

var MainComponent = React.createClass({
    /** ... */
    handleClick: function (e) {
        /** invoke the link */
        this.refs.login.click();
    },
    
    componentDidMount: function () {
        /** check whether Pjax has been already initiated */
        if (!window._isPjaxSet) {
			/** new the Pjax object */
			new Pjax({
				selectors: ['.container'],
				cacheBust: false
			});

			window._isPjaxSet = true;
		}
    },
    
    render: function() {
        return (<div>
            <a href="login" ref="login" className="link__hidden"></a>
            <div className="button__login" onClick={this.handleClick}></div>
        </div>);
    }
    /** ... */
});
```

### Loading Experience

Sometimes, for loading large sites, we may be supposed to add an loading icon to tell users that it still works. Conveniently, we can implement this by simply attaching event handlers to listen to two events: `pjax:send` and `pjax:complete` respectively.

```js
function handleSend(e) {
    /**
     * before using fadeIn, you have to implement it
     * as the prototype method of HTMLElement
     */
    document.querySeletor('loading').fadeIn();
}

function handleComplete(e) {
    /**
     * before using fadeOut, you have to implement it
     * as the prototype method of HTMLElement
     */
    document.querySeletor('loading').fadeOut();
}

/** listen to sending requests */
document.addEventListener('pjax:send', handleSend, false);

/** listen to ending requests */
document.addEventListener('pjax:complete', handleComplete, false);
```

### Loading Scripts

Loading scripts for each site is the largest problem I have ever met, and the document is too poor to introduce how to solve the problem. As my react applications are always built with different sites, which should include a main entrance JavaScript file, if I'm just going to simply swap script tags inside the container, they're not be loaded and executed at all, even thouth the `src` attribute of script elements have been changed.
