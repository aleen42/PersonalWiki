## The Graphics Rendering Pipeline [Back](../glsl.md)

### 1. The Graphics Rendering Pipeline

Similar to CPU, GPU has also accepted some generic orders and data as input, which must follow a path where they will pass through some stages. This path is so-called **The Graphics Rendering Pipeline**.

In the early OpenGL years, this pipeline was completely fixed, which means that all data should pass through the same operations inside this pipeline, and could not skip some of them. These were the pre-shader ages (2002 and earlier).

For example, the following figure has shown how data flows through:

<p align="center">
<img src="./1.png" />
</p>

Between 2002 and 2004, the programmable pipeline has arisen to support replacing some of the fixed stages in the rendering pipeline. However, the language of programming solution has not been unified when developers should code **Cg** (from NVidia) or **HLSL** (from Microsoft).

To realize the importance of compatibilities through different platforms **OpenGL Shading Languages (GLSL)** was born to support developers by a unique C-like shader. In that year, there were only two pieces of units could be replaced: the **vertex processing unit** (vertex shaders, 頂點著色器) and the **fragment processing unit** (fragment shaders, 片面著色器). Another two units were added later: **geometry shaders** (幾何著色器) in 2008 and **compute shaders** (計算著色器) in 2012 respectively.

Since that, the pipeline has changed to this:

<p align="center">
<img src="./2.png" />
</p>

#### 1.1 Geometry Stages

This stage mainly focuses on the transformation of vertex data from its initial state (model coordinates system) to its final state (viewport coordinates system):

- **Vertex data** (頂點數據): all vectorial (矢量) data of geometries like vertices (頂點), normals (法綫), indices (指數), tangents (切綫), binormals (副法綫), texture coordinates (紋理坐標), etc.
- **Texture** (紋理): helps to make renders colourful by displacing vertices according to values stored into a texture.
- **Vertex shader**: responsible for the transformation of the vertices from a local coordinate system to the clip space.
- **Geometry shader**: generate new primitives using the outcome of the vertex shader.
- **Clipping**: clip new primitives and discard outside the clip space.
- **Perspective division** (透视分割): convert our visualization volume into a regular and normalized cube:

  ![](./3.png)

- **Viewport transform**: translate the cube above and scaled to the viewport coordinates, like our screen or window.
- **Rasterizer** (光柵化): transform vectorial data to a discrete representation (離散表徵):

  ![](./4.png)

#### 1.2 Fragment Stages

This stage presents discrete data:

- **Fragment shader**: calculate texture, colours, and lights that applied and combined to form a fragment.
- **Post-fragment processing**: this process includes blending, depth tests, scissor tests, alpha tests, etc. If finally passed, the fragment will be written to the framebuffer (幀緩衝區).

#### 1.3 External Stages

This stage has included the computer shader stage, which can be written to affect any other programmable part of the Graphic Rendering Pipeline.


### 2. Types of shaders

**Vertex shader** and **fragment shader** are both the most important shaders in the whole pipeline, and we can control almost anything in our rendering process via these two shaders. However, enhancement room exists where we can use **Geometry shader** to create arbitrarily shaped primitives (多邊形), like quads, and transform only one vertex (the quad's centre) instead of four vertices.

Unlike vertex shader and fragment shader, the Geometry one is optional which means that you can just skip it in your pipeline. The **Computer shader** is also optional.

As OpenGL evolving every day, the types of shaders may change according to a certain requirement, like **Tessellation shaders** (細分(鑲嵌)著色器).

#### 2.1 Vertex shaders

In such a shader, we can perform any type of data transform, such as apply noise to the positions for a pseudorandom displacement, calculate normals, calculate texture coordinates, calculate vertex colours, prepare the data for a normal mapping shader, and so on.

*Notice: A vertex shader is actually a snippet of code run in GPU processors, and assume that we have a 3D model with 1000 vertices, the vertex shader (code) will be executed 1000 times.*

#### 2.2 Fragment shaders

In such a shader, we can control how to paint each primitive's area by outputting an RGBA colour, which can be calculated from textures, or vertex shader's output data. Like the vertex shader, the fragment shader is also actual a snippet of code, executed in any single pixel of a fragment, but the reality is even worse when doing post-processing shaders such as motion blur (動態模糊), glows (光暈), or screen space ambient occlusion (環境光遮罩), resulting in executing fragment shader in any relational fragment. That's why it is more essential to optimize in fragment shaders than in vertex shaders.

#### 2.3 Geometry shaders

This shader is responsible for rendering primitives parting from the output of the vertex shader. It is executed once per primitive, which is the same as the vertex one. The worst case is when it is used to emit point primitives, while the best one is when emitting triangles (3 times less than the vertex shader).

#### 2.4 Compute shaders

This shader is independent corresponding to vertex, fragment, or geometry shaders, which can affect them. As it does not belong to the pipeline, it can access to all functions (`matrix`, `advanced texture`, etc.) and data types (`vectors`, `matrices`, all texture formats, and `vertex buffers`) that exist in GLSL.

### 3. GPU

GPU is a vectorial and parallel architecture corresponding to CPU, offering high performance at processing fragments, pixels, and vertices, because it can process hundreds of instructions asynchronously via dozens or hundreds of small and very specific cores.

Another advantage of GPU is that all native types are vectorial, which means it can do lots of operations natively.

Assume that there is a structure for a vector of floats:

```glsl
struct Vector3
{
    float x, y, z;
};
```

In CPU, it may need more operations when crossing two vectors:

```glsl
vec3 a;
vec3 b = {1, 2, 3};
vec3 c = {1, 1, 1};

// a = cross(b, c);
a.x = (b.y * c.z) – (b.z * c.y);
a.y = (b.z * c.x) – (b.x * c.z);
a.z = (b.x * c.y) – (b.y * c.x);
```

In GPU, it can directly calculate them in the hardware by calling `cross`:

```glsl
a = cross(b, c);
```

Besides, there are many other built-in operations (directly native or based on native operations) for native types: addition, addition, dot products, and inner/outer multiplications, geometric, trigonometric, and exponential functions. GPU is so essential to support high-performance vector-based operations for most shader computations.

In summary, GPU can:

- make shaders executed at the same time
- make instructions executed in native

### 4. The shader environment

As GLSL relies on OpenGL, we must use it to compile and execute shaders like link, execution, and debug. In addition, resources like textures, vertices, normals, frame buffers, or rendering states can also managed in OpenGL.
