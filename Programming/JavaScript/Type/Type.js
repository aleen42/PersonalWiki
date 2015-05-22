var x;
x = 0;
x	//=>0

//JavaScript supports several types of values
x = 1;	//integers
x = 0.1;	//real
x = "Aloha";	//String in quatation marks
x = 'Aloha';	//String in single quatations 
x = true;	//boolean
x = null;	//no value
x = undefined;	//like null

//Math to use
Math.pow(2,53)	//=>2^53
Math.round(.6)	//=>1.0
//...

//Positive Infinity
Infinity	
Number.POSITIVE_INFINITY	
1/0
Number.MAX_VALUE + 1

//Negative Infinity
-Infinity
Number.NEGATIVE_INFINITY
-1/0		
-Number.MAX_VALUE - 1		

//NaN
NaN
Number.NaN
0/0

//Precision you need to know
var x = .3 - .2;
var y = .2 - .1;
x == y;		//false: the two values are not the same!
x == 0.1;	//false
y == 0.1;	//true

//Date and Time
var later = new Date(2010, 0, 1, 17, 10, 30);	//5:10:30pm, local time
var then = new Date(2010, 0, 1);	//Jan 1st, 2010

var now = new Date();	//current time

//API
later.toString();	// => "Fri Jan 01 2010 17:10:30 GMT-0800 (PST)"
later.toUTCString();	// => "Sat, 02 Jan 2010 01:10:30 GMT"
later.toLocaleDateString();	// => "01/01/2010"
later.toLocaleTimeString();	// => "05:10:30 PM"
later.toISOString();		// => "2010-01-02T01:10:30.000Z"; ES5