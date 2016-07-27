## Language Tooling [Back](./../tooling_integration.md)

### ES2015 with JSX

#### In-browser JSX Transform

If you like using JSX, Babel 5 provided an in-browser ES2015 and JSX transformer for development called browser.js that can be included from [CDNJS](https://cdnjs.com/libraries/babel-core/5.8.34).

With that JavaScript file, we can just include a `<script type="text/babel">` tag to engage the JSX transformer.

> Note:

> The in-browser JSX transformer is fairly large and results in extraneous computation client-side that can be avoided. Do not use it in production

#### Productionizing: Precompiled JSX

If you have npm, you can run: 

{% edit=false  %}
npm install -g babel-cli
