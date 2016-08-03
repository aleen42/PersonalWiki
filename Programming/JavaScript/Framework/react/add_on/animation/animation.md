## Animation [Back](./../add_on.md)

React provides a `ReactTransitionGroup` add-on component as a low-level API for animation, and a `ReactCSSTransitionGroup` for easily implementing basic CSS animations and transitions.

### High-level API: `ReactCSSTransitionGroup`

`ReactCSSTransitionGroup` is based on `ReactTransitionGroup` and is an easy way to perform CSS transitions and animations when a React component enters or leaves the DOM. It's inspired by the excellent [ng-animate](http://www.nganimate.org/) library.

#### Getting Started

`ReactCSSTransitionGroup` is the interface to ReactTransitions. This is a simple element that wraps all of the components you are interested in animating. Here's an example where we fade list items in and out.

{%ace edit=false, lang='jsx', theme='tomomrrow'%}
