## GreenSock [Back](./../Framework.md)

- **GreenSock** 
	- [**DrawSVGPlugin**](http://greensock.com/drawSVG) allows you to progressively reveal (or hide) the stroke of an SVG ```<path>```, ```<line>```, ```<polyline>```, ```<polygon>```, ```<rect>```, or ```<ellipse>``` and you can even animate outward from the center of the stroke (or any position/segment). It does this by controlling the ```stroke-dashoffset``` and ```stroke-dasharray``` CSS properties.

###Code
- DrawSVGPlugin

```js
var loader = document.getElementById('loader');	// loader is the id of the SVG
var container = document.getElementById('container');	// a container containing the SVG
var circle = document.getElementById('circle');	// a circle

// put SVG in the middle of the container by setting attributes
TweenMax.set([loader, container], {
	position: 'absolute',
	top: '50%',
	yPercent: -50,
	left: '50%',
	xPercent: -50
})

// create a object of TimelineMax(like a storyboard)
var tl = new TimelineMax({
	repeat: -1,		// indefinite for -1, n+1 times for n(n>=0)
	yoyo: false		// true: A-B-B-A
				// false: A-B-A-B
});

// speed
t1.timeScale(3);

// initialize
t1.set([jump], {
	drawSVG: '0% 0%'	// 'start length'
})
  .set([circle], {
	attr: {			// set attributes of a element of SVG		
		rx: 0,
		ry: 0,
	}
})

// write a timeline(storyboard)
  .to([jump], 0.4, {		// 0.4: Number - Amount of delay in seconds (or frames for frames-based tweens) before the animation should begin.
	drawSVG: '0% 30%',
	ease: Liner.easeNone	// ease: Ease (or Function or String) - You can choose from various eases to control the rate of change during the animation, giving it a specific "feel".
}, '+=0.3')

  .to([circl] 2, {
	attr: {
		rx: '+=30',
		ry: '+=10'
	},
	alpha: 0,
	ease: Power1.easeOut
}, '-=0.1')	// previous by 0.5

```

<img src="./api.png">


###Download
- DrawSVGPlugin
	- Just Click [**here**](https://github.com/aleen42/PersonalWiki/raw/master/Programming/JavaScript/Framework/GreenSock/DrawSVGPlugin.rar) to download.


<a href="#" style="left:200px;"><img src="./../../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a>