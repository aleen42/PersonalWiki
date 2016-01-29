## ffmpeg	[Back](./../summary.md)

<img src="./logo.png">

### 1. Install

- System version: **Ubuntu 14.04**
- Update local package

```sh
sudo apt-get upgrade
```

- Install the software

```sh
sudo apt-get install imagemagick
```

### 2. Usage

#### 2.1 generate perspective image

- to generate images from 4 differents points(A, B, C, D)

```sh
convert input.png -matte -virtual-pixel transparent\
-distort Perspective\
'from[A].x, from[A] to[A].x, to[B].y'
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
