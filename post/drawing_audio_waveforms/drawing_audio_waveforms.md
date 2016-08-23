## \[轉載\] Drawing Audio Waveforms [Back](./../post.md)

> * Author: [Joe Sullivan](https://twitter.com/itsjoesullivan)
> * Origin: [http:\/\/joesul.li\/van\/beat-detection-using-web-audio\/](http://joesul.li/van/beat-detection-using-web-audio/)

Working on [scat.io](http://scat.io/) I ran into the interesting issue of rendering audio waveforms on-screen. This is a walkthrough of my trial-and-error method of figuring out a good way to accomplish that using d3 and the Web Audio API.

### The data

We receive the audio data in the form of a typed array, like:

```
[ 0, 0.0253245, 0.0452343, ... ]
```

Audio data is that simple. Practically speaking, the values of the array correspond to the position of a speaker. At 44100 frames per second, it hardly sounds digital at all.

So far so good, except for those pesky 44100 frames for every second of audio...

### Boiling it down

So let's pare down this data. We don't reasonably need more data than we can display on the screen. In other words, we only need an array of values with length equal to the number of pixels along the x-axis.

```js
function summarize( data, pixels ) { 
    var pixelLength = Math.round(data.length/pixels);
    var vals = []; // For each pixel we display
    for (var i = 0; i < pixels; i++) {
        var posSum = 0,
            negSum = 0; 

        // Cycle through the data-points relevant to the pixel
        for (var j = 0; j < pixelLength; j++) {
            var val = data[ i * pixelLength + j ]; 
            
            // Keep track of positive and negative values separately
            if (val > 0) { 
                posSum += val;
            } else {
                negSum += val;
            }
        } 
        vals.push( [ negSum / pixelLength, posSum / pixelLength ] );
    }
    return vals;
}
```

Rendering

First I gave it the old college try:

```js
function render1() {
    var multiplier = 100;
    var summary = summarize(data, 100);
    d3.select('#ex1')
        .selectAll('div')
        .data( summary )
        .enter()
        .append('div')
        .style('height', function( pt ) {
            var sum = pt[1] - pt[0];
            return sum * multiplier + 'px';
        });
}
```

Resulting in:

![](./1.png)

Not bad--obviously we're looking at audio data. But it's not symmetrical. Let's center those lines:

```js
function render2() {
    var multiplier = 100;
    var summary = summaraize(data, 200);
    d3.select('#ex1')
        .selectAll('div')
        .data( summary )
        .enter()
        .append('div')
        .style('height', function( pt ) {
            var sum = pt[1];
            return sum * multiplier + 'px';
        })
        .style('margin-top', function( pt ) {
            var sum = pt[1]/2;
            return - sum * multiplier + 'px';
        });
}
```

Result: 

![](./2.png)

