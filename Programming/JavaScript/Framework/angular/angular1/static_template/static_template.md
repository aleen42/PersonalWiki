## Static Template [Back](./../angular1.md)

To illustrate how AngularJS enhances standard HTML, we may always create a purely static HTML page, and then examine how we can use AngularJS to turn it into a template, which will dynamically display according to any set of data.

After checkout the code, we can see that in this step, we will have two lists of information about two phones:

```html
<ul>
    <li>
        <span>Nexus S</span>
        <p>
            Fast just got faster with Nexus S.
        </p>
    </li>
    <li>
        <span>Motorola XOOM™ with Wi-Fi</span>
        <p>
            The Next, Next Generation tablet.
        </p>
    </li>
</ul>
```

And how to use AngularJS to dynamically generate the same list?
