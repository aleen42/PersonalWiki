## gl-obj.js [Back](../glsl.md)

**gl-obj.js** is a JavaScript file, which aims to create an WebGL object, taking [**vertex shaders**](https://www.opengl.org/wiki/Vertex_Shader), and [**fragment shader**](https://www.opengl.org/wiki/Fragment_Shader) as inputs.

```js
const WebGL = require('webgl.js');

function GL(canvas, options, vert, frag) {
    this.canvas = canvas;
    this.width = canvas.width;
    this.height = canvas.height;
    
    this.gl = WebGL.getContext(canvas, options);
    this.program = this.createProgram(vert, frag);
    this.useProgram(this.program);
}

const PROTO = GL.prototype;
Object.assign(PROTO, {
    createProgram(...args) { return WebGL.createProgram.apply(0, [this.gl, ...args]) },
    createTexture(...args) { return WebGL.createTexture.apply(0, [this.gl, ...args]) },
    createUniform(...args) { return WebGL.createUniform.apply(0, [this.gl, this.program, ...args]) },
    activeTexture(...args) { return WebGL.activeTexture.apply(0, [this.gl, ...args]) },
    updateTexture(...args) { return WebGL.updateTexture.apply(0, [this.gl, ...args]) },
    useProgram(program) {
        this.program = program;
        this.gl.useProgram(program);        
    },
    draw() {
        WebGL.setRectangle(this.gl, -1, -1, 2, 2);
        this.gl.drawArrays(this.gl.TRIANGLES, 0, 6);        
    },
});
```
