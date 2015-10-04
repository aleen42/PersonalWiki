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

###### Running A Select Query

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

###### Using Named Bindings

- Instead of using `?` to represent your parameter bindings, you may execute a query using named bindings:
	```php
$results = DB::select('select * from users where id = :id', ['id' => 1]);
```

###### Running An Insert Statement

- To execute an `insert` statement, you may use the `insert` method on the `DB` facade. Like `select`, this method takes the raw SQL query as its first argument, and bindings as the second argument:
	```php
DB::insert('insert into users (id, name) values (?, ?)', [1, 'Dayle']);
```

###### Running An Update Statement

- The `update` method should be used to update existing records in the database. The number of rows affected by the statement will be returned by the method:
	```php
$affected = DB::update('update users set votes = 100 where name = ?', ['John']);
```

###### Running A Delete Statement

- The `delete` method should be used to delete records from the database. Like `update`, the number of rows deleted will be returned:
	```php
$deleted = DB::delete('delete from users');
```

###### Running A General Statement

- Some database statements should not return any value. For these types of operations, you may use the `statement` method on the `DB` facade:
	```php
DB::statement('drop table users');
```

##### Listening For Query Events

- If you would like to receive each SQL query executed by your application, you may use the `listen` method. This method is useful for logging queries or debugging.

	```php
<?php

namespace App\Providers;

use DB;
use Illuminate\Support\ServiceProvider;

class AppServiceProvider extends ServiceProvider
{
	/**
     	* Bootstrap any application services.
     	*
     	* @return void
     	*/
    	public function boot()
    	{
        	DB::listen(function($sql, $bindings, $time) {
            	//
        	});
    	}

    	/**
     	* Register the service provider.
     	*
     	* @return void
     	*/
    	public function register()
    	{
        	//
    	}
}
```

<a href="#" style="left:200px;"><img src="./../../../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../../pic/tail.gif"></a>