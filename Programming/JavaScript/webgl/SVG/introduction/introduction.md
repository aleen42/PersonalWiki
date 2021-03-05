## Introduction [Back](./../SVG.md)

<img src="./logo.png">

- **Scalable Vector Graphics (SVG)** is an XML-based vector image format for two-dimensional graphics with support for interactivity and animation.
- It's not supported by **IE** kernel.
- There is no **semicolon** (`;`) behind each statement.

#### Animation

##### Step 1

- build the **outline** of one object with **Adobe Illustrator CC**.
- remember to save your SVG file with the following optimal **configuration**.

<img src="./configuration.png">

```html
<g>
	<!--M: start point; Z: end point -->
	<!--path label to represent the outline of an object-->
	<path style="fill:#60B17C;" d="M0.285-137.776c40.215,0.925,73.65,14.713,100.311,41.369
			c26.655,26.661,40.444,60.096,41.369,100.311c-0.553,31.731-9.685,59.588-27.395,83.568s-40.864,40.955-69.457,50.917
			c-3.506,0.552-5.997,0.043-7.471-1.522c-1.479-1.57-2.214-3.368-2.214-5.397l0.277-39.017c0-6.641-0.968-12.129-2.906-16.465
			c-1.937-4.332-4.198-7.61-6.779-9.822c16.417-1.108,31.131-6.408,44.137-15.911c13.006-9.5,19.877-27.534,20.615-54.099
			c0-7.562-1.293-14.527-3.874-20.891c-2.586-6.365-6.183-12.038-10.792-17.019c1.107-1.841,2.028-6.087,2.768-12.729
			c0.735-6.641-0.648-14.943-4.151-24.904c0-0.554-3.139-0.416-9.408,0.414c-6.274,0.83-16.145,5.583-29.609,14.251
			c-11.441-3.135-23.201-4.705-35.282-4.705c-12.084,0-23.936,1.57-35.558,4.705c-13.469-8.668-23.34-13.421-29.609-14.251
			c-6.274-0.83-9.408-0.968-9.408-0.414c-3.506,9.961-4.891,18.262-4.151,24.904c0.735,6.641,1.66,10.888,2.767,12.729
			c-4.613,4.8-8.21,10.378-10.791,16.742c-2.586,6.365-3.875,13.421-3.875,21.169c0.736,26.385,7.563,44.371,20.477,53.961
			c12.911,9.594,27.577,14.942,43.998,16.05c-2.033,1.66-3.874,4.059-5.534,7.194c-1.66,3.14-2.863,7.013-3.598,11.622
			c-4.799,2.586-11.254,3.692-19.37,3.321c-8.12-0.367-15.405-5.44-21.861-15.219c-2.953-4.981-6.322-8.578-10.1-10.792
			c-3.783-2.214-7.705-3.502-11.761-3.875c-3.506-0.367-5.672,0.187-6.503,1.66c-0.83,1.479,0.968,3.694,5.395,6.641
			c4.428,2.954,7.791,6.227,10.1,9.824c2.305,3.597,4.195,7.333,5.673,11.207c2.214,5.903,7.195,10.835,14.943,14.805
			c7.748,3.965,18.721,4.565,32.929,1.798l0.277,26.288c0,2.029-0.74,3.827-2.214,5.397c-1.479,1.565-3.969,2.075-7.472,1.522
			c-28.597-9.962-51.746-26.937-69.456-50.917s-26.842-51.838-27.395-83.568c0.921-40.215,14.709-73.651,41.369-100.311
			c26.656-26.656,60.092-40.444,100.311-41.369L0.285-137.776z"/>
</g>
```

##### Step 2

- add `<defs>` (放射性渐变標籤) for what you want to design, and then give it an **id**

