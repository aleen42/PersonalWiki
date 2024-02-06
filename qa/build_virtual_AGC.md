## Some problems of building Virtual AGC [Back](./qa.md)

**Virtual AGC (Apollo Guidance Computer)** is used for simulating the real AGC, the DSKY of the real Apollo Guidance System. For personal interest, I have decided to build this [project](https://github.com/rburkey2005/virtualagc) ([another one](https://github.com/aleen42/virtualagc) with translation into traditional chinese), and know more about Apollo's plan. Here, I will write down some problems of the process with a documenting way.

Here, I just use a **Ubuntu 14.04** OS system to build:

1. Download a development tarball firstly:
    https://www.ibiblio.org/apollo/Downloads/

    Here I would like to build with [**yaAGC-dev-20100220.tar.bz2**](https://www.ibiblio.org/apollo/Downloads/yaAGC-dev-20100220.tar.bz2)
2. Then, the following step should be unpacking:
    ```bash
    $ tar --bzip2 -xf yaAGC-dev-YYYYMMDD.tar.bz2
    ```
3. After, building the project with enter the directory, `yaAGC`:
    ```bash
$ cd yaAGC
$ make
    ```
    *Notice that, you should not run `configure` and `make install`*

    - Problems: **/usr/bin/ld: cannot find -lcurses**
    - Solutions: 
    ```bash
    $ sudo apt-get install libcurses-ocaml-dev
    ```
    
    <br />
    
    - Problems: **fatal error: wx/wx.h: No such file or directory**
    - Solutions:
    ```bash
    $ sudo apt-get install libwxgtk3.0-dev
    ```
    
4. To match the default setup:
    ```bash
    $ mv yaAGC/VirtualAGC/temp/lVirtualAGC ~/VirtualAGC
    ```
5. After installation, we can run it by executing files of `~/VirtualAGC/bin`

```bash
$ ~/VirtualAGC/bin/VirtualAGC
```

![](./virtualAGC.png)

    