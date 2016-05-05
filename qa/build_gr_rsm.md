## Some problems of building gr-rsm [Back](./qa.md)

Here is the official installation turtorial of **gr-rsm**: https://github.com/ptrkrysik/gr-gsm/wiki/Installation, but according to this document, there is some problems when building on the OS, **Ubuntu 14.04 64-bit**.

#### 1. gnuradio

###### Dependencies of Ubuntu 14.04

```bash
sudo apt-get -y install git-core cmake g++ python-dev swig \
pkg-config libfftw3-dev libboost1.55-all-dev libcppunit-dev libgsl0-dev \
libusb-dev libsdl1.2-dev python-wxgtk2.8 python-numpy \
python-cheetah python-lxml doxygen libxi-dev python-sip \
libqt4-opengl-dev libqwt-dev libfontconfig1-dev libxrender-dev \
python-sip python-sip-dev
```

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
sudo wget http://gnuradio.org/releases/gnuradio/gnuradio-3.7.9.2.tar.gz
```

###### Problems

```bash
make[2]: *** [gnuradio-runtime/swig/CMakeFiles/_runtime.swig.dir/runtime_swigPYTHON_wrap.cxx.o] Error 4
make[1]: *** [gnuradio-runtime/swig/CMakeFiles/_runtime.swig.dir/all] Error 2
make: *** [all] Error 2
PyBombs.Packager.source - ERROR - Build failed. See output above for error messages.
PyBombs.Packager.source - ERROR - Problems occured whild building package gnuradio:
Build failed.
PyBombs.Packager.source - ERROR - Error installing package gnuradio. Aborting.
```

###### Solutions
