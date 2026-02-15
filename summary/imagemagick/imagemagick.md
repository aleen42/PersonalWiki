## Imagemagick	[Back](./../summary.md)

<img src="./logo.jpg">

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
'from[A].x, from[A] to[A].x, to[B].y\
 from[B].x, from[B] to[B].x, to[B].y\
 from[C].x, from[C] to[C].x, to[C].y\
 from[D].x, from[D] to[D].x, to[D].y' output.png
```

- example: <img src="./examp1.png">

#### 2.2 create a complete transparent image

```sh
convert -size "[w]x[h]" xc:"rgba(0,0,0,0)" PNG32:output.png
```

#### 2.3 add padding to a png file

```sh
convert "input.png" -background transparent -gravity center -extent "[w]x[h]" output.png
```

#### 2.4 get width and heigh of an image

```sh
identify -format "{\"width\": %[fx:w], \"height\": %[fx:h]}" input.png
```

#### 2.5 genereate image with text

```sh
convert -size [width]x[height]\
    -font "msyh.ttf"\
    -pointsize 16\
    -fill "#000000"\
    -background transparent\
    -gravity center\
    caption:"这是一串字符串" text.png
```
