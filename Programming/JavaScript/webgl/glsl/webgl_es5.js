module.exports = {
    getContext: getContext,
    createShader: createShader,
    createProgram: createProgram,
    activeTexture: activeTexture,
    updateTexture: updateTexture,
    createTexture: createTexture,
    createUniform: createUniform,
    setRectangle: setRectangle
};

/**
 * [getContext: to get the context object of a canvas object]
 * @param  {[type]} canvas     [description]
 * @param  {[type]} options={} [description]
 * @return {[type]}            [description]
 */
function getContext(canvas, options) {
    options = Object.assign({}, options);

    var contexts = ['webgl', 'experimental-webgl'];
    var context = null;
    var contextLen = contexts.length;

    for (var i = 0; i < contextLen; i++) {
        try {
            context = canvas.getContext(contexts[i], options);
        } catch (e) {
        }

        if (context !== null) {
            break;
        }
    }

    if (context === null) {
        document.body.classList.add('no-webgl');
    }

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
    var shader = gl.createShader(type);

    /** set the source code in a WebGLShader */
    gl.shaderSource(shader, script);

    /** compile the WebGLShader created before */
    gl.compileShader(shader);

    /** check compiling status */
    var compiled = gl.getShaderParameter(shader, gl.COMPILE_STATUS);

    /** check whether the script can be compiled */
    if (!compiled) {
        /** failed to compile the script of the shader */
        var lastError = gl.getShaderInfoLog(shader);
        console.error("Error compiling shader '" + shader + "':" + lastError);

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
    var vertexShader = createShader(gl, vertexScript, gl.VERTEX_SHADER);
    var fragShader = createShader(gl, fragScript, gl.FRAGMENT_SHADER);

    /** create a temporary WebGLProgram and link it after attaching both shaders created above */
    var program = gl.createProgram();
    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragShader);

    gl.linkProgram(program);

    /** check whether the link is available */
    var linked = gl.getProgramParameter(program, gl.LINK_STATUS);

    if (!linked) {
        /** failed to link */
        var lastError = gl.getProgramInfoLog(program);
        console.error("Error in program linking: " + lastError);

        /** release the WebGLProgram created before */
        gl.deleteProgram(program);

        /** if failed, then return a null */
        return null;
    }

    var positionLocation = gl.getAttribLocation(program, 'a_position');
    var texCoordLocation = gl.getAttribLocation(program, 'a_texCoord');

    var texCoordBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, texCoordBuffer);

    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([
        -1.0, -1.0,
         1.0, -1.0,
        -1.0,  1.0,
        -1.0,  1.0,
         1.0, -1.0,
         1.0,  1.0
    ]), gl.STATIC_DRAW);

    /** enable a vertext attribute array at a given position */
    gl.enableVertexAttribArray(texCoordLocation);

    /** specify the data formats and locations of vertex attributes in a vertex attributes array */
    gl.vertexAttribPointer(texCoordLocation, 2, gl.FLOAT, false, 0, 0);

    /** create a buffer for the position of the rectangle corners */
    var buffer = gl.createBuffer();
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

function createTexture(gl, source, i, wrap = null) {
    if (wrap === null) {
        wrap = gl.CLAMP_TO_EDGE;
    }

    var texture = gl.createTexture();
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
    var location = gl.getUniformLocation(program, 'u_' + name

    var argsLen = arguments.length;
    var args = [];

    for (var i = 1; i < argsLen; i++) {
        args.push(arguments[i]);
    }

    gl['uniform' + type].apply(undefined, [location].concat(args));
}

function setRectangle(gl, x, y, width, height) {
    var x1 = x;
    var x2 = x + width;
    var y1 = y;
    var y2 = y + height;

    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([
        x1, y1,
        x2, y1,
        x1, y2,
        x1, y2,
        x2, y1,
        x2, y2
    ]), gl.STATIC_DRAW);
}
