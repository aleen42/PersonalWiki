## Crash Course of PHP [Back](./../JavaScript.md)

### 1. Embedding PHP in HTML

- PHP tags: 
	- **XML** Style: ```<?php echo '<p>Order processed.</p>'; ?>```
	- **Short** Style: ```<? echo '<p>Order processed.</p>'; ?>```
	- **SCRIPT** Style: ```<script language='php'> echo '<p>Order processed.</p>'; </script>```
	- **ASP** Style: ```<% echo '<p>Order processed.</p>'; %>```

```html
<html>
<head>
	<title>Bob's Auto Parts - Order Results</title>
</head>

<body>
	<h1>Bob's Auto Parts</h1>
```

```php
	<?php
		echo '<p>Order processed.</p>';
	?>
```

```html
</body>
</html>
```

### 2. PHP Statements
##### 2.1 Whitespace

```php
<?php echo 'hello     ' . 'world' ?>
<?php ecoo 'hello ' . 'world' ?>
```

<?php echo 'hello     ' . 'world' ?>
<?php ecoo 'hello ' . 'world' ?>


<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>