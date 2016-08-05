## CSS [Back](./../CSS.md)

### `-ms` `-moz` `-webkit`
Attribute|Description
:---:|---
`-ms`|to represent **IE**'s private attributes.
`-moz`|to represent **Firefox**'s private attributes.
`-webkit`|to represent private attributes of **Chrome** and **Safari**.

### `background`
- `background`是一個複合屬性, 其下有`background-image`, `background-color`, `background-position`, `background-attachment`和`background-repeat`. 我們可以直接設置- - `background`, 也可以分別對其下屬性進行社設置.

	```css
background:url(../pic/background.png);
```
	- `background-image`
	设置背景图片

	```css
background-image:url(../pic/background.png);
```

	- `background-color`
	设置背景顏色

	```css
background-color:#000;
background-color:transparent;
background-color:rgba(0, 0, 0, 0.8);
```

### `float`

- `float`用於浮動某個對象
- 通常`<div>`是在標準流之中從上往下排列的, 若要使得某個`<div>`擺脫標准流, 則要把其設置為浮動.
- 浮動特性:
	- 若A元素設置了浮動, 而A前面的元素在標準流中, 那麼這兩個元素將保持**垂直排列**.
	- 若A元素設置了浮動, 而A前面的元素也設置了浮動, 則這兩個元素將**並行排列**.
	- 若兩元素都設置了浮動, 且想要保持**垂直排列**, 則可設置後一元素即A:
	
	```css
clear: left;	/* 強迫A元素左邊不能出現浮動 */
```

