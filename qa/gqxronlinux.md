## How to build up gqxr in Ubuntu [Back](./qa.md)

#### 1. make sure any other source or binary installation of gqrx have been removed

```bash
sudo apt-get purge --auto-remove gqrx
sudo apt-get purge --auto-remove gqrx-sdr
```

#### 2. add new repositores to the package manager

```bash
sudo add-apt-repository -y ppa:bladerf/bladerf        (for 14.04 - 15.10 only)
sudo add-apt-repository -y ppa:ettusresearch/uhd
sudo add-apt-repository -y ppa:myriadrf/drivers
sudo add-apt-repository -y ppa:myriadrf/gnuradio
sudo add-apt-repository -y ppa:gqrx/gqrx-sdr
sudo apt-get update
```