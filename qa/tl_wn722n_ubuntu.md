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
# add the following two lines into the file
# Declare TP-WN727N USB ID to ath9k_htc module
echo "148F 7601" | tee /sys/bus/usb/drivers/ath9k_htc/new_id

exit 0
```

#### Part IV

Finally, the script mentions something about updating your initramfs. It might not be needed but these are kernel modules so that's what we will do by running the following command:

```bash
sudo update-initramfs -k all -u
```

and don't forget to update grub when you are done:

```bash
sudo update-grub
```