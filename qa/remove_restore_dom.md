## Remove DOM elements and restore again?  [Back](./qa.md)

Is it possible to remove some specific DOM elements and restore again later without any side effects? Perhaps it is possible when using `jQuery.detach()`. Recently, I have tried to do so with implementing screen lock in sites with a more safe way.

The most important thing during removing DOM elements and restore them later is to keep their data, as well as events registered on them. Besides, scripts elements should not be run again during restoring. At first, I found that [`jQuery.clone()`](https://api.jquery.com/clone/) had implemented such a case by passing `true` to the parameter `withDataAndEvents`. Nevertheless, some modules stored old DOM elements inside their states, which meant that we could not using the way of cloning, resulting in lost of old DOM elements.

The problem of losing references has been worked around by `jQuery.detach()`.

```js
const $copy = $element.children().detach();

// restore later
$element.append($copy);
```

As we can see in the snippet above, we can easily remove some elements by using the method, and restore the copy without worrying about losing any data or events, even including the dependencies whenever we want except one case, where elements contains `iframe` observed with [`iframe-resizer`](https://github.com/davidjbradshaw/iframe-resizer). According to [davidjbradshaw/iframe-resizer#651](https://github.com/davidjbradshaw/iframe-resizer/pull/651), IframeResizer has observed removing of iframes in order to avoid leaks of memory. It means that we may find that what we detach will not include those iframe elements. To workaround such a problem, we may need to detach specific iframes before:

```js
const $copy = $element.children().detach();

const $iframeCopies = [];
$element.children().find('iframe', function () {
	const $this = $(this);
	$iframeCopies.push({
	    $parent: $this.parent(),
	    $prev: $this.prev(),
	    $element: $this.detach(),
	});
});

// restore later
$element.append($copy);

// then restore iframe
$iframeCopies.forEach($copy => {
	$.contains($copy.$parent[0], $copy.$prev[0])
	    ? $copy.$prev.after($copy.$element)
	    : $copy.$parent.append($copy.element);
});
```

In addition, iframes may be sometimes used as wrapped documents rather than loading sources, like implementing an editor. These iframes won't have sources, which means that restoring such iframes will make them empty after reloading empty sources. To work around such a problem, the only way is to destroy and rebuild it.
