## Graduation Thesis(畢業論文)	[Back](./../summary.md)

> - Title: **Dynamical Content Injection of videos**(視頻動態植入內容)
- Tools: OpenCV, [Ffmpeg](./../ffmpeg/ffmpeg.md), [Imagemagick](./../imagemagick/imagemagick.md)
- Translation: [works](./../../translation/translation.md)

#### Progress

1. For **entities whose corners are easy to track** like quadrangles, we're going to use  LucasKanade Optical Flow Tracking to complete injection.
	-  the first thing to do is to use **Feature Detection** to detect strong corners in the first frame of the video.
	- then we can find out four corners of those entities to choose
	- after chosing 4 points, we will continue to track these points in the videos, and output positions of these 4 points in the following frames.
	- with data of those points, we can present an other layer of image above the video with CSS in HTML.

2. For **entities whose have not any corners**, there are some problems to solute (we are going to detect the motion of the camera.)
	- how to detect whether the image of the video has changed suddenly
		- Solution: use a feature point to track and monitoring the distance between the prev frame and the next frame. When the distance is more than **a specific value**.
	- how to judge whether the camera is static.
		- Testing: tracking all the points and find out two points which has not moved too much, then we will consider it to be static.
	- how to calculate the shift of **x-axis** and **y-axis**
	- how to calculate the shift of **z-axis**

3. Reverse tracking for calculating the upper edge frame:
    - there are some problems about OpenCV, because it cannot jump to a specific frame correctly, and tracking in reverse order should use `VideoCapture::set(CV_CAP_PROP_POS_FRAMES, n)` to reset.
4. Face replacement
    - real time problem
    - image size problem

#### Problems

1. the func `VideoCapture::set(CV_CAP_PROP_POS_FRAMES, n)` will lose a little precision in different systems, due to its **computions of float type**.
	- Solution: use `while` to read from the start, but it will cause severe problem of efficiency.

2. how to generate rebuild video with an overlay image.
	- Solution: 
		- **i.** Calc data with video and tracking points(**video_width**, **video_height**, **4 points**, **area_width**, **area_height**)
		- **ii.** Contract all the frames with ffmpeg

		```bash
		ffmpeg -i input.mp4 -r "[video-rate]" "frame/f_%1d.png"
		```

		- **iii.** Start to combine two image
			- Get the image size with Imagemagick (**logo_width**, **logo_height**):

			```bash
			identify -format "{\"width\": %[fx:w], \"height\": %[fx:h]}" overlay.png
			# or 
			identify -format "{\"width\": %w, \"height\": %h}" overlay.png
			```			

			- Add padding to an image with Imagemagick:
				- area_width > area_height:
					- overlay_pad_width = logo_height * 2 * (area_width / area_height)
					- overlay_pad_height = logo_height * 2
				- area_width <= area_height:
					- overlay_pad_width = logo_width * 2
					- overlay_pad_height = logo_width * 2 * (area_height / area_width)

				```bash
				convert "overlay.png" -background transparent -gravity center -extent "[overlay_pad_width]x[overlay_pad_height]" overlay_pad.png
				```

			- Change the image's size to the size of video and change perspective and it depends:
				- the image is smaller than the video:
					- add padding:
						
					```bash
					convert "overlay_pad.png" -background transparent -extent "[video_width]x[video_height]" mask.png
					```

					- perspective:
			
					```bash
					convert "mask.png" -matte -mattecolor transparent -virtual-pixel transparent\
					-distort Perspective\
					'0,0 point[0].x,point[0].y\
					 0,overlay_pad_height point[1].x,point[1].y\
					 overlay_pad_width,0 point[2].x,point[2].y\
					 overlay_pad_width,overlay_pad_height point[3].x,point[3].y' output.png
					```

				- the image is larger than the video:
					- crop without changing the ratio:

					```bash
					convert "overlay_pad.png" -resize "[video_width]x[video_height]" resize.png
					convert "resize.png" -background transparent -extent "[video_width]x[video_height]" mask.png
					```

					- get size of `resize.png` (**resize_width**, **resize_height**)
					
					```bash
					identify -format "{\"width\": %[fx:w], \"height\": %[fx:h]}" resize.png
					# or 
			        identify -format "{\"width\": %w, \"height\": %h}" resize.png
					```
			
					- perspective:
					
					```bash
					convert "mask.png" -matte -mattecolor transparent -virtual-pixel transparent\
					-distort Perspective\
					'0,0 point[0].x,point[0].y\
					 0,resize_height point[1].x,point[1].y\
					 resize_width,0 point[2].x,point[2].y\
					 resize_width,resize_height point[3].x,point[3].y' output.png
					```

3. put text to image
	- Solution: 
		
	```bash
	convert \
   	    -size 165x70 \
	    xc:lightblue \
		-font Bookman-DemiItalic \
		-pointsize 12 \
		-fill blue \
		-gravity center \
		-draw "text 0,0 '$(cat file.txt)'" \
		image.png
	```

4. handle real time live stream
    - Solution:
        1. read camera from a network stream

        ```cpp
        VideoCapture cam;
        
        ```

#### Performance

###### Handle Frames

video size|video length|handled frames number|result time
:--------:|:----------:|:-------------------:|:---------:
1920x1080|79s|47|10564ms
1920x1080|79s|394|1587437ms