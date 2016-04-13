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

`localStorage` API is not supported in the browser which is lower than IE 8. There are plenty of Polyfills to make it supported like RemySharp's Storage  polyfiller, store.js and PersistJS

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>