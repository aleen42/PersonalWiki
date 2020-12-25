## GLSL Basics [Back](../glsl.md)

GLSL bases on ANSI C and many features of the C programming language can be used in GLSL, except something go against performance or language simplicity (語言易用性).

This chapter mainly covers two topics:

- Language basics
- Shader input/output variables

### 1. Language basics

GLSL version decides how you can code it, which is always bound to a specific OpenGL version. If you want to use some new features, keep in mind checking the minimum version requirements.

#### 1.1 Instructions

Like C, each instruction should end with a semicolon (`;`), and there can be more than one instruction per line:

```glsl
vec4 g; g = vec4(1, 0, 1, 1);
```

All variables declared in a block should end their lifecycle when the block finishes:

```glsl
float a = 1.0;
float b = 2.0;
{
    float a = 4.0;
    float c = a + 1.0; // => 4.0 + 1.0
}
b = b + c; // error
```

#### 1.2 Basic types

GLSL has extended standard C types with others mainly representing vectors or exposing the internal GPU architecture.

|   type    | description                                                                        |
|:---------:|:-----------------------------------------------------------------------------------|
|  `bool`   | binary value of `true` or `false`                                                  |
|   `int`   | including `int` or `uint` (unsigned int)                                           |
| `sampler` | types that represent textures: `sampler1D`, `sampler2D`, `sampler3D`               |
|  `float`  |                                                                                    |
|  Vectors  | `bvec2`, `bvec3`, `bvec4` (vectors of 2, 3, and 4 Boolean elements)                |
|           | `ivec2`, `ivec3`, `ivec4` (vectors of 2, 3, and 4 Integers elements)               |
|           | `uvec2`, `uvec3`, `uvec4` (vectors of 2, 3, and 4 Unsigned Integer elements)       |
|           | `vec2`, `vec3`, `vec4` (vectors of 2, 3, and 4 Floats, single precision)           |
|           | `dvec2`, `dvec3`, `dvec4` (vectors of 2, 3, and 4 Floats, double precision)        |
| Matrices  | `mat2`, `mat3`, `mat4` (2x2, 3x3, and 4x4 Matrices of Floats, single precision)    |
|           | `dmat2`, `dmat3`, `dmat4` (2x2, 3x3, and 4x4 Matrices of Floats, double precision) |
|           | `mat{m}x{n}` like `mat2x3`, `mat3x4` (`m` for columns and `n` for rows)            |
|           | `dmat{m}x{n}` like above                                                           |

*Note: Like C language, float literals in GLSL will be specified as a single-precision float by default without putting the suffix `f`, and `lf` should be putting for specifying as double-precision. Both suffixes are case-insensitive.*

#### 1.3 Variable initializers

To initialize types like vectors or matrices, we must use the constructor:

```glsl
float a = 1.0;
bool switch = false;

ivec3 b = ivec3(1, 2, 3); // OK
uvec2 c = uvec2(-1, 1); // Error, should only contain unsigned integers
vec3 c(1.0, 2.0); // Error, should use assignment
vec3 c = vec3(1.0, 2.0); //OK
```

Vector initialization can also be mixed:

```glsl
vec4 a = vec4(1.0, vec3(0.0, 1.0, 0.0));
vec4 a = vec4(vec3(0.0, 1.0, 0.0), 1.0);
vec4 a = vec4(vec2(1.0, 1.0), vec2(0.5, 0.5));
```

For vectors, they can be seen as structures or arrays, and you can index it like this:

```glsl
vec2 p;
p[0] = 1.0;
p.x = 1.0;
p.y = 2.0;
p.z = 3.0; // Error, p only has two elements.
```

The following are the valid names of the structure's fields:

- `{x, y, z, w}`: positions
- `{r, g, b, a}`: colours
- `{s, t, p, q}`: texture coordinates

GLSL allows to **swizzle** (重組) the components of a vector (that is, construct a new vector by duplicating or reordering the elements):

```glsl
vec4 color1 = vec4(0.5, 0.2, 1.0, 1.0); // RGBA
vec4 color2 = color1.abgr; // equivalent to color1.wzyx

// Grey color based on the red component
vec4 redGray = color1.rrrr;
float red = color1.r;

// Swizzle randomly but valid
vec4 color3 = color1.gbgb;
vec4 color4 = vec4(color1.rr, color2.bb);
vec4 color5 = color1.tptp; // same as .gbgb and .yzyz
color5.xy = vec2(1.0, 0.0);
color5[3] = 2.0; // same as .z = 2.0

// Invalid swizzles
vec2 p;
p = color.rgb; // .rgb is vec3
p[2] = 3.0; // index out of bounds
vec4 color7 = color1.xxqq; // Error, the fields are not from the same set
```

