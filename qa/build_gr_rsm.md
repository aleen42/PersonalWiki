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
sudo git clone --recursive https://github.com/gnuradio/gnuradio.git
```

###### Suggestions:

- set up your RAM size by **at least 4GB**
- do not try to use `-j2` to accelrate your make process
- guarantee that the directory `/usr/local/src` should have **more than 3.5GB** spaces to set up gr-gsm

#### 2. gr-gsm

###### Dependencies

```bash
sudo apt-get install python-scapy
```

###### Frequencies

China Mobile

- 937,600,000
- 941,100,000
- 951,700,000

China Unicom

- 959166000

#### 3. Questions

- When catchnig imsi from a phone, there are two problems:
    - IMSI is only transmitted during the process of connecting to a base station
    - the rate of collection depends on the code

#### 4. Tutorials of using gsmIMSI

**1. Run `getFrequency.sh`**

After all installation is done, firstly what you should do is to run the script `getFrequency.sh` to get frenquencies of your local region. After then, you can see that there should be some frequencies stored in the file `frequency.dat`.

```bash
sudo bash getFrequency.sh
```

**2. Run `sniffIMSI.py`**

This python script is used to capture gsm data and analysis to emit IMSIs.

```bash
sudo python sniffIMSI.py
```

**3. Run `loopScan.sh**

This script is used to loop for scanning frequencies what you have just captured, with gr-gsm livemon.

```bash
sudo bash loopScan.sh
```