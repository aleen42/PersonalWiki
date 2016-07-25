## [轉載] Face Swap using OpenCV ( C++ / Python ) [Back](./../post.md)

> - Author: [SATYA MALLICK](http://www.learnopencv.com/about/)
- Origin: http://www.learnopencv.com/face-swap-using-opencv-c-python/
- Time: Apr, 5th, 2016

![](./1.jpg)

**Figure 1 : Face Swapped Presidential Candidates**

In this tutorial we will learn how to swap out a face in one image with a completely different face using OpenCV and DLib in C++ and Python.

> To understand the description below better, [download](http://www.learnopencv.com/face-swap-using-opencv-c-python/#download) the C++ and Python code and images by subscribing to our newsletter [here](http://www.learnopencv.com/face-swap-using-opencv-c-python/#download).

Ladies and gentlemen, let me present Ted Trump, Donald Clinton and Hillary Cruz. Do you like any of them ? Me neither! I know, I know, I know, the above images are pretty disturbing, but so are the original choices of presidential candidates. It is a race among clowns, so let’s have some fun at their expense.

This post builds on previous posts on Facial Landmark Detection, Delaunay Triangulation, Face Morphing and Seamless Cloning.

### Why is Face-Swap difficult ?

The human brain treats human faces as a special category and has specialized machinery to process faces. We are very good at analyzing faces and can easily detect a fake face. It is easy to computationally replace a face in one image with a different face if you want to do it for giggles, but extremely difficult to do if you want to do it completely automatically at a quality that will fool people consistently. After all, we are trying to fool one of the most advanced cognitive machinery in the human brain.

Consider the images of top three presidential candidates in Figure 2.

![](./2.jpg)

**Figure 2 : Original Image of Presidential Candidates**

The three images are pretty different. Yes, Donald Trump is very ugly, but that is not what I mean.

First, the facial geometry of regular human beings like Secretary Hillary Clinton and Senator Ted Cruz varies quite a bit. Add Donald Trump to the mix, and you now have to deal with outliers that lie on the intersection of homo sapiens and some unknown primate with funny hair.

Second, the lighting on the face combined with the tone of the skin can make the images look very different. E.g. Secretary Hillary Clinton’s image looks yellow, while Senator Ted Cruz’s image looks red, and Donald Trump continues to look ugly.

Third, the pose of the face ( or camera angle if you will ) can vary significantly.

And finally, the texture of the skin can vary from smooth to almost leathery ( i.e. Clinton to Trump ).

The technique proposed in this post will address the first two problems but not the last two.

### FaceSwap : Step by Step using OpenCV

1. **Face Alignment** : To replace one face with another, we first need place one face approximately on top of the other so that it covers the face below. An example is shown in Figure 3.