When it comes to GLSL matrices, they are different from a matrix. The first index of GLSL matrices is the column index, while the second one is the row index.

```glsl
mat4 m;
m[0] = vec4(1.0); // fill the first column with 1.0
m[1][1] = 2.0;
m[2] = color1.rrgg; // fill the third column with a swizzled vector 
```

#### 1.4 Vector and Matrix operations

Some arithmetic operators have been overloaded for vectors and matrices to match linear algebraic conventions (綫性代數法則).

```glsl
mat3 R, T, M;
vec3 v, b;
float f;

b = v + f; 

// same as followed
b.x = v.x + f;
b.y = v.y + f;
b.z = v.z + f;

b = T * v;

// same as followed
b.x = T[0].x * v.x + T[1].x * v.y + T[2].x * v.z;
b.y = T[0].y * v.x + T[1].y * v.y + T[2].y * v.z;
b.z = T[0].z * v.x + T[1].z * v.y + T[2].z * v.z;

M = T * R;

// same as followed
M[0][0] = T[0][0] * R[0][0] + T[1][0] * R[0][1] + T[2][0] * R[0][2];
M[1][0] = T[0][0] * R[1][0] + T[1][0] * R[1][1] + T[2][0] * R[1][2];
M[2][0] = T[0][0] * R[2][0] + T[1][0] * R[2][1] + T[2][0] * R[2][2];
M[0][1] = T[0][1] * R[0][0] + T[1][1] * R[0][1] + T[2][1] * R[0][2];
M[1][1] = T[0][1] * R[1][0] + T[1][1] * R[1][1] + T[2][1] * R[1][2];
M[2][1] = T[0][1] * R[2][0] + T[1][1] * R[2][1] + T[2][1] * R[2][2];
M[0][2] = T[0][2] * R[0][0] + T[1][2] * R[0][1] + T[2][2] * R[0][2];
M[1][2] = T[0][2] * R[1][0] + T[1][2] * R[1][1] + T[2][2] * R[1][2];
M[2][2] = T[0][2] * R[2][0] + T[1][2] * R[2][1] + T[2][2] * R[2][2];
```

Sometimes we can see vector as an {m}x1 matrix, and we can translate an {n}x{m} matrices to an {n}x1 vector by multiplying them.

#### 1.5 Castings and Conversions

Casting implicitly can only be done when there won't be precision issues like from `int` to `uint`, from `int` to `float`, from `float` to `double`, and so on. Otherwise, you must cast explicitly.

```glsl
float threshold = 0.5;
int a = int(threshold); // => 0

double value = 0.334lf;
float value1 = float(value); // may lost precision

bool c = true;
float t = float(c); // => 1.0
bool d = false;
float f = float(d); // => 0.0
```

#### 1.6 Code comments

Like C language, use double slashes (`//`) for commenting single line of code or slash-asterisk (`/*`) for commenting blocks of the snippet.

#### 1.7 Flow controls

If-else statement and switch statement are both common cases in the flow controls in any programming languages.

#### 1.8 Loops

For, while and do-while statements are all common cases in loops in any programming languages.

#### 1.9 Structures

We always use structures to describe more complicated types of basic types with a given custom name.

```glsl
struct Texture
{
    vec4 color;
    vec4 bgColor;
};
```

Then, we can declare variant with it:

```glsl
Texture t = Texture(vec4(1.0, 0.0, 0.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));
t.color = vec4(1.0, 1.0, 1.0, 1.0);
```

#### 1.10 Arrays

There are no dynamic arrays in GLSL like C programming language. Once you initialize an array with static capacity, you can't modify it:

```glsl
Texture textures[3];
textures[3] = Texture(vec4(1.0, 0.0, 0.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0)); // error, index out of bounds
```

If you want to get the capacity of an array, use the `.length()` method:

```glsl
for (int i = 0; i < textures.length(); i++)
{
    // do anything
}
```

You cal also initialize an array directly during declaration:

```glsl
Texture textures[] = {Texture(vec4(), vec4())};
```

#### 1.11 Functions

Developers always use functions for reusing code and reduce redundant logical. To some extent,
 proper abstracts of functions can help code more readable. As usual in C, the first keyword is the return type, which should be `void` if you want it to return nothing.

