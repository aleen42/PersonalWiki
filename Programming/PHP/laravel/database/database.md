## Database [Back](./../laravel.md)

### Configuration

- The database configuration file is located in **./conf/database.php**.

##### Read / Write Connections

- Note that two keys have been added to the configuration array: `read` and `write`. Both of these keys have array values containing a single key: `host`. The rest of the database options for the `read` and `write` connections will be merged from the main `mysql` array.
	```php
'mysql' => [
	'read' => [
		'host' => '192.168.1.1',
	],
	'write' => [
		'host' => '196.168.1.2'
    	],
    	'driver'    => 'mysql',
    	'database'  => 'database',
    	'username'  => 'root',
    	'password'  => '',
    	'charset'   => 'utf8',
    	'collation' => 'utf8_unicode_ci',
    	'prefix'    => '',
],
```

##### Running Raw SQL Queries

- Once you have configured your database connection, you may run queries using the `DB` facade. The `DB` facade provides methods for each type of query: `select`, `update`, `insert`, `delete`, and `statement`.
	```php
<?php

namespace App\Http\Controllers;

use DB;
use App\Http\Controllers\Controller;

class UserController extends Controller
{
    /**
     * Show a list of all of the application's users.
     *
     * @return Response
     */
    public function index()
    {
        $users = DB::select('select * from users where active = ?', [1]);

        return view('user.index', ['users' => $users]);
    }
}
```

- The first argument passed to the `select` method is the raw SQL query, while the second argument is any parameter bindings that need to be bound to the query. Typically, these are the values of the `where` clause constraints. Parameter binding provides protection against SQL injection.

- The `select` method will always return an `array` of results. Each result within the array will be a PHP `StdClass` object, allowing you to access the values of the results:
	```php
foreach ($users as $user) {
    echo $user->name;
}
```

<a href="#" style="left:200px;"><img src="./../../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a>