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
sudo mv gnuradio-3.7.9.2 gnuradio
```

###### Suggestions:

- set up your RAM size by **at least 4GB**
- 
