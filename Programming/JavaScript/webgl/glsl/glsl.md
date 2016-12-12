## GLSL [Back](./../webgl.md)

**GLSL**, a.k.a OpenGL Shading Language, is a high-level shading (著色) language based on the syntax of the C programming language. It was created to give developers more direct controls of the graphics pipeline without having to use ARB assembly language, or hardware-specific languages.

GLSL shaders are not stand-alone applications, because they require an application that utilizes the OpenGL APIs, which is available on many different platforms (e.g., GNU/Linux, Mac OS X, Windows).

In this document, I will note that how to use it in JavaScript.

### Utils

Before using this language, we should set up some utils to use before.

#### webgl.js

**webgl.js** is a JavaScript file, which will export some application programming interfaces of WebGL. Specific implementation can be checked in the following file:

- [webgl_es5.js](./webgl_es5.js)
- [webgl_es6.js](./webgl_es6.js)

```js
/** ES 5 */
module.exports = {
    getContext: function (canvas, options) { /** ... */ },
    createProgram: function (gl, vertexScript, fragScript){ /** ... */ },
    createShader: function (gl, script, type) { /** ... */ },
    createTexture: function (gl, source, i, wrap) { /** ... */ },
    createUniform: function (gl, program, type, name) { /** ... */ },
    activeTexture: function (gl, i) { /** ... */ },
    updateTexture: function (gl, source) { /** ... */ },
    setRectangle: function (gl, x, y, width, height) { /** ... */ }
};

/** ES 6 */
export function getContext(canvas, options = {}) { /** ... */ }
export function createProgram(gl, vertexScript, fragScript) { /** ... */ }
export function createShader(gl, script, type) { /** ... */ }
export function createTexture(gl, source, i, wrap = null) { /** ... */ }
export function createUniform(gl, program, type, name, ...args) { /** ... */ }
export function activeTexture(gl, i) { /** ... */ }
export function updateTexture(gl, source) { /** ... */ }
export function setRectangle(gl, x, y, width, height) { /** ... */ }
```

If you want to import all the interfaces, you can use it by importing like this:

```js
/** ES 5 */
const WebGL = require('./webgl.js');

/** ES 6 */
import * as WebGL from './webgl.js';
```

#### gl-obj.js

**gl-obj.js** is a JavaScript file, which aims to create an WebGL object, which takes [**vertex shaders**](https://www.opengl.org/wiki/Vertex_Shader), and [**fragment shader**](https://www.opengl.org/wiki/Fragment_Shader) as inputs.

```js
import * as WebGL from './webgl.js';

export default function GL(canvas, options, vert, farg) {
    this.canvas = canvas;
    this.width = canvas.width;
    this.height = canvas.height;
    
    this.gl = WebGL.getContext(canvas, options);
    this.program = this.createProgram(vert, frag);
    this.useProgram(this.program);
}

GL.prototype.createProgram = function (vert, frag) {
    return WebGL.createProgram(this,gl, vert, frag);
};

GL.prototype.useProgram = function (program) {
    this.program = program;
    this.gl.useProgram(program);
};

GL.prototype.createTexture = function (source, i, wrap) {
    return WebGL.createTexture(this.gl, source, i, wrap);
};

GL.prototype.createUniform = function (type, name, ...v) {
    WebGL.createUniform(this.gl, this.program, type, name, ...v);
};

GL.prototype.activeTexture = function (i) {
    WebGL.activeTexture(this.gl, i);
};

GL.prototype.updateTexture = function (source) {
    WebGL.updateTexture(this.gl, source);
};

GL.prototype.draw = function () {
    WebGL.setRectangle(this.gl, -1, -1, 2, 2);
    this.gl.drawArrays(this.gl.TRIANGLES, 0, 6);
};
```
