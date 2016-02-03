## Ffmpeg	[Back](./../summary.md)

### 1. Install

#### 1.1 Configure


##### Ubuntu 14.04 LTS 

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3`

##### Ubuntu 12.04 LTS

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3`

- *Note: `--enable-libbluray` will cause problems when building opencv*
- *Note: if you found that the libraries have not been installed, you can use `apt-get install` to install the related libraries. (always you can use `tab` key to find the `dev` edition to install)*

#### 1.2 Make

- `make`

#### 1.3 Make Install

- `make install`

### 2. Command of generating codes

#### 2.1 Concat

##### 2.1.1 Convert .mp4 to .ts 

`ffmpeg -y -i input.mp4 -vcodec copy -acodec copy -vbsf h264_mp4toannexb output.ts`

##### 2.1.2 Concat two videos

`ffmpeg -y -i "concat:input1.ts|input2.ts" -acodec copy -vcodec copy -absf aac_adtstoasc output.mp4`

##### 2.1.3 Concat sounds with a .txt file

`ffmpeg -y -f concat -i input.txt -c copy output.wav`

##### 2.1.4 Problem

- Problem: Different resolution ratio(分辨率) of two videos will result in distortion(失真) of images and sounds.
- Solution: Change the resolution ratio of two videos.
	- `ffmpeg -y -i input.mp4 -s 1280x720 -ar 44100 -strict -2 output.mp4`

#### 2.2 Synthesis(合成)

##### 2.2.1 Sampling sounds to 44100Hz

`ffmpeg -y -i input.mp4 -ar 44100 -strict -2 output.mp4`

##### 2.2.2 Synthesize the video with sounds

`ffmpeg -y -i input.mp4 -i input.wav -filter_complex amix=inputs=2:duration=first:dropout_transition=2 -ar 44100 -strict -2 output.mp4` 

##### 2.2.3 Problem

- Problem: Sampling will result in distortion of images when not enable **libx264**.
- Solution: Configure the ffmpeg again, and enable libx264.

### 3. Usage

#### 3.1 crop a video

`ffmpeg -i input.mp4 "crop=w:h:x:y" output.mp4`

- **w**: width
- **h**: height
- **x, y**: crop from the start point (x, y)

#### 3.2 cut a video

`ffmpeg -ss [start] -i intput.mp4 -t [duration] -c:v copy -c:a copy output.mp4`

- **-ss**: to specify the start time
- **-t**: to specify the duration
- **-c:v copy** and **-c:a copy**: to copy the video and audio stream without any re-encoding actions.

#### 3.3 change frame rate

- firstly, what you should do is to export all the frames of the videos with it's origin rate:

`ffmpeg -i input.mp4 -r "[origin-rate]" "frame/f_%1d.png`

- the next step to do is to generate a new video with all the frames:

`ffmpeg -r "[new-rate]" "frame/f_%1d.png" output.mp4` 

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
