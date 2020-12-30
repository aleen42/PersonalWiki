## Vertex Shaders [Back](../glsl.md)

Vertex shaders are responsible for transforming the incoming geometry into something suitable to be rasterized(光柵化), so the inputs and outputs of vertex shaders should be well-defined.

### 1. Vertex shader inputs

There are only two kinds of inputs for a vertex shader: **vertex attributes**, and **uniform variables**.

#### 1.1 Vertex attributes

A **vertex attribute** is simply the information you pass to the shader. Examples of vertex attributes could be:

- Texture coordinates
- Normals (常態)
- Tangents (切綫)
- Per-vertex colours

As the evolving processes of OpenGL, vertex attributes have been specified in a buffer described by a data type like **vertex array object (VAO)**, which will hold position and texture coordinates at once. The following snippet has shown how to set up such a buffer in the OpenGL host application:

```c
// Create vertex array object (VAO)
glGenVertexArrays(1, &vaoId);
glBindVertexArray(vaoId);

// Create vertex buffer object (VBO)
glGenBuffers(1, &vboId);
glBindBuffer(GL_ARRAY_BUFFER, vboId);

// Fill buffer with data
glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), bufferData, GL_STATIC_DRAW);

// Tell OpenGL how to locate positions inside the buffer
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4 + 2) * sizeof(GLfloat), NULL);

// Tell OpenGL how to locate texture coordinates inside the buffer
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (4 + 2) * sizeof(float), (void*) (4 * sizeof(float)));

// Unbind VAO & VBO via passing 0
glBindVertexArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
```

After setting up a VAO with two vertex attributes: positions with index 0, and texture coordinates with index 1, we can see how to access the buffer from the vertex shader.

```glsl
#version 430
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textCoordinates;

void main()
{
    // do something
}
```

As we can see, we have used `layout` qualifier to index vertex attributes:

```glsl
layout (location = attribute index) in vec4 position;
```

#### 1.2 Uniform variables

Except for vertex attributes, we can also pass variables unrelated with the pipeline or any other constraints. These kinds of variables are called **uniform variables** mentioned [above](../glsl_basics/glsl_basics.md#21-uniform-variables).

In the host application:

```c
// the shader must be activated/bound before setting uniform or vertex attributes
glUseProgram(programId);

GLfloat modelView[16];
glUniformMatrix2fv(glGetUniformLocation(programId, "modelView"), 1, GL_FALSE, modelView);

GLfloat projection[16];
glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, projection);
```

In the vertex shader:

```glsl
#version 430
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec4 position;
uniform mat4 modelView;
uniform mat4 projection;

void main()
{
    gl_Position = projection * modelView * position;
}
```

`gl_Position` is a special (built-in) variable that holds the transformed vertex position, which is the only requirement for a vertex shader. If it is not assigned inside the procedure, the shader will get a compiler error.

If we compute `projection * modelView` in the CPU, and pass it through uniform variables:

```glsl
#version 430
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec4 position;
uniform mat4 projectionModelView;

void main()
{
    gl_Position = projectionModelView * position;
}
```

### 2. Vertex shader outputs

Vertex shaders can output values to the next stage in the pipeline: geometry shaders.

```glsl
#version 430
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textCoordinates;

uniform mat4 modelView;
uniform mat4 projection;

smooth out vec2 textCoordinatesInterpolation;

void main()
{
    gl_Position = projection * modelView * position;
    
    // output to the next stage
    textCoordinatesInterpolation = textCoordinatesInterpolation;
}
```

`smooth` qualifier helps the value interpolate in a [perspective-correct (透視校正)](https://zh.wikipedia.org/zh-hans/%E9%80%8F%E8%A7%86%E6%A0%A1%E6%AD%A3) fashion.

### 3. Drawing a simple geometry sample

To draw such a simple geometry, we also need a fragment shader to run it.

```glsl
// Fragment Shader
#version 430
#pragma debug(on);
#pragma optimize(off);

uniform vec4 solidColor;

out vec4 frameBufferColor;

void main()
{
    frameBufferColor = solidColor;
}
```

This fragment shader paints the whole surface with a solid colour provided with a uniform variable.

If we compute the needed values' vertex positions for a teapot, we will get a render like 
