## [轉載] Rain & Water Effect Experiments [Back](./../post.md)

> - Author: [Lucas Bebber](https://github.com/lbebber)
- Origin: https://tympanus.net/codrops/2016/05/03/animated-heat-distortion-effects-webgl/
- Time: May, 3rd, 2016

<br />

> Some experimental rain and water drop effects made with WebGL and shown in different demo scenarios.

<p aling="center">
    <img src="./RainEffects.jpg" />
</p>

Today we’d like to share some WebGL experiments with you. The idea is to create a very realistic looking rain effect and put it in different scenarios. In this article, we’ll give an overview of the general tricks and techniques used to make this effect.

```
Please note that the effect is highly experimental and might not work as expected in all browsers. Best viewed in Chrome.
```

### Getting Started

If we want to make an effect based on the real world, the first step is to dissect how it actually looks, so we can make it look convincing.
If you look up pictures of water drops on a window in detail (or, of course, observed them in real life already), you will notice that, due to refraction, the raindrops appear to turn the image behind them upside down.

<p aling="center">
    <img src="./755px-GGB_reflection_in_raindrops.jpg" />
</p>
<p aling="center">
    <i>Image credits: Wikipedia, <a href="https://en.wikipedia.org/wiki/File:GGB_reflection_in_raindrops.jpg" target="_blank">GGB reflection in raindrop</a></i>
</p>

You’ll also see that drops that are close to each other get merged – and if it gets past a certain size, it falls down, leaving a small trail.
To simulate this behavior, we’ll have to render a lot of drops, and update the refraction on them on every frame, and do all this with a decent frame rate, we’ll need a pretty good performance – so, to be able to use hardware accelerated graphics, **we’ll use WebGL**.
