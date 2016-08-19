## [轉載] Beat Detection Using JavaScript and the Web Audio API [Back](./../post.md)

> - Author: [Joe Sullivan](https://twitter.com/itsjoesullivan)
- Origin: http://joesul.li/van/beat-detection-using-web-audio/

By [Joe Sullivan](https://twitter.com/itsjoesullivan)

This article explores using the [Web Audio API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API) and JavaScript to accomplish beat detection in the browser. Let’s define beat detection as determining (1) the location of significant drum hits within a song in order to (2) establish a tempo, in beats per minute (BPM).

If you’re not familiar with using the WebAudio API and creating buffers, [this tutorial will get you up to speed](http://www.html5rocks.com/en/tutorials/webaudio/intro/). We’ll use [Go](http://www.beatport.com/release/go/1338457) from [Grimes](http://www.beatport.com/artist/grimes/173967) as our sample track for the examples below.

