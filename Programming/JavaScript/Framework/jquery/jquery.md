## JQuery [Back](./../Framework.md)

[**JQuery.js**](https://jquery.com/) is a fast, small, and feature-rich JavaScript library.

### Code

##### DOM Traversal and Manipulation

```js
$( "button.continue" ).html( "Next Step..." );
```
##### Event Handling

```js
var hiddenBox = $( "#banner-message" );
$( "#button-container button" ).on( "click", function( event ) {
	hiddenBox.show();
});
```

##### Ajax

```js
$.ajax({
	url: "/api/getWeather",
	data: {
		zipcode: 97201
	},
	success: function( data ) {
		$( "#weather-temp" ).html( "<strong>" + data + "</strong> degrees" );
	}
});
```

##### Deferred Object

###### Allow linked operations

```js
$.ajax("test.html")
.done(function() {
	console.log('success');
	})
.fail(function() {
	console.log('error');
})
.always(function() {
	console.log('ajax completed');
});
```

###### Allow to bind mutiple callback methods to one ajax request

```js
$.ajax("test.html")
.done(function() {
	console.log('success');
	})
.fail(function() {
	console.log('error');
})
.done(function() {
	console.log('success 2');
});
```

###### Allow to bind one same callback method to different ajax requests

```js
$.when($.ajax("test.html"), $.ajax("test2.html"))
.done(function() {
	console.log('success');
	})
.fail(function() {
	console.log('error');
})
.always(function() {
	console.log('ajax completed');
});
```

###### Interfaces for original operations

```js

/**
 *	An original operation which costs some time
 */
var dtd = $.Deferred();		// a deferred object
var wait = function() {
	var tasks = function() {
		alert('completed');
		dtd.resolve();	// change the state of the deferred object to resolved. Deffered objects have 3 states: 未完成, 已完成(resolved), 已失敗(rejected)
		// dtd.reject();
	};
	setTimeout(tasks, 5000);
	return dtd.promise();	// avoid to the outter change to dtd like excuting a sentance, like `dtd.resolve();` after $.when()
};

/**
 *	Set the callback method to this function
 */
$.when(wait)
.done(function() {
	console.log('success');
	})
.fail(function() {
	console.log('error');
})
.always(function() {
	console.log('ajax completed');
});

/**
 * 	The second way to avoid to the outter change to deferred objects
 */
$.Defferred(wait)
.done(function() {
	console.log('success');
	})
.fail(function() {
	console.log('error');
})
.always(function() {
	console.log('ajax completed');
});

/**
 * 	The third way to avoid to the outter change to deferred objects
 */

dtd.promise(wait);
wait.done(function() {
	console.log('success');
	})
.fail(function() {
	console.log('error');
})
.always(function() {
	console.log('ajax completed');
});

```

###### Combine callback method `done` with `fail`

```js
$.when($.ajax("test.php"))
.then(successFunc, failFunc);
```

### Download

- Just Click [**here**](./jquery-2.1.4.min.js) to download.
