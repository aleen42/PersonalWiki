## Tables [Back](./../HTML.md)

- a table represent information in a **grid** format.
- each block in the grid is referred to as a **table cell**.

### 1. Basic structure
- ```<table>```is used to create a table
- ```<tr>```represents each row
- ```<td>```represents each element in this row
	
```html
<table>
	<tr>
		<td>15</td>
		<td>20</td>
	</tr>
	<tr>
		<td>25</td>
		<td>30</td>
	</tr>
</table>
```
<table>
	<tr>
		<td>15</td>
		<td>20</td>
	</tr>
	<tr>
		<td>25</td>
		<td>30</td>
	</tr>
</table>





### 2. Headings
- ```<th>``` is used to represent a **head** for each row or each column.

```html
<table>
	<tr>
		<th></th>
		<th scope="col">a</th>
		<th scope="col">b</th>
		<th scope="col">a+b</th>
	</tr>
	<tr>
		<th scope="row">example 1</th>
		<td>1</td>
		<td>2</td>
		<td>3</td>
	</tr>
	<tr>
		<th scope="row">example 2</th>
		<td>2</td>
		<td>2</td>
		<td>t</td>
	</tr>
</table>
```

<table>
	<tr>
		<th></th>
		<th scope="col">a</th>
		<th scope="col">b</th>
		<th scope="col">a+b</th>
	</tr>
	<tr>
		<th scope="row">example 1</th>
		<td>1</td>
		<td>2</td>
		<td>3</td>
	</tr>
	<tr>
		<th scope="row">example 2</th>
		<td>2</td>
		<td>2</td>
		<td>t</td>
	</tr>
</table>

### 3. Panning Columns & Spanning Rows

##### Panning Columns(合併列)

```html
<table>
	<tr>
		<th></th>
		<th>9am</th>
		<th>10am</th>
		<th>11am</th>
		<th>12am</th>
	</tr>
	<tr>
		<th>Monday</th>
		<td colspan="2">Geography</td>
		<td>Math</td>
		<td>Art</td>
	</tr>
	<tr>
		<th>Tuesday</th>
		<td colspan="3">Gym</td>
		<td>Home Ec</td>
	</tr>
</table>
```
<table>
	<tr>
		<th></th>
		<th>9am</th>
		<th>10am</th>
		<th>11am</th>
		<th>12am</th>
	</tr>
	<tr>
		<th>Monday</th>
		<td colspan="2">Geography</td>
		<td>Math</td>
		<td>Art</td>
	</tr>
	<tr>
		<th>Tuesday</th>
		<td colspan="3">Gym</td>
		<td>Home Ec</td>
	</tr>
</table>

##### Spanning Rows(合併行)

```html
<table>
	<tr>
		<th></th>
		<th>ABC</th>
		<th>BBC</th>
		<th>CNN</th>
	</tr>
	<tr>
		<th>6pm - 7pm</th>
		<td rowspan="2">Movie</td>
		<td>Comedy</td>
		<td>News</td>
	</tr>
	<tr>
		<th>7pm - 8pm</th>
		<td>Sport</td>
		<td>Current Affairs</td>
	</tr>
</table>
```
<table>
	<tr>
		<th></th>
		<th>ABC</th>
		<th>BBC</th>
		<th>CNN</th>
	</tr>
	<tr>
		<th>6pm - 7pm</th>
		<td rowspan="2">Movie</td>
		<td>Comedy</td>
		<td>News</td>
	</tr>
	<tr>
		<th>7pm - 8pm</th>
		<td>Sport</td>
		<td>Current Affairs</td>
	</tr>
</table>

<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
