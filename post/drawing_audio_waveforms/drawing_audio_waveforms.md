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

<div id="ex1"><div style="height: 0px;"></div><div style="height: 0px;"></div><div style="height: 0.000420619px;"></div><div style="height: 0.0740704px;"></div><div style="height: 0.139797px;"></div><div style="height: 7.50953px;"></div><div style="height: 30.106px;"></div><div style="height: 40.4945px;"></div><div style="height: 41.2383px;"></div><div style="height: 37.1424px;"></div><div style="height: 32.8074px;"></div><div style="height: 28.4373px;"></div><div style="height: 24.3414px;"></div><div style="height: 20.9676px;"></div><div style="height: 18.3381px;"></div><div style="height: 14.7116px;"></div><div style="height: 12.6193px;"></div><div style="height: 12.2126px;"></div><div style="height: 12.0736px;"></div><div style="height: 11.5085px;"></div><div style="height: 11.4123px;"></div><div style="height: 10.9304px;"></div><div style="height: 29.9476px;"></div><div style="height: 26.2026px;"></div><div style="height: 21.8663px;"></div><div style="height: 21.7706px;"></div><div style="height: 16.2973px;"></div><div style="height: 17.9958px;"></div><div style="height: 15.7707px;"></div><div style="height: 13.3809px;"></div><div style="height: 14.4242px;"></div><div style="height: 15.5889px;"></div><div style="height: 14.295px;"></div><div style="height: 15.2762px;"></div><div style="height: 11.1347px;"></div><div style="height: 12.5599px;"></div><div style="height: 8.14183px;"></div><div style="height: 7.05533px;"></div><div style="height: 16.8074px;"></div><div style="height: 16.0979px;"></div><div style="height: 13.6625px;"></div><div style="height: 13.0838px;"></div><div style="height: 12.345px;"></div><div style="height: 10.6424px;"></div><div style="height: 10.9072px;"></div><div style="height: 10.1431px;"></div><div style="height: 9.47943px;"></div><div style="height: 14.5795px;"></div><div style="height: 12.6627px;"></div><div style="height: 12.08px;"></div><div style="height: 13.5202px;"></div><div style="height: 7.43402px;"></div><div style="height: 5.19667px;"></div><div style="height: 3.78663px;"></div><div style="height: 15.0578px;"></div><div style="height: 40.9275px;"></div><div style="height: 41.9112px;"></div><div style="height: 31.067px;"></div><div style="height: 22.6023px;"></div><div style="height: 17.157px;"></div><div style="height: 13.2091px;"></div><div style="height: 10.0586px;"></div><div style="height: 7.66757px;"></div><div style="height: 7.7734px;"></div><div style="height: 8.04438px;"></div><div style="height: 6.59125px;"></div><div style="height: 5.88086px;"></div><div style="height: 8.07972px;"></div><div style="height: 5.86318px;"></div><div style="height: 7.95553px;"></div><div style="height: 19.0607px;"></div><div style="height: 31.9371px;"></div><div style="height: 26.6645px;"></div><div style="height: 16.1643px;"></div><div style="height: 13.2502px;"></div><div style="height: 21.158px;"></div><div style="height: 14.883px;"></div><div style="height: 8.64313px;"></div><div style="height: 13.1994px;"></div><div style="height: 15.1819px;"></div><div style="height: 11.5758px;"></div><div style="height: 6.24321px;"></div><div style="height: 2.8001px;"></div><div style="height: 5.96355px;"></div><div style="height: 8.41043px;"></div><div style="height: 8.25167px;"></div><div style="height: 17.9663px;"></div><div style="height: 37.0485px;"></div><div style="height: 34.4301px;"></div><div style="height: 28.7553px;"></div><div style="height: 23.2247px;"></div><div style="height: 19.6738px;"></div><div style="height: 15.739px;"></div><div style="height: 12.8087px;"></div><div style="height: 9.94589px;"></div><div style="height: 12.014px;"></div><div style="height: 15.3113px;"></div><div style="height: 12.0106px;"></div><div style="height: 8.61999px;"></div><div style="height: 9.42618px;"></div><div style="height: 8.19054px;"></div><div style="height: 8.69688px;"></div><div style="height: 11.5943px;"></div><div style="height: 23.9345px;"></div><div style="height: 23.941px;"></div><div style="height: 18.006px;"></div><div style="height: 13.0469px;"></div><div style="height: 8.2508px;"></div><div style="height: 8.51899px;"></div><div style="height: 7.6166px;"></div><div style="height: 12.7301px;"></div><div style="height: 13.92px;"></div><div style="height: 23.8323px;"></div><div style="height: 21.6298px;"></div><div style="height: 18.0855px;"></div><div style="height: 14.4261px;"></div><div style="height: 11.7562px;"></div><div style="height: 8.58724px;"></div><div style="height: 13.8875px;"></div><div style="height: 32.0526px;"></div><div style="height: 41.1631px;"></div><div style="height: 41.2912px;"></div><div style="height: 36.2116px;"></div><div style="height: 31.6233px;"></div><div style="height: 28.1054px;"></div><div style="height: 25.0953px;"></div><div style="height: 23.2512px;"></div><div style="height: 22.2446px;"></div><div style="height: 23.1315px;"></div><div style="height: 22.3367px;"></div><div style="height: 17.0145px;"></div><div style="height: 12.6897px;"></div><div style="height: 11.6587px;"></div><div style="height: 11.6059px;"></div><div style="height: 10.5797px;"></div><div style="height: 28.6251px;"></div><div style="height: 30.0777px;"></div><div style="height: 25.7395px;"></div><div style="height: 21.985px;"></div><div style="height: 24.7252px;"></div><div style="height: 20.2356px;"></div><div style="height: 19.4496px;"></div><div style="height: 17.5634px;"></div><div style="height: 28.7391px;"></div><div style="height: 32.9521px;"></div><div style="height: 33.4237px;"></div><div style="height: 31.576px;"></div><div style="height: 23.9976px;"></div><div style="height: 24.8794px;"></div><div style="height: 13.9085px;"></div><div style="height: 15.7929px;"></div><div style="height: 27.064px;"></div><div style="height: 31.8455px;"></div><div style="height: 24.268px;"></div><div style="height: 20.9234px;"></div><div style="height: 19.104px;"></div><div style="height: 32.2868px;"></div><div style="height: 33.2191px;"></div><div style="height: 37.3109px;"></div><div style="height: 30.6754px;"></div><div style="height: 25.3229px;"></div><div style="height: 20.2617px;"></div><div style="height: 12.68px;"></div><div style="height: 17.4625px;"></div><div style="height: 16.675px;"></div><div style="height: 16.1119px;"></div><div style="height: 20.5049px;"></div><div style="height: 43.1767px;"></div><div style="height: 46.5122px;"></div><div style="height: 35.7489px;"></div><div style="height: 26.5289px;"></div><div style="height: 26.039px;"></div><div style="height: 27.0153px;"></div><div style="height: 22.1954px;"></div><div style="height: 20.618px;"></div><div style="height: 22.254px;"></div><div style="height: 24.6994px;"></div><div style="height: 21.0791px;"></div><div style="height: 16.539px;"></div><div style="height: 15.7094px;"></div><div style="height: 15.1476px;"></div><div style="height: 14.9215px;"></div><div style="height: 16.4307px;"></div><div style="height: 28.1849px;"></div><div style="height: 29.937px;"></div><div style="height: 22.3733px;"></div><div style="height: 17.9383px;"></div><div style="height: 17.4717px;"></div><div style="height: 15.6274px;"></div><div style="height: 13.2684px;"></div><div style="height: 10.1304px;"></div><div style="height: 12.8937px;"></div><div style="height: 14.868px;"></div><div style="height: 13.4754px;"></div><div style="height: 14.069px;"></div><div style="height: 18.6654px;"></div><div style="height: 24.6001px;"></div><div style="height: 24.2579px;"></div><div style="height: 22.3259px;"></div><div style="height: 26.9322px;"></div><div style="height: 38.5698px;"></div><div style="height: 34.609px;"></div><div style="height: 25.8976px;"></div><div style="height: 22.0091px;"></div><div style="height: 18.7625px;"></div><div style="height: 13.9812px;"></div><div style="height: 10.0579px;"></div><div style="height: 9.25865px;"></div><div style="height: 12.2228px;"></div><div style="height: 12.5243px;"></div><div style="height: 9.92215px;"></div><div style="height: 9.92175px;"></div><div style="height: 6.21869px;"></div><div style="height: 7.01024px;"></div><div style="height: 6.37576px;"></div><div style="height: 16.604px;"></div><div style="height: 25.135px;"></div><div style="height: 21.8449px;"></div><div style="height: 17.3171px;"></div><div style="height: 18.2714px;"></div><div style="height: 14.9479px;"></div><div style="height: 13.9147px;"></div><div style="height: 10.6028px;"></div><div style="height: 13.5389px;"></div><div style="height: 18.4526px;"></div><div style="height: 16.9292px;"></div><div style="height: 14.2526px;"></div><div style="height: 11.704px;"></div><div style="height: 10.2154px;"></div><div style="height: 8.42114px;"></div><div style="height: 8.43408px;"></div><div style="height: 37.0422px;"></div><div style="height: 34.9948px;"></div><div style="height: 34.098px;"></div><div style="height: 29.9015px;"></div><div style="height: 25.3618px;"></div><div style="height: 19.7009px;"></div><div style="height: 12.0275px;"></div><div style="height: 10.3633px;"></div><div style="height: 12.7549px;"></div><div style="height: 17.3524px;"></div><div style="height: 16.9277px;"></div><div style="height: 12.6563px;"></div><div style="height: 8.43392px;"></div><div style="height: 14.2786px;"></div><div style="height: 8.65864px;"></div><div style="height: 8.02285px;"></div><div style="height: 24.1969px;"></div><div style="height: 32.3679px;"></div><div style="height: 29.2744px;"></div><div style="height: 18.2283px;"></div><div style="height: 10.2563px;"></div><div style="height: 20.1006px;"></div><div style="height: 22.0032px;"></div><div style="height: 21.2153px;"></div><div style="height: 23.27px;"></div><div style="height: 23.5487px;"></div><div style="height: 24.8474px;"></div><div style="height: 26.2348px;"></div><div style="height: 25.4786px;"></div><div style="height: 24.5032px;"></div><div style="height: 24.3382px;"></div><div style="height: 25.1704px;"></div><div style="height: 26.7427px;"></div><div style="height: 29.9632px;"></div><div style="height: 28.6233px;"></div><div style="height: 23.5069px;"></div><div style="height: 20.9937px;"></div><div style="height: 21.9784px;"></div><div style="height: 16.9314px;"></div><div style="height: 13.4876px;"></div><div style="height: 8.13858px;"></div><div style="height: 12.038px;"></div><div style="height: 15.171px;"></div><div style="height: 7.17693px;"></div><div style="height: 12.7693px;"></div><div style="height: 17.1756px;"></div><div style="height: 28.7626px;"></div><div style="height: 34.4658px;"></div><div style="height: 36.8942px;"></div><div style="height: 45.3802px;"></div><div style="height: 45.5065px;"></div><div style="height: 40.9182px;"></div><div style="height: 38.016px;"></div><div style="height: 32.719px;"></div><div style="height: 24.1255px;"></div><div style="height: 8.27852px;"></div><div style="height: 15.7905px;"></div><div style="height: 23.0388px;"></div><div style="height: 15.7562px;"></div><div style="height: 15.2041px;"></div><div style="height: 17.3524px;"></div><div style="height: 27.07px;"></div><div style="height: 36.1538px;"></div><div style="height: 35.5594px;"></div><div style="height: 36.5415px;"></div><div style="height: 42.9127px;"></div><div style="height: 41.8126px;"></div><div style="height: 37.2867px;"></div><div style="height: 1.6182px;"></div></div>
Not bad--obviously we're looking at audio data. But it's not symmetrical. Let's center those lines:

