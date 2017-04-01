## [轉載] Basics of CSS Blend Modes [Back](./../post.md)

> - Author: [Chris Coyier](https://css-tricks.com/author/chriscoyier/)
> - Origin: https://css-tricks.com/basics-css-blend-modes/
> - Time: Feb, 28th, 2014

Bennett Feely has been doing a good job of [showing people the glory of CSS blend modes](./../css_blend_mode/css_blend_mode.md). There are lots of designerly effects that we're used to seeing in static designs (thanks to Photoshop) that we don't see on the web much, with dynamic content. But that will change as CSS blend modes get more support. I'd like to look at the different ways of doing it, since it's not exactly cut and dry.

### CSS Multiple Backgrounds Blend Modes

You can blend `background-images` together, or blend them with background-color. It's a simple as:

```css
.blended {
    background-image: url(face.jpg);
    background-color: red;
    background-blend-mode: multiply;
}
```

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="rrBJQx" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="Background Blending" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/rrBJQx/">Background Blending</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

`multiply` is a nice and useful one, but there is also: `screen`, `overlay`, `darken`, `lighten`, `color-dodge`, `color-burn`, `hard-light`, `soft-light`, `difference`, `exclusion`, `hue`, `saturation`, `color`, and `luminosity`. And also `normal` which reset it.

Adobe (who works on [the spec](http://dev.w3.org/fxtf/compositing-1/) for this stuff, of course) created this Pen for playing with the different possibilities here:

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="FeiCp" data-default-tab="result" data-user="adobe" data-embed-version="2" data-pen-title="CSS Element Background Blend Modes" class="codepen">See the Pen <a href="http://codepen.io/adobe/pen/FeiCp/">CSS Element Background Blend Modes</a> by Adobe Web Platform (<a href="http://codepen.io/adobe">@adobe</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

A single element can have more than one background, [stacked up](http://css-tricks.com/stacking-order-of-multiple-backgrounds/). Like:

```css
.graphic-or-whatever {
    background:
        url(grid.png),
        url(building.jpg)
}
```

Those can blend too simply by adding a `background-blend-mode`.

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="GjKQbP" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="Multiple Background Blending" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/GjKQbP/">Multiple Background Blending</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### Arbitrary HTML Elements Blend Modes

Blending backgrounds together is pretty cool, but personally I'm less excited about that than I am about blending arbitrary HTML elements together. Like a `<h1>` title over a background, for example. Or even text over text.

I saw this at an airport the other day and snapped a pic because I thought it looked neat and figured I could figure out how to do it on the web:

![](./1.jpg)

My first attempt to recreate it, I used opacity. But opacity really dulls the colors and doesn't make those overlapping bits have the extra darkness they should have. CJ Gammon [showed me](http://codepen.io/cjgammon/pen/nEzpj) there is a blending property precisely for this purpose: `mix-blend-mode`.

So to reproduce this:

```html
<h1>hungry?</h1>
```

Then break it up into ` `s with Lettering.js:

```js
$("h1").lettering();
```

Then squeeze the letters together with negative letter-spacing, set the `mix-blend-mode`, and colorize:

```css
h1 {
    font-size: 7rem;
    font-weight: 700;
    letter-spacing: -1.25rem;
}

h1 span {
    mix-blend-mode: multiply;
}
h1 span:nth-child(1) {
    color: rgba(#AB1795, 0.75);
}
/* etc, on coloring */
```

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="mAbxya" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="Overlapping Letters" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/mAbxya/">Overlapping Letters</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

Like I mentioned, real web text over image is a pretty sweet use case if you ask me:

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="RGbrPq" data-default-tab="css,result" data-user="aleen42" data-embed-version="2" data-pen-title="RGbrPq" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/RGbrPq/">RGbrPq</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### Canvas Blend Modes

The DOM blend mode stuff is most interesting to me, but it should be noted that `<canvas>` has blend modes as well and it has a bit deeper support (see below for all that).

You set it on the canvas context. So like:

```js
var canvas = document.getElementById('canvas');
var ctx = canvas.getContext('2d');

ctx.globalCompositeOperation = 'multiply';
```

That value can be any of those I listed above. Here's a simple demo:

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="Kkliq" data-default-tab="js,result" data-user="chriscoyier" data-embed-version="2" data-pen-title="canvas blend modes" class="codepen">See the Pen <a href="http://codepen.io/chriscoyier/pen/Kkliq/">canvas blend modes</a> by Chris Coyier (<a href="http://codepen.io/chriscoyier">@chriscoyier</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

And a fancy one where you can see the blending give the demo life:

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="foktm" data-default-tab="js,result" data-user="soulwire" data-embed-version="2" data-pen-title="sketch.js Demo" class="codepen">See the Pen <a href="http://codepen.io/soulwire/pen/foktm/">sketch.js Demo</a> by Justin Windle (<a href="http://codepen.io/soulwire">@soulwire</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### SVG Blend Modes

As you might suspect, SVG does have its own mechanism for doing this. One way to do it is to define it within the `<svg>` itself, and it's fairly complicated:

```html
<svg>

    <defs>

        <filter id="f1" x="0" y="0" width="1" height="1">
            <feImage xlink:href="#p1" result="p1"/>
            <feImage xlink:href="#p2" result="p2"/>
            <feBlend mode="multiply" in="p1" in2="p2" />
        </filter>

        <path id="p1" d='M100 100 L200 100 L200 200 L100 200 Z' fill='#00FFFF'/>
        <path id="p2" d='M150 150 L250 150 L250 250 L150 250 Z' fill='#CC3300'/>

    </defs>

    <rect width="100%" height="100%" filter="url(#f1)"/>
</svg>
```

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="ZpzxWZ" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="ZpzxWZ" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/ZpzxWZ/">ZpzxWZ</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

And [a more complex example](http://codepen.io/chriscoyier/pen/tCykv).

The good news is that `mix-blend-mode` will work on inline SVG. So if you're using SVG that way, you can target the shapes themselves with classes or whatever and give them whatever blend mode you want.

Here's an example by Bennet that does just that:

<p>
<p data-height="300" data-theme-id="21735" data-slug-hash="KDkCj" data-default-tab="html,result" data-user="bennettfeely" data-embed-version="2" data-pen-title="KDkCj" class="codepen">See the Pen <a href="http://codepen.io/bennettfeely/pen/KDkCj/">KDkCj</a> by Bennett Feely (<a href="http://codepen.io/bennettfeely">@bennettfeely</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
</p>

### Browser Support

[For canvas](http://caniuse.com/#feat=canvas-blending): Firefox 20+, Chrome 30+, Safari 6.1+, Opera 17+, iOS 7+, Android 4.4+. Worst bad news: No IE.

[For HTML/CSS](http://caniuse.com/#feat=css-backgroundblendmode): Firefox 30+, Chrome 35+, Safari 6.1 (apparently not 7?). Not quite as supported as canvas.

At this second, for Chrome, you'll have to run Canary, go to chrome://flags/ and enable "experimental Web Platform features".

This actually it a bit more complicated, so if you really want to dig in and know about support, check out the [Support Matrix](http://html.adobe.com/webplatform/graphics/blendmodes/browser-support/) from Adobe.

### Progressive Enhancement

What is nice about blending is that the whole point is designerly effects. If they aren't supported, you can take care to make sure the fallback is still readable (progressive enhancement!).

Here's [a recent thought](http://adactio.com/journal/6692/) by Jeremy Keith:

> It is entirely possible—nay, desirable—to use features long before they are supported in every browser. That’s how we move the web forward.

So one way to do support is to look at the design in a non-supporting browser and if it is still readable/usable, you're good, no further action required.

If the result ends up unreadable/unusable, you could tweak things around until they are, or run a test to determine support and do something specific in the case of non-support.

To test for support, I guess you could do test for the property you want to use:

```js
var supportsMixBlendMode = window.getComputedStyle(document.body).mixBlendMode;

var supportsBackgroundBlendMode = window.getComputedStyle(document.body).backgroundBlendMode;
```

If the returned value is "normal" (or anything other than `undefined`) support is there, otherwise not. Then probably apply a class to the `<html>` element so you can know that and use it anywhere in your CSS to adjust things, Modernizr style. Perhaps they'll even do a test for it in the future.

Unless it's not that simple in which case let me know.
