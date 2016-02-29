## Eloquent [Back](./../laravel.md)

- **Eloquent** is the 'Object Relational Mapping'(ORM) in Laravel. We can easily handle data by using Eloquent Class.

```php
<?php

class Article extends \Eloquent {
    protected $fillable = [];
}
```

- When extending the class Eloquent, we can use many methods to handle data like `first()`, `find()`, `where()` or `orderBy()`.
- There is somd case to know how to use Eloquent to handle data:

#### Case1: find the article which id is 2 and print out

```php
$article = Article::find(2);

echo $article->title;
```

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a>