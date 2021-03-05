## WebAssembly (WASM) [Back](../JavaScript.md)

[WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly) is a new type of language, as well as a low-level assembly-like language which can be run with near-native performance on the web. In most cases, developers always precompiled C/C++ programs into WASM with [**Emscripten**](https://github.com/emscripten-core/emscripten), using [**LLVM**](https://github.com/llvm/llvm-project) and [**Binaryen**](https://github.com/WebAssembly/binaryen).

```mind:height=100,title=how Emscripten works
# C/C++ source code
## Emscripten
### WASM module + JavaScript glue code
```

Here I want to list some useful WASM modules in the future:

|Categories| |
|--:|:--:|
|Computer Vision)|[openCV](https://docs.opencv.org/master/d4/da1/tutorial_js_setup.html)|
|Video|[ffmpeg.wasm](https://github.com/ffmpegwasm/ffmpeg.wasm)|
|Image|[WASM-ImageMagick](https://github.com/KnicKnic/WASM-ImageMagick)|
