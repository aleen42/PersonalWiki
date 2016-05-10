## Eloquent [Back](./../laravel.md)

- **Eloquent** is the 'Object Relational Mapping'(ORM) in Laravel. We can easily handle data by using Eloquent Class.

```php
<?php

class Article extends Eloquent {
    protected $fillable = [];
}
```

### 1. Base Operation

- When extending the class Eloquent, we can use many methods to handle data like `first()`, `find()`, `where()` or `orderBy()`.
- There is some case to know how to use Eloquent to handle data:

#### Case1: find the article which id is 2 and print out its title

```php
$article = Article::find(2);

echo $article->title;
```

#### Case2: find out the article which title is 'hello' and print out its id

```php
$article = Article::where('title', 'hello')->first();

echo $article->id;
```

#### Case3: print out titles of all articles

```php
$articles = Article::all();

foreach ($articles as $key) {
    echo $key->title;
}
```

#### Case4: print out titles of articles which id is between 10 and 20

```php
$articles = Article::where('id', '>=', 10)->where('id', '<=', 20)->get();

foreach ($articles as $key) {
    echo $key->title;
}
```

#### Case5: print out titles of all articles under the order of ‘update_at'

```php
$articles = Article::orderBy('update_at', 'desc')->get();

foreach ($articles as $key) {
    echo $key->title;
}
```

### 2. Builder

- **Builder** is used to complete the function of chaining operation:

```php
/** the follow sentence will return a builder which can continue to add conditions */
Article::where('id', 1)
```

- the path of builder is in `Illuminate\Database\Eloquent\Builder`

### 3. Relationships

- **Relationships** mean the relationships between two models.
    - One to One
    - One to Many
    - Many to Many

#### One to One

```
user: id ... ... account_id
account: id ... ... user_id
```

- If we want to query related info in the table Account, we will have the following model of User:

```php
<?php

class User extends Eloquent {
    protected $table = 'users';
    
    public function hasOneAccount()
    {
        return $this->hasOne('Account', 'user_id', 'id');
    }
}
```

- and then, we can query the account which user id is 10:

```php
/** SQL: select * from account where user_id = 10; */
$account = User::find(10)->hasOneAccount;
```

- the related model of Account should be as follow:

```php
<?php

class Account extends Eloquent {
    protected $table = 'accounts';
    
    public function belongsToUser()
    {
        return $this->belongsTo('User', 'user_id', 'id');
    }
}
```

#### One to Many

```
user: id ... ...
pay: id ... ... user_id
```

- the model of User should be:

```php
<?php

class User extends Eloquent {
    protected $table = 'users';
    
    public function hasManyPays()
    {
        return $this->hasMany('Pay', 'user_id', 'id');
    }
}
```

- and the model of Pay should be as follow:

```php
<?php

class Pay extends Eloquent {
    protected $table = 'pays';
    
    public function belongsToUser()
    {
        return $this->belongsTo('User', 'user_id', 'id');   
    }
}
```

- then we can query like this:

```php
/** SQL: select * from pays where user_id = 10; */
$accounts = User::find(10)->hasManyPays()->get();

/** If you want to show out all two tables */
$accounts = User::where('id', 10)->with('hasManyPays')->first();
/** then you can look fr the data of another table */
var_dump($accounts->hasManyPays->pay_info);
```

#### Many to Many

```
article: id ... ...
tag: id ... ...
article_tag: article_id tag_id
```

- the model will be:

```php
class Tag extends Eloquent {
    protected $table = 'tags';
    
    public function belongsToManyArticle()
    {
        return $this->belongsToMany('Article', 'article_tag', 'tag_id', 'article_id');
    }
}
```

- the query will be:

```php
$tagsWithArticles = Tag::take(10)->get()->belongsToManyArticle()->get();
```

### 4. Eager Loading

- You'll find that if you want to query 10 users with info in the table, Account, you are in need to use **1 + 10** SQL sentences. Nevertheless, you'll only use **1 + 1** instead when using **Eager Loading**. More details about Eager Loading in [http://laravel-china.org/docs/eloquent#eager-loading](http://laravel-china.org/docs/eloquent#eager-loading).

```php
/** SQL: select * from account wher id in (1, 2, 3, ...) */
$users = User::with('hasOneAccount')->take(10)->get();
```

### 5. Specific Attributes

```php
/** Key and Value */
$tagsName = Tag::select('name')->get();

/** Only Value */
$tagsNameValue = Tag::pluck('name');
```