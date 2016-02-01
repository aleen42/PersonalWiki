## How to build up Opencv in Linux [Back](./qa.md)

#### 1. be sure to install cmake

`sudo apt-get install cmake`

#### 2. download and extract opencv

`wget -O opencv-3.1.0.zip https://github.com/Itseez/opencv/archive/3.1.0.zip`

`upzip opencv-3.1.0.zip`

#### 3. build

##### 3.1 create a build directory

`mkdir build && cd build`

##### 3.2 use cmake to build

`cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..`

- Problem: **qmake: could not exec '/usr/lib/i386-linux-gnu/qt4/bin/qmake': No such file or directory**
- Solution: install the `qt` dependence (`sudo apt-get install qt4-qmake libqt4-dev)

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
