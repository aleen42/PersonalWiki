## Some problems of building gr-rsm [Back](./qa.md)

Here is the official installation turtorial of **gr-rsm**: https://github.com/ptrkrysik/gr-gsm/wiki/Installation, but according to this document, there is some problems when building on the OS, **Ubuntu 14.04 64-bit**.

#### 1. gnuradio

###### Problems

```bash
PyBombs.install - INFO - Installing package: gnuradio
PyBombs.Packager.source - ERROR - Problems occured whild building package gnuradio:
There should be a source dir in /usr/local/src/gnuradio, but there isn't.
PyBombs.install - ERROR - Error installing package gnuradio. Aborting.
```

###### Solutions

```bash
cd /usr/local/src/
sudo pybombs fetch gnuradio
```

###### Problems

```bash
make[2]: *** [gnuradio-runtime/swig/CMakeFiles/_runtime.swig.dir/runtime_swigPYTHON_wrap.cxx.o] Error 4
make[1]: *** [gnuradio-runtime/swig/CMakeFiles/_runtime.swig.dir/all] Error 2
make: *** [all] Error 2
PyBombs.Packager.source - ERROR - Build failed. See output above for error messages.
PyBombs.Packager.source - ERROR - Problems occured whild building package gnuradio:
```

###### Solutions