```glsl
void main()
{
    // code
}
```

When it comes to the parameters' definition, it is more complicated because you can describe it with `const`, and `in/out/inout` qualifiers (修飾詞). For instance:

```glsl
vec3 Lighten(const in Light light, const in vec3 position);
```

This function receives a `Light` type variable and a `vec3` variable as input. The qualifier `const` means that the variable will not be modified inside the function. The qualifier `in` means that the variable will remain unchanged after the function call no matter how the function changes it (like passing by value). `out` means that the function won't initialize a new value and modify the parameter directly. After the function call, such a value will be output to the specified variable (like passing by reference). `inout` combines both of above.

```glsl
void MyFunction(in float a, out int b, inout float c)
{
  a = 0.0;
  b = int(c + a);
  c = 3.0;
}

void main()
{
  float in1 = 10.5;
  int out1 = 5;
  float out2 = 10.0;
  MyFunction(in1, out1, out2); // => in1: 10.5, out1: 10.0, out2: 3.0 
}
```

Once parameters have been declared as `out` or `inout`, they should be assigned with values inside a function, which means they can't be combined with `const` qualifier.

If no qualifiers are specified, `in` is the default one.

#### 1.12 Preprocessor

Like in C, GLSL also has a preprocessor. Preprocessor tags start with the character `#`, and they are before the compilation step, which will be evaluated and replaced before compilation. The following processor tags are the most important:

- `#error`
- `#version`
- `#pragma`
- `#define`
- `#if`, `#ifdef`, `#ifndef`, `#else`, `#elif`, `#endif`

Take `#error` tag as an example, if the preprocessor reaches such a tag, the shader will be considered ill-formed (不規範) and not executable:

```glsl
#ifndef DEG2RAD
    #error missing conversion macro
#endif
```

The `#version` tag is meant to output certain GLSL version. It helps ensure the compatibility of your current GLSL version. In common, it will be placed in the first line of each shader.

```glsl
#version 430 // ensure running the GLSL version 4.30 (throw an error when not match)
```

The `#pragma` tag is meant to configure the GLSL compiler like setting up debug/release mode, or optimizations:

```glsl
#pragma debug(on) // #pragma debug(off)
#pragma optimize(on) // #pragma optimize(off)
```

*Note: When developing, it is suggested that turns on debug mode and close optimization for more information when an error occurs. After ensuring that it works exactly like the non-optimized version, you can release it with optimization. Sometimes optimization will lead to some internal mistakes.*

If you want to define some symbols in the preprocessor, you can use the `#define` tag, or remove it with the `#undef` tag:

```glsl
#ifdef PI
    #undef PI
#endif
#define PI 3.141592
```

The `#if` and `#endif` tags specify code between them to compile if the condition applies. `#else` is for else, while `#elif` for else-if.

The `#ifdef` and `#ifndef` are different from `#if` because they only check the list of the preprocessor symbols.

### 2. Shader input and output variables

After learning the basics of GLSL, it is time to learn some functional parts of GLSL.

#### 2.1 Uniform variables

A parameter that is passed from the application to the shaders is called a **uniform** variable. They are always constant, and global.

For example, we can set a uniform variable in the host programming (in C and OpenGL):

```c
// C code to initialize a uniform variable
float lightPositions[] = {0, 10.0f, 0};
glUniform3fv(glGetUniformLocation(programId, "lightPosition"), lightPositions);
```

Then, in the shader, we can access such a variable like this:

```glsl
#version 430
#pragma debug(on)
#pragma optimize(off)

uniform vec3 lightPosition; // => {0, 10.0f, 0}
void main()
{
    // do anything with lightPosition
}
```

We can pass any uniform variables like integers, matrices, structures, etc.

#### 2.2 Other input variables

Some other input variables shared between different pipeline stages must be declared globally in the shader with the keyword `in`.

```glsl
#version 430
#pragma debug(on)
#pragma optimize(off)

in vec3 vertexColor;
out vec4 frameBufferColor; // which will be written into the framebuffer

// fragment shader
void main()
{
    frameBufferColor = vec4(vertexColor, 1.0);
}
```

Like snippet shown above, `vertexColor` is an input variable that holds the output from the last shader (`a vertex shader`)

#### 2.3 Shader output variables

Each shader should have its form of output for the next one. For a fragment shader, the output should at least the colour of a fragment. For a vertex shader, the output should at least the vertex position in clip coordinates, and some other vertex attributes that will be passed to the fragment shader.

We can define such output with the qualifier `out` globally.
