## ffmpeg	[Back](./../summary.md)

### Install



### Command

- ffmpeg -f concat -i Mic.txt -c copy Mic.wav
- ffmpeg -i Mic_video.mp4 -i mic.wav -filter_complex amix=inputs=2:duration=first:dropout_transition=2 dsgl_new.mp4

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
