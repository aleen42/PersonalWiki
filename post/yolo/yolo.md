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

### How It Works

Prior detection systems repurpose classifiers or localizers to perform detection. They apply the model to an image at multiple locations and scales. High scoring regions of the image are considered detections.

We use a totally different approach. We apply a single neural network to the full image. This network divides the image into regions and predicts bounding boxes and probabilities for each region. These bounding boxes are weighted by the predicted probabilities.

<p align="center"><img src="./model2.png" /></p>

Our model has several advantages over classifier-based systems. It looks at the whole image at test time so its predictions are informed by global context in the image. It also makes predictions with a single network evaluation unlike systems like [R-CNN](https://github.com/rbgirshick/rcnn) which require thousands for a single image. This makes it extremely fast, more than 1000x faster than R-CNN and 100x faster than [Fast R-CNN](https://github.com/rbgirshick/fast-rcnn). See our [paper](http://arxiv.org/abs/1506.02640) for more details on the full system.

#### What's New in Version 2?

YOLOv2 uses a few tricks to improve training and increase performance. Like Overfeat and SSD we use a fully-convolutional model, but we still train on whole images, not hard negatives. Like Faster R-CNN we adjust priors on bounding boxes instead of predicting the width and height outright. However, we still predict the `x` and `y` coordinates directly. The full details are in our paper soon to be released on Arxiv, stay tuned!