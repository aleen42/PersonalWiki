## GLSL [Back](./../webgl.md)

**GLSL**, a.k.a OpenGL Shading Language, is a high-level shading (著色) language based on the syntax of the C programming language. It was created to give developers more direct controls of the graphics pipeline without having to use ARB assembly language, or hardware-specific languages.

GLSL shaders are not stand-alone applications, because they require an application that utilizes the OpenGL APIs, which is available on many different platforms (e.g., GNU/Linux, Mac OS X, Windows).

In this document, I will note that how to use it in JavaScript.

### Utils

Before using this language, we should set up some utils to use before.

#### webgl.js

**webgl.js** is a JavaScript file, which will export some application programming interfaces of WebGL.

```js
/** ES 5 */
module.exports = {
    getContext: function getContext(canvas, options) { /** ... */ },
    createProgram
}

/** ES 6 */
export function getContext(canvas, options = {}) { /** ... */ }
```

If you want to import all the interfaces, you can use it by importing like this:

```js
/** ES 6 */
import * as WebGL from './webgl.js';
```

#### gl-obj.js

**gl-obj.js** is a JavaScript file, which aims to create an WebGL object, which takes [**vertex shaders**](https://www.opengl.org/wiki/Vertex_Shader), and [**fragment shader**](https://www.opengl.org/wiki/Fragment_Shader) as inputs.