```html
<defs>
<g id="github">
	<path style="fill:#60B17C;" d="M0.285-137.776c40.215,0.925,73.65,14.713,100.311,41.369
			c26.655,26.661,40.444,60.096,41.369,100.311c-0.553,31.731-9.685,59.588-27.395,83.568s-40.864,40.955-69.457,50.917
			c-3.506,0.552-5.997,0.043-7.471-1.522c-1.479-1.57-2.214-3.368-2.214-5.397l0.277-39.017c0-6.641-0.968-12.129-2.906-16.465
			c-1.937-4.332-4.198-7.61-6.779-9.822c16.417-1.108,31.131-6.408,44.137-15.911c13.006-9.5,19.877-27.534,20.615-54.099
			c0-7.562-1.293-14.527-3.874-20.891c-2.586-6.365-6.183-12.038-10.792-17.019c1.107-1.841,2.028-6.087,2.768-12.729
			c0.735-6.641-0.648-14.943-4.151-24.904c0-0.554-3.139-0.416-9.408,0.414c-6.274,0.83-16.145,5.583-29.609,14.251
			c-11.441-3.135-23.201-4.705-35.282-4.705c-12.084,0-23.936,1.57-35.558,4.705c-13.469-8.668-23.34-13.421-29.609-14.251
			c-6.274-0.83-9.408-0.968-9.408-0.414c-3.506,9.961-4.891,18.262-4.151,24.904c0.735,6.641,1.66,10.888,2.767,12.729
			c-4.613,4.8-8.21,10.378-10.791,16.742c-2.586,6.365-3.875,13.421-3.875,21.169c0.736,26.385,7.563,44.371,20.477,53.961
			c12.911,9.594,27.577,14.942,43.998,16.05c-2.033,1.66-3.874,4.059-5.534,7.194c-1.66,3.14-2.863,7.013-3.598,11.622
			c-4.799,2.586-11.254,3.692-19.37,3.321c-8.12-0.367-15.405-5.44-21.861-15.219c-2.953-4.981-6.322-8.578-10.1-10.792
			c-3.783-2.214-7.705-3.502-11.761-3.875c-3.506-0.367-5.672,0.187-6.503,1.66c-0.83,1.479,0.968,3.694,5.395,6.641
			c4.428,2.954,7.791,6.227,10.1,9.824c2.305,3.597,4.195,7.333,5.673,11.207c2.214,5.903,7.195,10.835,14.943,14.805
			c7.748,3.965,18.721,4.565,32.929,1.798l0.277,26.288c0,2.029-0.74,3.827-2.214,5.397c-1.479,1.565-3.969,2.075-7.472,1.522
			c-28.597-9.962-51.746-26.937-69.456-50.917s-26.842-51.838-27.395-83.568c0.921-40.215,14.709-73.651,41.369-100.311
			c26.656-26.656,60.092-40.444,100.311-41.369L0.285-137.776z"/>

</g>
</defs>
```

##### Step 3

