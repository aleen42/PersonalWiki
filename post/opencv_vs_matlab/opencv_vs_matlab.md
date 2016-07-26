## [轉載] OpenCV (C++ vs Python) vs MATLAB for Computer Vision [Back](./../post.md)

> - Author: [SATYA MALLICK](http://www.learnopencv.com/about/)
- Origin: http://www.learnopencv.com/opencv-c-vs-python-vs-matlab-for-computer-vision/
- Time: Oct, 30th, 2015

![](./1.jpg)

We often confuse our tools for our craft. Tools help you practice your craft, but they do not make you a good craftsman. A good craftsman has many different tools in her pocket, and she judiciously uses the one that is appropriate for the job. She is not married to the tools. She is married to her craft.

I am often amused by wars over programming languages. People have very strong opinions about which one is better. The truth is that a programmer should chose the language appropriate for their task. Want to rapidly build a web app ? Try Ruby on Rails or Django. Want to write high performance code for an embedded device. Try C.

In computer vision, we are faced with similar choices. Which tool should a computer vision engineer / programmer learn — OpenCV using C++, OpenCV using Python, or MATLAB ? The good news is that today we have a few options to choose from! A decade back there were no good libraries for computer vision. If you wanted to learn, you just picked up a book and started coding your own mini library of computer vision algorithms. Thankfully, things are much better now.

If you are a beginner, I would suggest using the path of least resistance and picking a tool you are familiar with. If you are a python programmer, use OpenCV with Python. If you know C++, use C++ with OpenCV. The same holds true for MATLAB. That said in a few months you will no longer be a beginner. You may be looking to apply this newly acquired knowledge to the real world. You could be thinking of a new side project, or looking for a new job in this area. It pays ( sometimes literally ) to know how to make your choices. So here are my thoughts.

### MATLAB for Computer Vision

Until recently Computer Vision was a research area in its infancy. People who worked in Computer Vision were mostly in the academia or research labs. Their tool of choice was MATLAB, and for the longest time OpenCV paled in comparison to what MATLAB and its community had to offer. In the last 7 years, the tides have turned. Here are some of the pros of using MATLAB.

#### Why Should You Use MATLAB for Computer Vision : The Pros

1. **Powerful matrix library** : Not only do we treat an image as a multi-dimensional matrix in computer vision, we use a heavy dose of linear algebra in various algorithms. MATLAB’s linear algebra routines are very powerful and blazingly fast ( when used correctly ). Once we needed to solve a large sparse linear system as part of an algorithm. It was a one line code in MATLAB — something like X = A \ b . We were assuming that our C++ implementation will be at least 3x faster than the MATLAB implementation. The first version of our C++ implementation turned out to be slower than the MATLAB version! It took us days to match the performance of the MATLAB routine. So in MATLAB a single operator like backslash ( \ ) is sometimes a collection of powerful algorithms that MATLAB appropriately chooses for you.
2. **Toolboxes** : What ever your needs, there is a toolbox for that. They have an image processing toolbox, a computer vision toolbox, and a statistical and machine learning one that provide implementations of a wide variety of very useful algorithms. The functions usually provide a clean and obvious interface. Many computer vision problems are often set up as optimization problems. You are trying to maximize or minimize some objective functions under certain constraints. The optimization toolbox in MATLAB provides excellent implementations of many optimization algorithms.
3. **Visualization and debugging tools** : One of the joys of using MATLAB is that writing code, visualizing results, and debugging happens in one integrated environment. The environment makes you extremely productive.
4. **Works with OpenCV** : You can interface with OpenCV using MATLAB’s OpenCV Interface.
5. **Great documentation** : Even staunch supporters of OpenCV admit that its documentation sucks. In contrast, MATLAB comes with great documentation and examples that are easily accessible within the IDE. Great documentation alone can make coding in MATLAB 2x faster than using OpenCV. MATLAB functions are also better designed compared to OpenCV. E.g. compare this simple code for displaying an image in OpenCV and MATLAB.

    ```cpp
    // MATLAB
    imshow(im); 
     
    // OpenCV 
    imshow("myWindow", im); 
    ```
Most of the time, I just want to display an image. Call it “Image 1” for God’s sake instead of forcing me to type the window name ( “myWindow” ) over and over again.
6. **Large research community** : As I have mentioned earlier, MATLAB is extremely popular in the academia. Latest research demos are often shared as MATLAB code. If you want to be on the cutting edge, you should be able to read MATLAB code.

#### Why You Should Not MATLAB for Computer Vision : The Cons

1. **Cost is HUGE** : MATLAB is hideously expensive. Let us start with basic MATLAB ($2,150) and throw in the computer vision toolbox ($1,350). But the computer vision toolbox requires the image processing toolbox ($1000). Add optimization ($1,350) and machine learning toolboxes ($1000). That brings your grand total to $6850! Ok, now you have built your application and want to deploy it. Well, you gotta buy the MATLAB compiler ($4,250). Oh you want it for two different operating systems ? That would be another $4,250. MATLAB makes sense if you get it for a discounted price through your University, or your company has a license.
2. **Learning curve** : MATLAB is a matrix engine. There is a MATLAB way to write code which is different from general purpose programming languages like C++ or Python. And if you do not write code the MATLAB way, your code can be extremely slow.
3. **Slower runtime** : A typical MATLAB program runs many times slower than a C++ program. Built-in MATLAB routines can be very fast, but the code you write in MATLAB will usually run much slower. Often times people end up coding computationally intensive parts in C and integrating it with MATLAB code using mex

### OpenCV (C++) for Computer Vision

OpenCV is my primary tool for developing computer vision applications. I have prototyped a lot in MATLAB, but except on one occasion the production version has always been OpenCV based. Let’s look at the pros and cons.

#### Why should you use OpenCV (C++) for Computer Vision : The Pros

1. **It’s free!** : Large parts of OpenCV are free — i.e. free as in beer, and free as in speech! You can use OpenCV freely in your commercial application, and you can view the source and fix issues if needed. You do not have to open source your project if you use OpenCV.
2. **Huge optimized library** : The collection of algorithms available in OpenCV dwarfs everything out there. The library is also optimized for performance. With OpenCV 3, you can use the Transparent API to easily use OpenCL compliant devices (e.g. GPU) on your machine. Many algorithms have a CUDA implementation.
3. **Platforms and devices** : You can obviously use OpenCV in your desktop app or as the backend of your web application. Because of its focus on performance OpenCV (C/C++) is the vision library of choice in many embedded vision applications and mobile apps.
4. **Big community** : There is a big community of developers (47,000 or so) that use and support OpenCV. It has been downloaded more than 9 Million times. Unlike the MATLAB community that consists of researchers, the OpenCV community is a mix of people from many fields and industries. The OpenCV development is funded by companies like Intel, AMD & Google. Needless to say, this blog is part of this vibrant community of people who are trying to help each other.
