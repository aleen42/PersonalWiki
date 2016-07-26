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
Works with OpenCV : You can interface with OpenCV using MATLAB’s OpenCV Interface.
Great documentation : Even staunch supporters of OpenCV admit that its documentation sucks. In contrast, MATLAB comes with great documentation and examples that are easily accessible within the IDE. Great documentation alone can make coding in MATLAB 2x faster than using OpenCV. MATLAB functions are also better designed compared to OpenCV. E.g. compare this simple code for displaying an image in OpenCV and MATLAB.
