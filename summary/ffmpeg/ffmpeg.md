## ffmpeg	[Back](./../summary.md)

### 1. Install

#### 1.1 Configure

##### Ubuntu 14.04 LTS 

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libbluray --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3`

##### Ubuntu 12.04 LTS

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libbluray --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3`

#### 1.2 Make

- `make`

#### 1.3 Make Install

- `make install`

### 2. Command of generating codes

#### 2.1 Concat

##### 2.1.1 Convert .mp4 to .ts 

- `ffmpeg -i input.mp4 -vcodec copy -acodec copy -vbsf h264_mp4toannexb output.ts`

##### 2.1.2 Concat

- `ffmpeg -i "concat:input1.ts|input2.ts" -acodec copy -vcodec copy -absf aac_adtstoasc output.mp4`

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
