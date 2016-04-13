## Shim and Polyfills [Back](./../JavaScript.md)

**Polyfills** is one kind of Shim, and shim means a library used to import new APIs into an old environment, which is completed by old methods. Polyfills is a shim in APIs of browsers.

Polyfills is a term first coined by *RemySharp* to describe the copying of missing APIs and API functions, with which you don't have to worry about use new features in an old environment.

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

However, no one is willing to handle so many new elements by calling this function, while that's the advantage of Polyfills, and it's **html5shim** (also called html5shiv) to automatically complete all the new features in IE.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>