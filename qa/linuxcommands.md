## Some commands of Linux [Back](./qa.md)

#### 1. If you want to checkout the version of Linux

```bash
lsb_release -a
```

#### 2. If you want to see the space size

```bash
# checkout the hard disk
df -h
# checkout the current directory
du -h --max-depth=1
```

#### 3. If you want to check the info of the space size in the physical memory

```bash
# Total Mem
free | sed -n "2, 1p" | awk '{print int($2)}'
# Used
free | sed -n "3, 1p" | awk '{print int($3)}'
```

#### 4. Dynamically check a file

```bash
tail -f file
```

#### 5. Check device ID of some USB ports

```bash
lsusb
```

#### 6. To connect some port of a specified IP address

```bash
telnet <IP addr> <port>
```
