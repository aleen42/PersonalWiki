## Pjax + React [Back](./../react.md)

<p align="center">
    <img src="./logo.png" width="75%" alt="pjax react" title="pjax+react" />
</p>

<p align="center">
    <strong>Pjax</strong>, combined with powerful React
</p>

<br />

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

After completing the installation, we're going to find out which sites should be the main entrance of our web applications. It also means that you should find out your main component which will be mounted at the beginning.

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

Actually, if you have more than one sites to initiate Pjax, this way is not appropriate for you, as you are not able to share the same flag between sites. For this reason, you may have to change another way:

```js
var Pjax = require('pjax');

var MainComponent = React.createClass({
    /** ... */
    handleClick: function (e) {
        /** invoke the link */
        this.refs.login.click();
    },

    componentDidMount: function () {
        /** check whether a property has been delivered into the component */
        if (this.props.isNewPjax) {
			/** new the Pjax object */
			new Pjax({
				selectors: ['.container'],
				cacheBust: false
			});
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

As you can see, we can set a property like `isNewPjax` before, to check whether the site should initiate a new Pjax object. When to initiate is another topic talked later.

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

Loading scripts for each site is the largest problem I have ever met, and the document is too poor to introduce how to solve the problem.

As my react applications are always built with different sites, which should include a JavaScript file as the main entrance, and if I'm just going to simply swap script tags inside the container, they're not be loaded and executed at all, even though the `src` attribute of script elements have already been changed.

With few helps, I have finally find out a way to solve this problem, and that's why I took them into documentations to share with you.

#### Build sites with a similar format

Firstly, we're going to build sites with a similar constructor:

```html
<body>
    <div class="container">
        <script type="text/javascript">
            /** the name of your site */
            var viewName = 'index';

        	if (typeof window.resourcesRender[viewName + 'Render'] !== 'undefined') {
        		window.resourcesRender[viewName + 'Render'].apply();
        	} else {
        		var script = document.createElement('script');

        		/**
        		 * For example, the main entrace file of the site index is at the path:
        		 * build/index.main.js
        		 */
        		script.src = 'build/' + viewName + '.main.js';

        		document.querySelector('.container').appendChild(script);
        	}
    	</script>
    </div>
</body>
```

`window.resourcesRender` is a global array variable for storing render methods for each sites, and if the method you want to call has already been stored in such an array, it means that you have already loaded the script file before, and it's not necessary to load it again, which should result in costing additional overheads.

#### Build the entrance for each site

Also take the index site as an example, we can build the entrance like this:

```js
var React = require('react');
var ReactDOM = require('react-dom');

var Index = require('./components/index.jsx');

/** push the render method into the global array object */
window.resourcesRender.indexRender = function (isNewPjax) {
    isNewPjax = isNewPjax || false;
    ReactDOM.render(
        <Index isNewPjax={isNewPjax}></Index>,
        document.querySelector('.container')
    );
};

window.resourcesRender.indexRender(true);
```

With the property `isNewPjax`, we will only initiate the object Pjax when the JavaScript is loaded first time, and it means that the object will be initiated at the first time rendering your site.

#### Others

If we sometimes have some scripts for "business logic" in a specific site, you can use a similar way to store what we want and use it rather than reload scripts when users redirect to the same site through falling back, going forward, or links directly.

### Memory Leaks

As Pjax would not like to release memory for you when switching DOM structure, you may have to worry about the problem of memory leaks, especially you have initiate some events within the contents which will be replaced. With this reason, we may have to focus on how to unbind this events.

Firstly, we can release memory in the event handler `pjax:send`, which is called after any link is triggered, and before replacing contents. Then, setup a global variable named `releaseFunctions`, which is exactly an array to store functions that used to release memory:

```js
window.releaseFunctions = [];

function handleSend(e) {
    /** check whether to release */
    var releaseFuncs = window.releaseFunctions;
    var releaseFunctionsLen = releaseFuncs.length;

    for (var i = 0; i < releaseFunctionsLen; i++) {
        var fn = releaseFuncs[i];

        if (Object.prototype.toString.call(fn).toLowerCase() === '[object function]') {
            /** check whether it's a real function */
            fn.call();
        }
    }

    /** reset the array */
    releaseFuncs = [];

    /** Ohter operations ... */
}

/** listen to sending requests */
document.addEventListener('pjax:send', handleSend, false);
```

With that array, we can easily handle releasing by pushing a function into the array.

```js
var React = require('react');
var ReactDOM = require('react-dom');

var Index = require('./components/index.jsx');

/** push the render method into the global array object */
window.resourcesRender.indexRender = function (isNewPjax) {
    isNewPjax = isNewPjax || false;
    var container = document.querySelector('.container');

    ReactDOM.render(
        <Index isNewPjax={isNewPjax}></Index>,
        container
    );

    /** setup release functions after calling render */
    window.releaseFunctions.push(function () {
        ReactDOM.unmountComponentAtNode(container);
    });
};

window.resourcesRender.indexRender(true);
```

As we can see, after calling the method `ReactDOM.render()`, we can release memory of components by unmounting it with the method `ReactDOM.unmountComponentAtNode()`. With this method, components rendered in the container before will be unmounted, and at the same time, all events, which are bound to elements in components, are released at the same time. However, events bound to global object like `window`, `document`, etc. won't be released at all, so we should avoid using this way to add event listeners like the following case:

```js
export class MyComponent extends React.Component {
    constructor(props) {
        super(props);

        this.handleResize = this.handleResize.bind(this);
    }

    handleResize(e) {
        /** operation ... */
    }

    componentDidMount() {
        window.addEventListener('resize', handleResize, false);
    }

    render() {
        /** render part */
    }
}
```

If you do need to use this way, you should remember to release these events when components are going to be unmounted:

```js
export class MyComponent extends React.Component {
    /** ... */

    componentDidMount() {
        window.addEventListener('resize', handleResize, false);
    }

    componentWillUnmount() {
        window.removeEventListener('resize', handleResize);
    }

    /** ... */
}
```

With the lifecycle method `componentWillUnmount()` of components, we can still release these events as well.

### Summary

This document has mainly talked about how to combine Pjax with React applications. Since there have been some terrible problems we may meet, we need to consider about a flexible way to work around them. As long as making good use of the Pjax module, animations are just another magic thing to implement between sites' switching.

The document has not covered all problems in using Pjax with React, so if you have any problems, it's welcome to open an issue directly in [the project](https://github.com/aleen42/PersonalWiki) of this book to make a discussion. Certainly, you can directly contact me with the email: **aleen42@vip.qq.com**.
