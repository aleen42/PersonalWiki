## How to use ffmpeg in c/c++ [Back](./qa.md)

**Qt Creator** is a way for you to use ffmpeg in c/c++, and [here](http://infernusweb.altervista.org/wp/download/HMI/UsingFFMPEGinCwithQtCreator.pdf) you can read more for details

#### i. Ffmpeg as a system call

The built version of FFMPEG can be called by shell with an argument list (see the wiki on the
official web site), so to use this into a C++ code it is necessary to implement a **QProcess** that can start a program.

```bash
ffmpeg -i inputMovie.avi -acodec pcm_s16le outputAudioFile.wav
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
