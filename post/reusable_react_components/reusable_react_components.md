## [原創] How to make React components actually reusable [Back](./../post.md)

<p align="center">
    <img class="progressiveMedia-noscript js-progressiveMedia-inner" src="https://cdn-images-1.medium.com/max/800/1*5jIE1tOzVSuz5NPHsfeQ8w.png">
</p>

Recently, I have translated an article written by [Alex Grigoryan](https://medium.com/@lexgrigoryan?source=post_header_lockup), which is mainly to describe how Walmart achieved reusablility with React Components. Due to this translation, I also want to write another article here to summarize how we can actually make this happen.

Firstly, before the discussion, we should know about one point, which is claimed by the author - **reusability is a process that touches every stage of development and every level of an organization. Therefore, we can not implement it through just technique approaches**.

Then, here is a list of todo items, which can helpfully facilitate reusabilitiy of React components:

- components need to be versioned, easy to install, and upgradeable.
- provide a prototype for linting, transpilation, and bundling.
- create a stable Continuous Integration/Continuous Deployment system to solve the problem of dependencies within components.
- create a explorer system to make components able to be searched by other teams.
- have a proposal system to let developers discuss a new component they're going to create, so that other teams can give out their suggestions.
- open the source code of all components, even though inner applications of your organization are built with those.

