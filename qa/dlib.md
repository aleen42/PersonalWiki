## How to setup Dlib in the Visual Studio 2013 [Back](./qa.md)

### Introduction

- According to the offical [**document**](http://dlib.net/), we will know that Dlib is a modern C++ toolkit containing **machine learning algorithms** and tools for creating complex software in C++ to solve real world problems. It is open source software and licensed under the Boost Software License.
- Examples of Dlib:
	- 3D Point Cloud
	- Face Detection
	- ...

- With the reason that the [**document**] about how to compile is too old to use for the Visual Studio 2013, here I have written a document to describe how can we setup Dlib in the version 2013 without CMake.

### Proccess

- Version: Visual Studio 2013 (with update 4)
- The most important things to do before the follow steps is to get your **Visual Studio 2013**

##### 1. Properties

- In this step, you'll need to find out the Property Manager. Here you can see the screen shot of both English Version and Chinese one.
	- en: <img src="./dlib_2.png">
	- zh: <img src="./dlib_1.png">
- And then, you'll see that the manager will appear in your right bars, maybe when it's not for you, you can find it in other bars.
	- en: <img src="./dlib_4.png">
	- zh: <img src="./dlib_3.png">
- Open the project, you'll see two directory named **Debug|Win32** and **Release|Win32**. So in the next step, you should click each with right button of your mouse to **Add New Project Property Sheet**.
	- en: <img src="./dlib_6.png">
	- zh: <img src="./dlib_5.png">



<a href="#" style="left:200px;"><img src="./../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
