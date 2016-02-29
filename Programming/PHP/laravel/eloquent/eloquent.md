## Eloquent [Back](./../laravel.md)

- **Eloquent** is the 'Object Relational Mapping'(ORM) in Laravel. We can easily handle data by using Eloquent Class.

```php
<?php

class Article extends \Eloquent {
    protected $fillable = [];
}
```

- When extending the class Eloquent, we can use many methods to handle data like `first()`, `find()`, `where()` or `orderBy()`.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a>