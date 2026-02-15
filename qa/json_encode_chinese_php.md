## How to json_encode Chinese in PHP [Back](./qa.md)

In PHP, you'll find that when you call `json_encode` to encode Chinese, they will be converted into string like this `\u4e2d\u6587`.

After PHP 5.4, you can solve it by using `JSON_UNESCAPED_UNICODE`:

```php
<?php
    echo json_encode('中文');   /** => "\u4e2d\u6587" */
?>
```

```php
<?php
    echo json_encode('中文', JSON_UNESCAPED_UNICODE);   /** => "中文" */
?>
```
