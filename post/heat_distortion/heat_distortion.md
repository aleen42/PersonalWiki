## [轉載] Animated Heat Distortion Effects with WebGL [Back](./../post.md)

> - Author: [Lucas Bebber](https://github.com/lbebber)
- Origin: https://tympanus.net/codrops/2016/05/03/animated-heat-distortion-effects-webgl/
- Time: May, 3rd, 2016

<br />

> A tutorial on how to use fragment shaders in WebGL to create an animated heat haze distortion effect on images and text.

<p align="center">
    <img src="./DistortionEffect_800x600.jpg" />
</p>

Today we want to show you how to create some realistic looking heat haze distortion effects using fragment shaders in WebGL. The idea is to add a subtle animated distortion to a static image and some text.

> **Attention**: The demos use some modern web technology that might not work in older browsers.

**Please note that the current ZIP file is the compiled build of this project; source files and GitHub link are coming soon! Stay tuned.**

### Overview

For this article, we’ll pick apart one of the demos to give you an overview of how it works.

This effect uses **WebGL**. We’ve already seen WebGL being used in [some](http://tympanus.net/codrops/2016/04/26/the-aviator-animating-basic-3d-scene-threejs/) [experiments](http://tympanus.net/codrops/2015/11/04/rain-water-effect-experiments/) posted here on Codrops. [Here you can see an introduction on how it works](http://tympanus.net/codrops/2015/11/04/rain-water-effect-experiments/#WebGL_20). For a more in-depth explanation, take a look at the [WebGL Fundamentals](http://webglfundamentals.org/) page, look into [](http://learningwebgl.com/blog/)Learning WebGL, or start right away with [three.js](http://threejs.org/) or [pixi.js](http://www.pixijs.com/).

The important thing to have in mind for this effect is how fragment shaders, or pixel shaders, work: it runs a function for every pixel of the area that is being processed – in our case, the entire canvas – and returns a color, which will be set for the said pixel. In order to be able to do what we want with the shader, we can send information to it, such as the current pixel position, images (as textures), mouse position, etc.

Let’s look into a few aspects of the demo to get an idea of how we can use it.

### Distortion

The heart of this effect is the heat haze distortion. First let’s have a look at how we can draw a regular image, and then we’ll look into how we can distort it.

This is how we can get the color of a pixel in a texture in the same position as the pixel being processed currently by the shader:

```glsl
// "attribute", "varying" and "uniform" variables are values passed down from
// other parts of the code: the program, the vertex shader, etc.
varying vec2 position;
uniform sampler2D texture;

void main(){
    // Get the color of the pixel at the current position
    vec4 color=texture2D(texture,position);

    gl_FragColor=color;
}
```

<p align="center">
    <img src="./distortion-normal.jpg" />
</p>

Instead of simply getting the pixel from the current position though, we can apply some transform the position value to get the pixel from a different position. For example:

```glsl
...
float distortion=position.y*0.2;
vec4 color=texture2D(texture,vec2(position.x+distortion,position.y));
```

<p align="center">
    <img src="./distortion-slant.jpg" />
</p>

Now, to get a simple but interesting distortion, we could vary the position based on a sine wave.

<p align="center">
    <img src="./sine.png" />
</p>

Here we will add to the x position a sine curve based on the y position.

```glsl
...
// Since the position usually goes from 0 to 1, we have to multiply the result
// of the sine by a small value so to not make the effect too harsh.
// For the same reason, we have to multiply the value inside the sine function
// by a large value if we want a higher frequency of the curves.
float frequency=100.0;
float amplitude=0.003;
float distortion=sin(position.y*frequency)*amplitude;
vec4 color=texture2D(texture,vec2(position.x+distortion, position.y));
```

