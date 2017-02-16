## [原創] How to make React components actually reusable [Back](./../post.md)

Recently, I have translated an article written by [Alex Grigoryan](https://medium.com/@lexgrigoryan?source=post_header_lockup), which is mainly to describe how Walmart achieved reusablility with React Components. Due to this translation, I also want to write another article here to summarize how we can actually make this happen.

Firstly, before the discussion, we should know about one point, which is claimed by the author - **reusability is a process that touches every stage of development and every level of an organization. Therefore, we can not implement it through just technique approaches**.

Then, here is a list of todo items, which can helpfully facilitate reusabilitiy of React components:

- components need to be versioned, easy to install, and upgradeable.
- provide a prototype for linting, transpilation, and bundling.
- create a stable Continuous Integration/Continuous Deployment system to solve 
