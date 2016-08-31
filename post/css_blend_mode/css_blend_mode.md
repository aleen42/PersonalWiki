## [轉載] CSS Blend Modes could be the next big thing in Web Design [Back](./../post.md)

> - Author: [Bennett Feely](https://medium.com/@bennettfeely)
- Origin: https://medium.com/@bennettfeely/css-blend-modes-could-be-the-next-big-thing-in-web-design-6b51bf53743a#.cmprev5a6
- Time: Dec, 22nd, 2013

### Coming to a browser near you.

For everyone who has ever opened Photoshop or Illustrator you are most likely familiar with blend modes. Multiply, screen, overlay, and soft light, to name a few can turn boring opaque layers into beautiful pieces of stained glass. However, what awesome “blend modes” do web designers have at their disposal for making websites beautiful? Opacity. Yep, that’s it.

![](./1.png)

> Cool-looking things that are difficult or downright impossible to replicate in CSS right now. Top row: Doublenaut, Graham Hicks, Jonathan Quintin, and Geoff Teehan. Bottom row: Ben Johnson, Claire Morales, Alan Defibaugh, and Jess Barlow.

### Blend modes and the web

It’s a shame that we couldn’t have had more blend modes to work with when the opacity property gained widespread support across browsers, but it turns out that ensuring Photoshop-like blend modes render uniformly across different browsers and implementations is [no easy task](http://dbaron.org/log/20130306-compositing-blending). Some blend modes have been available in SVG through filters, but these are limited and don’t see much use in the real world.

Despite this, things are changing fast and there is a candidate recommendation titled [CSS Compositing and Blending](http://dev.w3.org/fxtf/compositing-1/). Blend modes in CSS have been promoted heavily by Adobe Web Platform team (along with other interesting features like CSS filters and masking).