- use `<use>` to add `<animateTransform >` or `<animate>`.

	- **Scale with opacity**

	**Code**

	```html
<use x="0" y="0" opcity="0" xlink:href="#github">
		<animateTransform
			attributeName="transform"
			attributeType="XML" <!--this can be CSS/XML/auto, x, y and transform belong to XML-->
			type="scale"
			dur="1s"
			values="1; 1.06; 1"
			keyTimes="0; 0.138; 1" <!--time: 0.138 * 1, to be 1.06.-->
			additive="sum" <!--This attribute controls whether or not the animation is additive.-->
			repeatCount="Indefinite" <!--forever-->
			/>
		<animate
			attributeName="opacity"
			dur="1s"
			values="0; 0.6; 0"
			keyTimes="0; 0.138; 1"
			repeatCount="Indefinite"
			/>
</use>
```

	**Show**

    <p>
    <p data-height="533" data-theme-id="21735" data-slug-hash="kXmvRL" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="kXmvRL" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/kXmvRL/">kXmvRL</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
    <script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
    </p>

	- **x/y with opacity**

	**Code**

	```html
<use x="0" y="0" opcity="0" xlink:href="#github">
		<animate
			attributeName="x"
			dur="2s"
			values="0; 100; 200; 100; 0; -100; -200; -100; 0"
			keyTimes="0; 0.125; 0.25; 0.375; 0.5; 0.625; 0.75; 0.875; 1"
			repeatCount="indefinite"
			/>
		<animate
			attributeName="y"
			dur="2s"
			values="0; 100; 200; 100; 0; -100; -200; -100; 0"
			keyTimes="0; 0.125; 0.25; 0.375; 0.5; 0.625; 0.75; 0.875; 1"
			repeatCount="indefinite"
			/>
		<animate
			attributeName="opacity"
			dur="2s"
			values="0; 1; 0"
			keyTimes="0; 0.5; 1"
			repeatCount="indefinite"
			/>
</use>
```

	**Show**

	<p>
    <p data-height="300" data-theme-id="21735" data-slug-hash="oLOpPd" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="oLOpPd" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/oLOpPd/">oLOpPd</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
    <script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
    </p>

	- **path(with auto rotate)**

	**Code**

	```html
<use x="0" y="0" opcity="0" xlink:href="#github">
		<animateMotion
			attributeName="x"
			dur="2s"
			keyTimes="0; 0.138; 1"
			path="M10,80 q100,120 120,20 q140,-50 160,0"
			repeatCount="indefinite"
			/>
		<animate
			attributeName="opacity"
			dur="2s"
			values="0; 1; 0"
			keyTimes="0; 0.138; 1"
			repeatCount="indefinite"
			/>
</use>
```

	**Show**

	<p>
    <p data-height="300" data-theme-id="21735" data-slug-hash="rLbpqr" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="rLbpqr" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/rLbpqr/">rLbpqr</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
    <script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
    </p>

	- **path(without auto rotate)**

	**Code**

	```html
<use x="0" y="0" opcity="0" xlink:href="#github">
		<animateMotion
			attributeName="x"
			dur="2s"
			keyTimes="0; 0.138; 1"
			path="M10,80 q100,120 120,20 q140,-50 160,0"
			repeatCount="indefinite"
			rotate="auto"
			/>
		<animate
			attributeName="opacity"
			dur="2s"
			values="0; 1; 0"
			keyTimes="0; 0.138; 1"
			repeatCount="indefinite"
			/>
</use>
```

	**Show**

	<p>
    <p data-height="300" data-theme-id="21735" data-slug-hash="qNwpJx" data-default-tab="result" data-user="aleen42" data-embed-version="2" data-pen-title="qNwpJx" class="codepen">See the Pen <a href="http://codepen.io/aleen42/pen/qNwpJx/">qNwpJx</a> by aleen42 (<a href="http://codepen.io/aleen42">@aleen42</a>) on <a href="http://codepen.io">CodePen</a>.</p>
    <script async src="https://production-assets.codepen.io/assets/embed/ei.js"></script>
    </p>

##### Step 4

- what we can also do is to add event for **SVG** with **JavaScript**.

	- JavaScript

	```js
var animate = document.getElementsByTagName("animate")[0];
if (animate) {
    document.getElementById("svg").onclick = function() {
        animate.beginElement();
    };
}
```

	- SVG

	```html
    <svg id="svg">
    	<!--relization-->
    </svg>
    ```

### Appendix

- **Bezier Curve(貝塞爾曲線)**

`calcMode="spline"`
`calcMode="linear"`

<img src="./interpSpline01.png">
`keySplines="0 0 1 1"`
<img src="./interpSpline02.png">
`keySplines="0.5 0 .5 1"`
<img src="./interpSpline03.png">
`keySplines="0 .75 .25 1"`
<img src="./interpSpline04.png">
`keySplines="1 0 .25 .25"`

- **accumulate & additive**
	- `accumulate`是累積的意思. 支持參數有：`none` | `sum`. 默認值是`none`. 如果值是`sum`表示動畫結束時候的位置作為下次動畫的起始位置.
	- `additive`控制動畫是否附加. 支持參數有：`replace` | `sum`. 默認值是`replace`. 如果值是`sum`表示動畫的基礎屬性會附加到其低優先級的動畫上

- **stroke**
	- `stroke` 表示描邊**顏色**
	- `stroke-width` 表示描邊**粗細**
	- `stroke-linecap` 表示描邊**端點**的表示方法
		- butt
		- round
		- square
		- inherit
		- <img src="./linecap.png">
	- `stroke-linejoin` 表示描邊**轉角**的表示方式
		- miter
		- round
		- bevel
		- <img src="./linejoin.png">
	- `stroke-dasharray` 表示虛線描邊
	- `stroke-dashoffset` 表示虛線的起始位置
	- `stroke-opacity` 表示描邊透明度

- **restart**

支持的參數有：`always` | `whenNotActive` | `never`, 默認值是`always`, 用於動畫開始後點擊事件對動畫的影響
