## ImageMagick	[Back](./../summary.md)

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
'from[A].x, from[A].y to[A].x, to[A].y\
 from[B].x, from[B].y to[B].x, to[B].y\
 from[C].x, from[C].y to[C].x, to[C].y\
 from[D].x, from[D].y to[D].x, to[D].y' output.png
```

- example:

<img src="./examp1.png">
