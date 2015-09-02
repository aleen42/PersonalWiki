## ffmpeg	[Back](./../summary.md)

### Install

##### Ubuntu 14.04 LTS 

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libbluray --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3`

##### Ubuntu 12.04 LTS

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libbluray --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3`

- `make`
- `make install`

### Command

- ffmpeg -f concat -i Mic.txt -c copy Mic.wav
- ffmpeg -i Mic_video.mp4 -i mic.wav -filter_complex amix=inputs=2:duration=first:dropout_transition=2 dsgl_new.mp4

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
