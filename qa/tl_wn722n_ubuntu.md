## How to deploy TL-WN722N in Ubuntu 14.04 [Back](./qa.md)

### Driver Installation

#### Part I

Install all the dependencies in need:

```bash
sudo apt-get update
sudo apt-get dist-upgrade
apt-get install gcc build-essential linux-headers-generic linux-headers-`uname -r`
```


#### Part II

Download `backports-3.16-1.tar.gz` here and unzip it:

```bash
tar xvfz backports-3.16-1.tar.gz
```

Enter the uncompressed directory and clean build area:

```bash
cd backports-3.16-1 && sudo make clean
```