## webgl.js [Back](../glsl.md)

**webgl.js** is a JavaScript file, which will export some application programming interfaces of WebGL.

```js
module.exports = {
    getContext,
    createShader,
    createProgram,
    activeTexture,
    updateTexture,
    createTexture,
    createUniform,
    setRectangle,
};

/**
 * [getContext: to get the context object of a canvas object]
 * @param  {[type]} canvas     [description]
 * @param  {[type]} options={} [description]
 * @return {[type]}            [description]
 */
function getContext(canvas, options) {
    options = Object.assign({}, options);

    const context = ['webgl', 'experimental-webgl'].reduce((context, key) => {
        if (!context) return context;
        try {
            return canvas.getContext(key, options);
        } catch (ignore) {
            return context;
        }
    }, null);

    !context && document.body.classList.add('no-webgl');
    return context;
}

/**
 * [createShader: cretae the specific shader object from a script]
 * @param  {[type]} gl     [description]
 * @param  {[type]} script [description]
 * @param  {[type]} type   [description]
 * @return {[type]}        [description]
 */
function createShader(gl, script, type) {
    /** create a WebGLShader object */
    const shader = gl.createShader(type);

    /** set the source code in a WebGLShader */
    gl.shaderSource(shader, script);

    /** compile the WebGLShader created before */
    gl.compileShader(shader);

    /** check compiling status */
    const compiled = gl.getShaderParameter(shader, gl.COMPILE_STATUS);

    /** check whether the script can be compiled */
    if (!compiled) {
        /** failed to compile the script of the shader */
        const lastError = gl.getShaderInfoLog(shader);
        console.error(`Error compiling shader '${shader}':${lastError}`);

        /** release the WebGLShader created before */
        gl.deleteShader(shader);

        /** if failed, then return a null */
        return null;
    }

    /** if successful, then return the created shader */
    return shader;
}

function createProgram(gl, vertexScript, fragScript) {
    /** create the vertex shader and the fragment shader respectively */
    const vertexShader = createShader(gl, vertexScript, gl.VERTEX_SHADER);
    const fragShader = createShader(gl, fragScript, gl.FRAGMENT_SHADER);

    /** create a temporary WebGLProgram and link it after attaching both shaders created above */
    const program = gl.createProgram();
    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragShader);

    gl.linkProgram(program);

    /** check whether the link is available */
    const linked = gl.getProgramParameter(program, gl.LINK_STATUS);

    if (!linked) {
        /** failed to link */
        const lastError = gl.getProgramInfoLog(program);
        console.error(`Error in program linking: ${lastError}`);

        /** release the WebGLProgram created before */
        gl.deleteProgram(program);

        /** if failed, then return a null */
        return null;
    }

    const positionLocation = gl.getAttribLocation(program, 'a_position');
    const texCoordLocation = gl.getAttribLocation(program, 'a_texCoord');

    const texCoordBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, texCoordBuffer);

    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([
        -1.0, -1.0,
        1.0, -1.0,
        -1.0, 1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    ]), gl.STATIC_DRAW);

    /** enable a vertext attribute array at a given position */
    gl.enableVertexAttribArray(texCoordLocation);

    /** specify the data formats and locations of vertex attributes in a vertex attributes array */
    gl.vertexAttribPointer(texCoordLocation, 2, gl.FLOAT, false, 0, 0);

    /** create a buffer for the position of the rectangle corners */
    const buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.enableVertexAttribArray(positionLocation);
    gl.vertexAttribPointer(positionLocation, 2, gl.FLOAT, false, 0, 0);

    return program;
}

function activeTexture(gl, i) {
    /** to select the active texture unit */
    gl.activeTexture(gl['TEXTURE' + i]);
}

function updateTexture(gl, source) {
    /** to specify a 2D texture image with a given source */
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, source);
}

function createTexture(gl, source, i, wrap) {
    if (!wrap) {
        wrap = gl.CLAMP_TO_EDGE;
    }

    const texture = gl.createTexture();
    activeTexture(gl, i);
    gl.bindTexture(gl.TEXTURE_2D, texture);

    /** set the parameters so we can render any size image */
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, wrap);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, wrap);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    updateTexture(gl, source);

    return texture;
}

function createUniform(gl, program, type, name) {
    /** return the location of a uniform variable. */
    const location = gl.getUniformLocation(program, `u_${name}`);
    gl[`uniform${type}`].apply(undefined, [location, ...[].slice.call(arguments, 1)]);
}

function setRectangle(gl, x, y, width, height) {
    const x1 = x, x2 = x + width, y1 = y, y2 = y + height;
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([
        x1, y1,
        x2, y1,
        x1, y2,
        x1, y2,
        x2, y1,
        x2, y2
    ]), gl.STATIC_DRAW);
}
```
