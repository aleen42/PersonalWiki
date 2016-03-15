## How to compile Dlib(C++) on Linux [Back](./qa.md)

1. the first step is to download `.zip` files of Dlib [here(dlib 18.18)](https://github.com/aleen42/PersonalWiki/raw/master/qa/dlib-18.18.zip).
2. unzip the file you downloaded just now and place it wherever you want, which is a new `lib` in the same directory of the cpp source for me.
> - detectFace
>> - lib
>>> - dlib
>> - detectFace.cpp
>> - CMakeLists.txt
3. then you can create your `CMakeLists.txt`

```txt
#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#

cmake_minimum_required(VERSION 2.8.4)

PROJECT(detectFace)

include(./lib/dlib/dlib/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
find_package(OpenCV)
if (OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})

	ADD_EXECUTABLE(detectFace detectFace.cpp)
	TARGET_LINK_LIBRARIES(detectFace dlib ${OpenCV_LIBS} )
else ()
	# Tell CMake to compile a program.  We do this with the ADD_EXECUTABLE()
	# statement which takes the name of the output executable and then a list of
	# .cpp files to compile.  Here each example consists of only one .cpp file but
	# in general you will make programs that const of many .cpp files.
	ADD_EXECUTABLE(detectFace detectFace.cpp)
	# Then we tell it to link with dlib.
	TARGET_LINK_LIBRARIES(detectFace dlib)
endif ()

if (DLIB_LINK_WITH_SQLITE3)
	add_example(sqlite_ex)
endif ()

```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
