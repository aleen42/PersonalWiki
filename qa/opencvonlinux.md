## How to build up Opencv in Linux [Back](./qa.md)

- **Ubuntu 14.04** + **OpenCV 3.1.0**

#### 1. be sure to install cmake

`sudo apt-get install cmake`

#### 2. download and extract opencv

`wget -O opencv-3.1.0.zip https://github.com/Itseez/opencv/archive/3.1.0.zip`

`upzip opencv-3.1.0.zip`

#### 3. build

##### 3.1 create a build directory

`mkdir build && cd build`

##### 3.2 use cmake to build (without Ffmpeg)

`cmake -D WITH_FFMPEG=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..`

- Problem: **qmake: could not exec '/usr/lib/i386-linux-gnu/qt4/bin/qmake': No such file or directory**
- Solution: install the `qt` dependence (`sudo apt-get install qt4-qmake libqt4-dev`)

##### 3.3 make

`sudo make -j2`

- *Note: this will take some time to complete. *
- Problem: **some lib*.so have undefined link to reference LibXML2**
- Solution: you should check the lib when installing ffmpeg.

##### 3.4 make install

`sudo make install`

#### 4. Configure

`sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'`

`sudo ldconfig`

#### 5. Reboot the computer

#### 6. Create a project and run it

##### 6.1 Create CMakeLists.txt

`vim CMakeLists.txt`
```
cmake_minimum_required(VERSION 2.8)
project( [projectName] )
find_package( OpenCV REQUIRED )
add_executable( [projectName] [projectName].cpp )
target_link_libraries( [projectName] ${OpenCV_LIBS} )
```

##### 6.2 Run the project

`cmake .`

`make`

`./[projectName]`

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
