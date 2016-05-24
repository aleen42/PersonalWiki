## Database [Back](./../laravel.md)

### Configuration

- The database configuration file is located in **./conf/database.php**.

### Menu

- <a href="#1"><strong>Raw SQL Queries</strong></a>
- <a href="#2"><strong>Query Builder</strong></a>

<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />

<h1 id="1"> Raw SQL Queries</h1>

### Running Raw SQL Queries

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

### Database Transactions

- To run a set of operations within a database transaction, you may use the `transaction` method on the `DB` facade. If an exception is thrown within the transaction `Closure`, the transaction will automatically be rolled back. If the `Closure` executes successfully, the transaction will automatically be committed. You don't need to worry about manually rolling back or committing while using the `transaction` method:

	```php
DB::transaction(function () {
	DB::table('users')->update(['votes' => 1]);

	DB::table('posts')->delete();
});
```

##### Manually Using Transactions

- If you would like to begin a transaction manually and have complete control over rollbacks and commits, you may use the `beginTransaction` method on the `DB` facade:

	```php
DB::beginTransaction();
```

- You can rollback the transaction via the `rollBack` method:

	```php
DB::rollBack();
```

- Lastly, you can commit a transaction via the `commit` method:

	```php
DB::commit();
```

<br />
<br />
<br />
<br />
<br />
<br />

<h1 id="2"> Query Builder</h1>

### Introduction

- The database **query builder** provides a **convenient**, **fluent** interface to creating and running database queries.

### Retrieving Results

###### Retrieving All Rows From A Table

```php
$users = DB::table('users')->get();

return view('user.index', ['users' => $users]);
```

###### Retrieving A Single Row / Column From A Table

```php
$user = DB::table('users')->where('name', 'John')->first();

echo $user->name;
```

```php
$email = DB::table('users')->where('name', 'John')->value('email');
```

###### Chunking(大塊) Results From A Table

```php
DB::table('users')->chunk(100, function($users) {
	// Process the records...

	return false;
});
```

###### Retrieving A List Of Column Values (custom key)

```php
$roles = DB::table('roles')->lists('title', 'name');

foreach ($roles as $name => $title) {
	echo $title;
}
```

###### Aggregates(集合)

- `count`, `sum`, `avg`, `max` and `min`.

```php
$users = DB::table('users')->count();

$price = DB::table('orders')->max('price');
```

### Selects

###### Specifying A Select Clause

```php
$users = DB::table('users')->select('name', 'email as user_email')->get();
```

```php
$users = DB::table('users')->distinct()->get();
```

```php
$query = DB::table('users')->select('name');

$users = $query->addSelect('age')->get();
```

```php
$users = DB::table('users')
                     ->select(DB::raw('count(*) as user_count, status'))
                     ->where('status', '<>', 1)
                     ->groupBy('status')
                     ->get();
```
