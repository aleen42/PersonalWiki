## [轉載] YOLO: Real-Time Object Detection ( C++ / Python ) [Back](./../post.md)

> - Author: [pjreddie](https://github.com/pjreddie)
- Origin: http://pjreddie.com/darknet/yolo/

You only look once (YOLO) is a state-of-the-art, real-time object detection system. On a Titan X it processes images at 40-90 FPS and has a mAP on VOC 2007 of 78.6% and a mAP of 44.0% on COCO test-dev.

<iframe width="100%" height="415" src="https://www.youtube.com/embed/VOC3huqHrss" frameborder="0" allowfullscreen=""></iframe>


Model|Train|Test|mAP|FLOPS|FPS|Cfg|Weights
:----|----:|---:|--:|----:|--:|--:|------:
Old YOLO|VOC 2007+2012|2007|63.4|40.19 Bn|45||link
SSD300|VOC 2007+2012|2007|74.3|-|46||link
SSD500|VOC 2007+2012|2007|76.8|-|19||link
YOLOv2|VOC 2007+2012|2007|76.8|34.90 Bn|67|cfg|weights
YOLOv2 544x544|VOC 2007+2012|2007|78.6|59.68 Bn|40|cfg|weights
Tiny YOLO|VOC 2007+2012|2007|57.1|6.97 Bn|207|cfg|weights
SSD300|COCO trainval|test-dev|41.2|-|46||link
SSD500|COCO trainval|test-dev|46.5|-|19||link
YOLOv2 544x544|COCO trainval|test-dev|44.0|59.68 Bn|40|cfg|weights
Tiny YOLO|COCO trainval|-|-|7.07 Bn|200|cfg|weights