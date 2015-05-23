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

//Text
var p = "π";	//π is 1 character with 16-bit codepoint 0x03c0
var e = "e"	//e is 1 character with 17-bit codepoint 0x1d452
p.length	// => 1
e.length 	// => 2
	
"two\nlines"	//there are 2 lines
	
//there is only 1 line.
"one\
line\
only"

	
//Pattern matching
var text = "testing: 1, 2, 3";
var pattern = /\d+/g
pattern.test(text)	// => true
text.search(pattern)	// => 9: position of first match
text.match(pattern)	// => [ "1", "2", "3"]: array of all matches
text.replace(pattern, "#")	// => "testing: #, #, #"
text.split(/\D+/);	// => [ "", "1", "2", "3"]: split on non-digits

//Wrapper Objects
var s = "Aloha";
s.substring(s.indexOf("A"), s.length);	//s.length (value)
										//s.indexOf() (method)

var s = "test";
s.len = 4;		//s.len undefined
var t = s.len;	//t = undefined

var s = "Aloha"
s.toUpperCase();	//return a new string, but dosen't change s
s					// => "Aloha"

var o = {x: 1};  
o.x = 2;		//change the value of x
o.y = 3;		//set a new property y

var a = [1, 2, 3];
a[0] = 0;	//Change the value of the first element
a[3] = 4;	//Add new element into the array

//Compare
var a = 3;
var b = "3";
a == b			// => true: only when the values are the same
a === b			// => false: cause the type is not the same

var a = [], b = [];
a == b			// => false
a === b			// => false

var a = {x: 1}, b = {x: 1};
a == b			// => false
a === b			// => false

var a = [];
var b = a;
a == b			// => true
a === b			// => true

function equalArray(a, b){
	if(a.length != b.length) 			//first check length
		return false;
	for(var i = 0; i < a.length; i++)		//second check member
		if(a[i] !== b[i])
			return false;
	return true;
}
