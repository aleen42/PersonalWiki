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
<?php echo 'hello ' . 'world' ?>
```

##### 2.2 Comments

```php
<?php 
	echo ‘<p>Order processed.</p>’; // Start printing order
?>
<?php 
	echo ‘<p>Order processed.</p>’; # Start printing order
?>
<?php 
	echo ‘<p>Order processed.</p>’; /* Start printing order */
?>
```

##### 2.3 Function

```php
<?php
	data('H:i, jS F');	// 'H' for 24-hour format with leading zeros
				// 'i' for minutes	with leading zeros
				// 'j' for the day of the month without a leadig zero
				// 'S' for the ordinal suffix(like 'th')
				// 'F' for the full name of month
?>
```

##### 2.4 Variables

- **short style**: requires the **register_globals** configuration setting be turned on with the reson of security issue.(off by default)
- **medium style**: solve the security issue.(**recommended**)
	- **$_POST**: the form was submitted via the *POST* method.
	- **$_GET**: the form was submitted via *GET* method.
	- **$_REQUEST**: th for was submitted via either *POST* or *GET* method.
- **long style**: used on **old** server.

```php
$var				// short style
$_POST['var']			// medium style
$HTTP_POST_VARS['var']		// long style
```



<a href="#" style="left:200px;"><img src="./../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>