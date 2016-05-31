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

Build and Compile:

```bash
sudo make
```

If you have met some error while compiling, following these instructions to specify the driver you want to build and install by running the following command and make again:

```bash
sudo make defconfig-ath9k && sudo make
```

If there is no error, then install:

```bash
sudo make install
```

#### Part III

Load drivers at boot time:

```bash
echo "ath9k" | sudo tee -a /etc/modules
echo "ath9k_htc" | sudo tee -a /etc/modules
```

Edit `rc.local`:

```bash
# sudo vim /etc/rc.local


```