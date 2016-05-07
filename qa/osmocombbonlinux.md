## How to build up osmocomBB in Ubuntu [Back](./qa.md)

#### 1. install dependencies

```bash
aptitude install libtool shtool autoconf git-core pkg-config make gcc
```

### 2. download GnuARM ToolChain

x86:

[**download**](https://github.com/aleen42/software-packages/blob/master/bu-2.15_gcc-3.4.3-c-c++-java_nl-1.12.0_gi-6.1.tar.bz2?raw=true)

```bash
wget http://gnuarm.com/bu-2.15_gcc-3.4.3-c-c++-java_nl-1.12.0_gi-6.1.tar.bz2
tar xf bu-2.15_gcc-3.4.3-c-c++-java_nl-1.12.0_gi-6.1.tar.bz2
mv gnuarm-* ~/gnuarm
```

x64:

[**download**](https://github.com/aleen42/software-packages/blob/master/bu-2.16.1_gcc-4.0.2-c-c++_nl-1.14.0_gi-6.4_x86-64.tar.bz2?raw=true)

```bash
wget http://www.gnuarm.com/bu-2.16.1_gcc-4.0.2-c-c++_nl-1.14.0_gi-6.4_x86-64.tar.bz2
tar xf bu-2.16.1_gcc-4.0.2-c-c++_nl-1.14.0_gi-6.4_x86-64.tar.bz2
mv gnuarm-* ~/gnuarm
```

*Notice that: download the specified file according to your machine type, or it will occur a problem like the follow one:*

```
~/osmocom-bb/src/target/firmware/include/asm/swab.h: Assembler messages:
~/osmocom-bb/src/target/firmware/include/asm/swab.h:32: Error: no such instruction: `eor %edx,%ecx,%ecx,ror
make[4]: *** [gsmtap_util.lo] Error 1
make[4]: Leaving directory `/root/osmocom-bb/src/shared/libosmocore/build-target/src'
make[3]: *** [all] Error 2
make[3]: Leaving directory `/root/osmocom-bb/src/shared/libosmocore/build-target/src'
make[2]: *** [all-recursive] Error 1
make[2]: Leaving directory `/root/osmocom-bb/src/shared/libosmocore/build-target'
make[1]: *** [all] Error 2
make[1]: Leaving directory `/root/osmocom-bb/src/shared/libosmocore/build-target'
make: *** [shared/libosmocore/build-target/src/.libs/libosmocore.a] Error 2
```

### 3. configure environmental parameters

```bash
export PATH=~/gnuarm/bin:$PATH
```

### 4. install libosmocore

```bash
git clone https://github.com/osmocom/libosmocore.git && cd libosmocore/
autoreconf -i
./configure
make
make install
cd ..
ldconfig
```

### 5. compile osmocom-bb

```bash
git clone https://github.com/osmocom/osmocom-bb.git && cd osmocom-bb
git pull --rebase
cd src
make
```