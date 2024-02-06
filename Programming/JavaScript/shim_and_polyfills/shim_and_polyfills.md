## Shim and Polyfills [Back](./../JavaScript.md)

**Polyfills** is one kind of Shim, and shim means a library used to import new APIs into an old environment, which is completed by old methods. Polyfills is a shim in APIs of browsers.

Polyfills is a term first coined by *RemySharp* to describe the copying of missing APIs and API functions, with which you don't have to worry about use new features in an old environment.

#### Case1: HTML5 elements

There is a case that we can't apply special CSS for new HTML5 elements like `<article>`, `<aside>`, `<header>` or, `<time>` in IE Browser. Fortunately, *Sjoerd Visscher* has found a solution with calling `document.createElement()`.

```html
<html>
    <head>
        <title>HTML5 In IE?</title>
        <style>
            article { margin: 0 auto; width: 640px; }
        </style>
        <script>
            document.createElement('article');
        </script>
    </head>
    <body>
        <article>
            <!-- Write something here -->
        </article>
    </body>
</html>
```

However, no one is willing to handle so many new elements by calling this function, while that's the advantage of Polyfills, and it's [**html5shim**](https://github.com/aFarkas/html5shiv) (also called html5shiv) to automatically complete all the new features in IE. We can use it as follow:

```html
<html>
    <head>
        <title>HTML5 In IE?</title>
        <style>
            article { margin: 0 auto; width: 640px; }
        </style>
        <!--[if lt IE 9]>
            <script src="bower_components/html5shiv/dist/html5shiv.js"></script>
        <![endif]-->
    </head>
    <body>
        <article>
            <!-- Write something here -->
        </article>
    </body>
</html>
```

*Notice that: the arround style of script is written according to html5shiv itself, and the script will be loaded when the browser is lower than IE 9.*

#### Case 2: localStorage

`localStorage` API is not supported in the browser which is lower than IE 8. There are plenty of Polyfills to make it supported like **RemySharp's Storage Polyfiller**, **store.js** and **PersistJS**. Both **LawnChair** and **the storage module of AmplifyJS** are the Polyfills of localStorage as well.

Here has the case of using AmplifyJS to solve compatibility problems of localStorage:

```js
/** Set a localStorage variable of name */
amplify.store('name', 'Aleen');

/** Store an object */
const website = {
    name: 'PersonalWiki',
    url: 'https://aleen42.github.io/PersonalWiki/'
};
amplify.store('websiet', website);
```

According to the suggestion, Remy Sharp's Storage Polyfiller is the only one which can simulate HTML5 localStorage API perfectly.

#### Case 3: Geographic Location

Geographic Location is well supported by mobiles because of its GPS sensors, and on PC, it can only use IP address to locate your region.

```js
navigator.geolocation.getCurrentPosition(function (position) {
    const lat = position.coords.latitude;
    const long = position.coords.longitude;
    
    console.log('Current location:', lat, long);
);
```

There is a Polyfills written by *Paul Irish* to solve this problem by using Google Geographic Location APIs.

#### Case 4: History and Navigation

DHTML has provided some features like paging based on AJAX or single page, which has not used History and Navigation of browsers. Using this features, problems is coming when users want to go back last step by clicking "back" button. **Hash** can solve these problems, because changing a hash value of a link will not reload the webiste.

`Onhashchange` Event is an event to handle changement of hash value, which is not supported in old browsers. Therefore, we need Polyfills like *Ben Alman's* jQuery Hashchange. Nevertheless, Alman's Hashchage is based on jQuery, and it's not a Polyfills in definition. Even that, hash still has some problems. For example, when I store a website as a tag, it can only show me a default page when I open it next time.

For that problem, HTML5 has given out a more advanced API called **pushState**. The method `windows.history.pushState` and the event `windows.onpopstate` are both combined with this API to use handle navigation events asynchronously. *Benjamin Lupton* has built a library **history.js** for improving compatibility of pushState.

```js
/** change the uri to /state1 and change it to /#/state1 in older browsers */
History.pushState(null, 'State 1', 'state1');

/** get historystate and write it on the console */
History.Adapter.bind(window, 'statechange', function () {
    /** get the new history state */
    const state = History.getState();
    
    console.log(state.url);
});
```

*Notice that: your server should act like a smart person when handling so many undefined uris rather than only return a 404 or 500 reponse.*

#### More info

[HTML5-Cross-browser-Polyfillw](https://github.com/Modernizr/Modernizr/wiki/HTML5-Cross-browser-Polyfills)
