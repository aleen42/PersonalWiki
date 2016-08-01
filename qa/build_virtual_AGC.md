## Some problems of building Virtual AGC [Back](./qa.md)

**Virtual AGC (Apollo Guidance Computer)** is used for simulating the real AGC, the DSKY of the real Apollo Guidance System. For personal interest, I have decided to build this [project](https://github.com/rburkey2005/virtualagc) and know more about Apollo's plan. Here, I will write down some problems of the process with a documenting way.

Here, I just use a **Ubuntu 14.04** to build:

1. Download a development tarball firstly:
    https://www.ibiblio.org/apollo/Downloads/

    Here I would like to build with [**yaAGC-dev-20100220.tar.bz2**](https://www.ibiblio.org/apollo/Downloads/yaAGC-dev-20100220.tar.bz2)
2. Then, the following step should be unpacking:
    {%ace edit=false, lang='sh' %}
    $ tar --bzip2 -xf yaAGC-dev-YYYYMMDD.tar.bz2
    {%endace%}
3. After, building the project with enter the directory, `yaAGC`:
    {%ace edit=false, lang='sh' %}
$ cd yaAGC
$ make
    {%endace%}
    *Notice that, you should not run `configure` and `make install`*

    - Problems: **/usr/bin/ld: cannot find -lcurses**
    - Solutions: 
    {%ace edit=false, lang='sh' %}
    $ sudo apt-get install libcurses-ocaml-dev
    {%endace%}
    
    - Problems: **fatal error: wx/wx.h: No such file or directory**
    - Solutions:
    {%ace edit=false, lang='sh' %}
    $ sudo apt-get install libwxgtk3.0-dev
    {%endace%}
    
4. To match the default setup:
    {%ace edit=false, lang='sh' %}
    $ mv yaAGC/VirtualAGC/temp/lVirtualAGC ~/VirtualAGC
    {%endace%}
5. After installation, we can run it by executing files of `~/VirtualAGC/bin`

{%ace edit=false, lang='sh' %}
$ ~/VirtualAGC/bin/VirtualAGC
{%endace%}

![](./virtualAGC.png)

    