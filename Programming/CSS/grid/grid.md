## Grid [Back](../CSS.md)

Like [Flexbox](../flexbox/flexbox.md), [Grid](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Grid_Layout) is another kinds of CSS layout technics for defining responsive layouts conveniently. Since Chrome 87, we can also easily debug CSS Grid layouts with dev tools when a DOM element is set with `display: grid` or `display: inline-grid`.

When a container has been set with grid layouts, it is easy for children elements to define their position with `grid-column` and `grid-row`. For example, assume that there is a container that has been split into 3 columns of grids of which each width is equal on average:

```css
.container {
    display: grid;
    grid-template-columns: repeat(3, auto);
}
```

Then we can easily use this layout like this:

<p class="codepen" data-height="489" data-theme-id="21735" data-default-tab="css,result" data-user="aleen42" data-slug-hash="eYgrBVa" style="height: 489px; box-sizing: border-box; display: flex; align-items: center; justify-content: center; border: 2px solid; margin: 1em 0; padding: 1em;" data-pen-title="eYgrBVa">
  <span>See the Pen <a href="https://codepen.io/aleen42/pen/eYgrBVa">
  eYgrBVa</a> by aleen42 (<a href="https://codepen.io/aleen42">@aleen42</a>)
  on <a href="https://codepen.io">CodePen</a>.</span>
</p>
<script async src="https://cpwebassets.codepen.io/assets/embed/ei.js"></script>
