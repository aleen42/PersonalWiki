## Dates & Times [Back](./../Type.md)
- create objects that represent dates and times with `Date()`.

```js
var later = new Date(2010, 0, 1, 17, 10, 30);	//5:10:30pm, local time
var then = new Date(2010, 0, 1);	//Jan 1st, 2010

var now = new Date();	//current time

//API
later.toString();	// => "Fri Jan 01 2010 17:10:30 GMT-0800 (PST)"
later.toUTCString();	// => "Sat, 02 Jan 2010 01:10:30 GMT"
later.toLocaleDateString();	// => "01/01/2010"
later.toLocaleTimeString();	// => "05:10:30 PM"
later.toISOString();		// => "2010-01-02T01:10:30.000Z"; ES5
```
