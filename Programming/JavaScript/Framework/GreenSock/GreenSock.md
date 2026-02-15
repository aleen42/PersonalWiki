## GreenSock [Back](./../Framework.md)

- **GreenSock** 
	- [**DrawSVGPlugin**](http://greensock.com/drawSVG) allows you to progressively reveal (or hide) the stroke of an SVG ```<path>```, ```<line>```, ```<polyline>```, ```<polygon>```, ```<rect>```, or ```<ellipse>``` and you can even animate outward from the center of the stroke (or any position/segment). It does this by controlling the ```stroke-dashoffset``` and ```stroke-dasharray``` CSS properties.

### Code

- SVG

```svg
<svg version="1.1" id="loader" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" style="background:#a10000;" width="100%" height="50%" viewBox="0 -45 400 250" xml:space="preserve">
    <path id="path1" style="fill:none;stroke:#000000;stroke-miterlimit:10;"d="M200.198,34.273c-15.919,0-30.338,6.227-41.5,16.227H187.5v17H180
	h-35.196c-3.067,5-5.355,11-6.711,17H187.5v18h-50.736c0.279,4,1.152,10,2.551,15H200h60.646c1.399-5,2.272-10,2.551-15H209.5v-18
	h52.368c-1.356-6-3.643-12-6.711-17h-35.196H209.5v-17h31.764c-11.163-10-25.562-15.977-41.481-15.977"/>
	<path id="path2" style="fill:none;stroke:#000000;stroke-miterlimit:10;" d="M209.5,160.134c18-2.905,33.225-12.634,42.771-26.634H208h-13
	h-48.63c9.419,14,24.13,23.463,41.13,26.515v14.44c-38-5.712-67.083-38.587-67.083-78.288c0-43.723,35.569-79.167,79.292-79.167
	s78.979,35.444,78.979,79.167c0,40.278-30.188,73.53-69.188,78.52V160.134z"/>
</svg>
```

- DrawSVG
	- DrawSVGPlugin.min.js
	- TweenMax.min.js

```js
(function(){
	var container = document.getElementById('container');
	var loader = document.getElementById('loader');
	var path1 = document.getElementById('path1');
	var path2 = document.getElementById('path2');
	
	var t = new TimelineMax({
		repeat: -1,				// -1: indefinite, n: n+1 if n>=0
		yoyo: false				// false: A-B-A-B, true: A-B-B-A
	});
	
	t.timeScale(1.2);				// speed
	t.set([path1, path2], {
		drawSVG: '0% 0%'
	}, '-=2');					// previous 2/speed (s)
	
	t.to([path1, path2], 3, {			// 3/speed (s)
		drawSVG: '0% 100%'			// 'start, length'
	});
	
	t.to([path1, path2], 3, {
		drawSVG: '0% 0%'
	}, '+=2');					// delay 2/speed (s)
				
})();
```

- Alpha [[**Example**](http://aleen42.github.io/example/Greensock/Alpha.html)]
	- TweenMax.min.js

```js
(function(){
	var container = document.getElementById('container');
	var loader = document.getElementById('loader');
	var path1 = document.getElementById('path1');
	var path2 = document.getElementById('path2');
	
	var t = new TweenlineMax({
		repeat: -1,
		yoyo: true
	});
	
	t.timeScale(5);
	t.set([path1, path2], {
		alpha: 0.0,					// alpha
		ease: Power1.easeInOut
	}, '-=2');
	
	t.to([path1, path2], 3, {
		alpha: 0.8,
		ease: Power1.easeInOut
	});
				
	t.to([path1, path2], 3, {
		alpha: 1.0,
		ease: Power1.easeInOut
	}, '+=2');
})();
```

- Scale [[**Example**](http://aleen42.github.io/example/Greensock/Scale.html)]

```js
(function(){
	var container = document.getElementById('container');
	var loader = document.getElementById('loader');
	var outer = document.getElementById('outer');
	
	var t = new TimelineMax({
		repeat: -1,
		yoyo: false
	});
	
	t.timeScale(5);
	t.set(outer, {
		scale: 1.0,
		transformOrigin: '50% 50%',
		ease: Power1.easeInOut
	}, '-=2');
	
	t.to(outer, 3, {
		scale: 1.1,				// scale
		transformOrigin: '50% 50%',		// the centeral point
		ease: Power1.easeInOut
	});
	
	t.to(outer, 3, {
		scale: 1.0,
		transformOrigin: '50% 50%',
		ease: Power1.easeInOut
	}, '+=2');		
})();
```

- Rotation and Move [[**Example**](http://aleen42.github.io/example/Greensock/RotationandMove.html)]

```js
(function(){
	var rectangle = document.getElementById('rectangle');
	
	var t = new TimelineMax({
		repeat: -1,
		yoyo: true
	});
	
	t.timeScale(2);
	
	var width = rectangle.width;
	var num = 1;
	
	t.set(rectangle, {
		transformOrigin: '100% 100%',
	});
	
	t.to(rectangle, 3, {
		rotation: '+=90',
		ease: Power1.easeInOut
	});
	
	t.set(rectangle, {
		transformOrigin: '100% 100%',
		x: '+=100',			// move
		rotation: 0
	});
	
	t.to(rectangle, 3, {
		rotation: '+=90',		// rotation
		ease: Power1.easeInOut
	});
	
	t.to(rectangle, 2, {
						// delay for 2/speed (s)
	});	
})();

```

- Rain [[**Example**](http://aleen42.github.io/example/Greensock/Water.html)]

```js
var loader = document.getElementById('loader');
var circle = document.getElementById('circle');
var rectangle = document.getElementById('rectangle');
var rain = document.getElementById('rain');
var ra = [rain];
var re = [rectangle];
var ci = [circle];

var play = function(circle, rectangle, rain){	
	var t = new TimelineMax({
		repeat: -1,
		yoyo: false
	});
	
	t.timeScale(2.5);
	
	
	t.set(rain, {
		x: Math.floor(Math.random() * 300),
		y: Math.floor(Math.random() * 120)
	});
	
	t.set(circle, {
		attr: {
			rx: 0,
			ry: 0
		}
	});
	
	t.set(rectangle, {
		attr: {
			height: 0
		}
	});
	
	t.set([rectangle, circle], {
		y: 0
	});
	
	t.to(circle, Math.random() * 3,{
		
	});
	
	t.to(rectangle, 1, {
		attr: {
			height: '+=20'
		},
		y: '+=50',
		alpha: 0
	});
	
	r_x = Math.floor(Math.random() * 5) + 10;
	
	t.to(circle, 1.5, {
		attr: {
			rx: '+=' + r_x,
			ry: '+=' + r_x/3
		},
		alpha: 0,
		ease: Power1.easeInOut
	}, '-=0.3');
	
	t.to([circle, rectangle], 5, {
		
		});
	
};

var add = function(num){
	play(ci[0], re[0], ra[0]);
	for(i = 1; i < num; i++)
	{
		ra[num] = rain.cloneNode();
		re[num] = rectangle.cloneNode();
		ci[num] = circle.cloneNode();
		ra[num].appendChild(re[num]);
		ra[num].appendChild(ci[num]);
		loader.appendChild(ra[num]);
		play(ci[num], re[num], ra[num]);
	}
};

add(80);
```
- Leaves [[**Example**](http://aleen42.github.io/example/Greensock/Leaves.html)]
	
```js
// near
var leave = document.getElementById('leave');
var leave_child = document.getElementById('leave_child');
var container = document.getElementById('container');
var le = [leave];
var lc = [leave_child];

var animation = function(leave, leave_child){

	var t = new TimelineMax({
		repeat: -1,
		yoyo: false
	});
	
	t.timeScale(1);

	var time = 10 + Math.random() * 15;
	var height = 100 + Math.floor(Math.random() * 800);
	var distance = 1800 + Math.random() * 500;
	var rota = 300 + Math.random() * 700;
	var sc = 2 + Math.random() * 2;
	
	t.set(leave, {
		top: -100 + Math.random() * 250,
		left: -200,
		alpha: 0.9 + Math.random()
	});
	
	t.set(leave_child, {
		rotation: Math.random() * 360
	});
	
	t.to([leave,leave_child], Math.random()* 4, {
		
	});

	t.to(leave_child, time, {
		transformOrigin: '50% 50%',
		rotation: '+=' + rota,
	}, '-=' + time);

	t.to([leave, leave_child], time, {
		top: '+=' + height,
		left: '+=' + distance,
		scale: sc,
		
		ease: Power1.easeInOut
	}, '-=' + time);
	
	t.to([leave,leave_child], Math.random()* 4, {
		
	});
};

var add = function(num){
	for(i = 1; i < num; i++)
	{
		le[i] = leave.cloneNode();
		var pre = Math.random() * 360;
		var next = pre + 360;
		le[i].innerHTML = "<style>#leave_" + i +"{-webkit-transform-origin:center;-webkit-transform: rotateY("+ pre + "deg);-webkit-animation: rotate_Y "+ (Math.random() + 3) +"s;-webkit-animation-iteration-count:infinite;}@-webkit-keyframes rotate_Y{from {-webkit-transform: rotateY("+ pre + "deg);}to {-webkit-transform: rotateY("+ next + "deg);}}</style>";
		le[i].id = "leave_" + i;
		lc[i] = leave_child.cloneNode();
		le[i].appendChild(lc[i]);
		container.appendChild(le[i]);
		animation(le[i], lc[i]);
	}
};

add(3);
```


```js
// middle
var leave = document.getElementById('leave');
var leave_child = document.getElementById('leave_child');
var container = document.getElementById('container');
leave.innerHTML = "<style>#leave{-webkit-transform-origin:center;-webkit-animation: rotate_Y 2s;-webkit-animation-iteration-count:infinite;}@-webkit-keyframes rotate_Y{from {-webkit-transform: rotateY(0deg);}to {-webkit-transform: rotateY(360deg);}}</style>";
var le = [leave];
var lc = [leave_child];

var animation = function(leave, leave_child){

	var t = new TimelineMax({
		repeat: -1,
		yoyo: false
	});
	
	t.timeScale(1);

	var time = 10 + Math.random() * 15;
	var height = 100 + Math.floor(Math.random() * 800);
	var distance = 1800 + Math.random() * 500;
	var rota = 300 + Math.random() * 700;
	var sc = 0.3 + Math.random() * 1.5;
	
	t.set(leave, {
		top: -100 + Math.random() * 250,
		left: -200,
		alpha: 0.8 + Math.random()
	});
	
	t.set(leave_child, {
		rotation: Math.random() * 360
	});
	
	t.to([leave,leave_child], Math.random()* 4, {
		
	});

	t.to(leave_child, time, {
		transformOrigin: '50% 50%',
		rotation: '+=' + rota,
	}, '-=' + time);

	t.to([leave, leave_child], time, {
		top: '+=' + height,
		left: '+=' + distance,
		scale: sc,
		
		ease: Power1.easeInOut
	}, '-=' + time);
	
	t.to([leave,leave_child], Math.random()* 4, {
		
	});
};

var add = function(num){
	animation(le[0], lc[0]);
	for(i = 1; i < num; i++)
	{
		le[i] = leave.cloneNode();
		var pre = Math.random() * 360;
		var next = pre + 360;
		le[i].innerHTML = "<style>#leave_" + i +"{-webkit-transform-origin:center;-webkit-transform: rotateY("+ pre + "deg);-webkit-animation: rotate_Y "+ (Math.random() + 3) +"s;-webkit-animation-iteration-count:infinite;}@-webkit-keyframes rotate_Y{from {-webkit-transform: rotateY("+ pre + "deg);}to {-webkit-transform: rotateY("+ next + "deg);}}</style>";
		le[i].id = "leave_" + i;
		lc[i] = leave_child.cloneNode();
		le[i].appendChild(lc[i]);
		container.appendChild(le[i]);
		animation(le[i], lc[i]);
	}
};

add(20);
```

```js
// far
var remote_leave = document.getElementById('remote_leave');
var remote_leave_child = document.getElementById('remote_leave_child');
var container = document.getElementById('container');
remote_leave.innerHTML = "<style>#remote_leave{-webkit-transform-origin:center;-webkit-animation: rotate_Y 2s;-webkit-animation-iteration-count:infinite;}@-webkit-keyframes rotate_Y{from {-webkit-transform: rotateY(0deg);}to {-webkit-transform: rotateY(360deg);}}</style>";
var le = [remote_leave];
var lc = [remote_leave_child];

var animation = function(remote_leave, remote_leave_child){

	var t = new TimelineMax({
		repeat: -1,
		yoyo: false
	});
	
	t.timeScale(1);

	var time = 10 + Math.random() * 15;
	var height = 100 - Math.floor(Math.random() * 800);
	var distance = 1800 + Math.random() * 500;
	var rota = 300 + Math.random() * 700;
	var sc = 1.2 - Math.random();
	
	t.set(remote_leave, {
		top: 100 + Math.random() * 100,
		left: 180,
		alpha: 0.7 + Math.random()
	});
	
	t.set(remote_leave_child, {
		rotation: Math.random() * 360
	});
	
	t.to([remote_leave,remote_leave_child], Math.random()* 4, {
		
	});

	t.to(remote_leave_child, time, {
		transformOrigin: '50% 50%',
		rotation: '+=' + rota,
	}, '-=' + time);

	t.to([remote_leave, remote_leave_child], time, {
		top: '+=' + height,
		left: '+=' + distance,
		scale: sc,
		
		ease: Power1.easeInOut
	}, '-=' + time);
	
	t.to([remote_leave,remote_leave_child], Math.random()* 4, {
		
	});
};

var add = function(num){
	animation(le[0], lc[0]);
	for(i = 1; i < num; i++)
	{
		le[i] = remote_leave.cloneNode();
		var pre = Math.random() * 360;
		var next = pre + 360;
		le[i].innerHTML = "<style>#remote_leave_" + i +"{-webkit-transform-origin:center;-webkit-transform: rotateY("+ pre + "deg);-webkit-animation: rotate_Y "+ (Math.random() + 3) +"s;-webkit-animation-iteration-count:infinite;}@-webkit-keyframes rotate_Y{from {-webkit-transform: rotateY("+ pre + "deg);}to {-webkit-transform: rotateY("+ next + "deg);}}</style>";
		le[i].id = "remote_leave_" + i;
		lc[i] = remote_leave_child.cloneNode();
		le[i].appendChild(lc[i]);
		container.appendChild(le[i]);
		animation(le[i], lc[i]);
	}
};

add(15);
```

### Download

- DrawSVGPlugin
	- Just Click [**here**](https://github.com/aleen42/PersonalWiki/raw/master/Programming/JavaScript/Framework/GreenSock/DrawSVGPlugin.rar) to download.
