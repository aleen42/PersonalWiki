## How to install double-boot Ubuntu in a Macbook Air [Back](./qa.md)

### Download Ubuntu image

The installation need a copy of the Ubuntu desktop ISO image. **Be sure to choose a 64-bit version**, which can boot up in both BIOS and EFI modes.

### Write to a empty USB Driver

Find out a USB which has at least 2GB size to store the image, and be sure to format it with a apple format. 

After that, convert a ISO image into the apple specific one `.dmg` by using the following command:

```bash
hdiutil convert ./ubuntu.iso -format UDRW -o ./ubuntu.dmg
```

Then, mount your USB and check the serial number:

```bash
diskutil list

# may be /dev/diskN, in which N should be 0, 1 or any integer
```

And, unmount the USB before recording:

```bash
diskutil unmountDisk /dev/diskN
```

Recording:

```bash
sudo dd if=./ubuntu.img of=/dev/diskN bs=1m
```

If successfully, you can just eject your USB device:

```bash
diskutil eject /dev/diskN
```

### Clear out sizes and create a empty partition for installation

![](./mac_linux_disk_utility.jpg)

After creating the partition, you can just reboot and hold keying the `optional` key. After a while, some options have been shown to choose. Just remember to choose the EFI one.

![](./mac_linux_boot.jpg)

Then, choose `install Ubuntu`.

### Installer

![](./mac_linux_installer_partitions.jpg)

When choosing where to install, you have to be careful. The option of **Device for boot loader installer should choose `/dev/sda1`**. Besides, you are ought to double click the partion you have just created like `/dev/sda4` and change it with a EXT4 format, and set the mount point as `/`.

### EFI Boot Fix

When the installer completes, **don't restart just yet**! We still need to do one more thing so that we'll be able to use GRUB. Run the following command: 

```bash
sudo apt-get update
sudo apt-get install efibootmgr
```

This will temporarily install a configuration tool for EFI boot setups.

Next, run

```bash
sudo efibootmgr
```

This will print out the current boot configuration to your screen. In this, you should be able to see "ubuntu" and "Boot0000\*". Currently, the EFI system will point to "Boot0080\*", which skips GRUB and goes directly to Mac OS.

To fix this, run the command

```bash
sudo efibootmgr -o 0,80
```

### Fix Mac OS Boot

First, you'll need to make a quick change to a GRUB setting so that the SSD won't occasionally freeze. 

```bash
# before using vim, you have to install it by `sudo apt-get install vim`
sudo vim /etc/default/grub
```

Find `GRUB_CMDLINE_LINUX` and change it:

```
GRUB_CMDLINE_LINUX="libata.force=noncq"
```

Then edit `/etc/grub.d/40_custom` and add the following content right behind the file:

```
menuentry "Mac OS X" {
exit
}
```

After that, use the following command to take your configuration into effect.

```bash
sudo update-grub
```
