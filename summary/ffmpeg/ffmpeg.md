## Ffmpeg	[Back](./../summary.md)

### 1. Install

#### 1.1 Configure


##### Ubuntu 14.04 LTS 

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3`

##### Ubuntu 12.04

- `./configure --extra-version=tessus --enable-avisynth --enable-fontconfig --enable-gpl --enable-libass --enable-libfreetype --enable-libgsm --enable-libmodplug --enable-libmp3lame --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libschroedinger  --enable-libsoxr --enable-libspeex --enable-libtheora --enable-libvo-aacenc --enable-libvo-amrwbenc --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libx264 --enable-version3 --enable-pic --enable-shared`

- *Note: `--enable-libbluray` will cause problems when building opencv*
- *Note: if you found that the libraries have not been installed, you can use `apt-get install` to install the related libraries. (always you can use `tab` key to find the `dev` edition to install)*
- *Note: libsoxr cannot be installed by apt-get in Ubuntu 12.04, so you should download three package and install them by ordered*
    1. [libsoxr0](http://www.ubuntuupdates.org/package/webupd8/precise/main/base/libsoxr0)
    2. [libsoxr-lsr0](http://www.ubuntuupdates.org/package/webupd8/precise/main/base/libsoxr-lsr0)
    3. [libsoxr-dev](http://www.ubuntuupdates.org/package/webupd8/precise/main/base/libsoxr-dev)
- *Note: in Ubuntu 12.04, you should recompile libx264 and ffmpeg with `--enable-pic` and `--enable-shared`.(Be sure that you have completely uninstall ffmpeg before recompile libx264, more [details](http://www.ozbotz.org/opencv-installation/) in step 7 and 8)*.
- *Remember to type `make distclean` before you configure again*.
- Problem: **ffmpeg: error while loading shared libraries: libavdevice.so.55: cannot open shared object file: No such file or directory**.
- Solution:

```bash
# vim /etc/ld.so.conf and add this line
/usr/local/ffmpeg/lib

# then type ldconfig to load config
```

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

##### 2.2.4 Combine audio and video

`ffmpeg -y -i audio.mp3 -i input.mp4 -c:v copy -absf aac_adtstoasc -b 192k output.mp4`

### 3. Usage

#### 3.1 crop a video

`ffmpeg -i input.mp4 -filter:v "crop=w:h:x:y" -pix_fmt yuv420p output.mp4`

- **w**: width
- **h**: height
- **x, y**: crop from the start point (x, y)

#### 3.2 cut a video

`ffmpeg -ss [start] -i intput.mp4 -t [duration] -c:v copy -c:a copy output.mp4`

- **-ss**: to specify the start time (*Notice that the position of -ss will cause problem of durations of the video)*
- **-t**: to specify the duration
- **-c:v copy** and **-c:a copy**: to copy the video and audio stream without any re-encoding actions.

#### 3.3 change frame rate

- firstly, what you should do is to export all the frames of the videos with it's origin rate:

`ffmpeg -r "[origin-rate]" -i input.mp4 "frame/f_%1d.png"`

- the next step to do is to generate a new video with all the frames:

`ffmpeg -r "[new-rate]" -i "frame/f_%1d.png" -start_number 1 -vcodec "libx264" -crf "0" -pix_fmt yuv420p output.mp4` 

- *Notice: without **-pix_fmt yuv420p**, the video codec is not supported for iOS, Safari, and so on.*

#### 3.4 extract a specific frame

`ffmpeg -ss [time] -i input.mp4 -vframes 1 output.jpg`

#### 3.5 admix two audio, and put one audio in the specifc time

**i.** create a blank video of the longest time:

`ffmpeg -f lavfi -i anullsrc=r=44100:cl=mono -t <seconds> -q:a 9 -acodec libmp3lame <blank audio>`

**ii.** add the clip audio(the shorter one) to the blank audio in a specific time.

`ffmpeg -i <blank audio> -i <shorter audio file> -filter_complex "aevalsrc=0:d= <time> [s1];[s1][1:a]concat=n=2:v=0:a=1[aout]" -c:v copy -map [aout] <reserved file>`

**iii.** combine with the origin audio file:

`ffmpeg -i <resreved file> -i <original longer audio file> -filter_complex "amix=inputs=2:duration=longest:dropout_transition=2, volume=2" <output audio file>`

#### 3.6 sample audio stream with slow down filter

`ffmpeg -i input.mp4 -vn -ar 44100 -ac 2 -ab 192k -f mp3 -filter:a "atempo=0.5" sample.mp3`

- atempo: it's used to slow down/speed up an audio file, which should be between **0.5~2**.

#### 3.7 get video bitrate

`ffprobe -v error -select_streams v:0 -show_entries stream=bit_rate -of default=noprint_wrappers=1:nokey=1 input.mp4 `

#### 3.8 convert a video into a gif format picture

generate a palette with output width 320 pixels:

`ffmpeg -i input.mp4 -vf fps=10,scale=320:-1:flags=lanczos,palettegen palette.png`

output a gif with the palette:

`ffmpeg -i input.mp4 -i palette.png -filter_complex "fps=10,scale=320:-1:flags=lanczos[x];[x][1:v]paletteuse" output.gif`

