## Components [Back](./../angular1.md)

The **template** (the part of the view containing the bindings and presentation logic) acts as a blueprint for how our data should be organized and presented to the user. The **controller** provides the context in which the bindings are evaluated and applies behavior and logic to our template.

However, there are still a couple of areas we can do better:

- What if we want to reuse the same functionality in a different part of the application?
- The scope is not isolated from other parts of the page, which means that unrelated change in a different part of the page could have unexpected side effects on views.

These two problems has led us to use **components**.

Since the combination (**template** + **controller**) is such a common pattern, AngularJS provides an easy way to combine them together into reusable and isolated entities, a.k.a **components**. To eliminate risk of effect from other parts of the application, AngularJS has also created a so-called **isolate scope** for each instance of components. 