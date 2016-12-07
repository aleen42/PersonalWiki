## Strings and Regular Expressions [Back](./../high_performance.md)

This chapter mainly helps you understand how regular expression engines internally process strings and teaches you how to write regular expressions that take advantage of this knowledge.

Also in this chapter, we will learn about the fastest cross-browser methods for concatenating and trimming strings, discover how to increase regex performance by reducing backtracking, and any other tips and tricks for efficiently processing strings and regular expressions.

### String Concatenation

String concatenation is a common task for us to build a string, and how to optimize it? For starters, there is more than one way to merge strings

| Method | Example     |
| :------------- | :------------- |
| The `+` operator       | `str = 'a' + 'b' + 'c';`       |
| The `+=` operator       | `str = 'a';`       |
|| `str += 'b';`       |
|| `str += 'c';`       |
|array.join()| `str = ['a', 'b', 'c'].join('');`       |
|string.concat()| `str = 'a';`       |
|| `str = str.concat('b', 'c');`|

All of these methods are fast when concatenating a few strings, nevertheless as the length and number of strings that must be merged increases, some methods start to show their strength.

#### `+` and `+=` Operators

Several techniques maximize the efficiency of these operators.

First, an example.

```js
str += 'one' + 'two';
```

When evaluating this code, four steps are taken:

1. A temporary string is created in memory.
2. The concatenated value "onetwo" is assigned to the temporary string.
3. The temporary string is concatenated with the current value of `str`.
4. The result is assigned to `str`.

But considering the following code, which avoids the temporary string (step 1 and step 2 in the above list), and it will end up running about 10%-40% faster in most browsers:

```js
str += 'one';
str += 'two';
```

In fact, you can get the same performance improvement using one statement like this:

```js
/** equivalent to `str = ((str + 'one') + 'two')` */
str = str + 'one' + 'two';
```

Why? That's because the concatenation is based on the `str` itself, and avoid the temporary string, which will allocate some memory. For this reason, if you assign like this, you'll also lose your improvement:

```js
str = 'one' + str + 'two';
```

Apart from IE, browsers try to expand the memory allocation for the string on the left of an expression and simply copy the second string to the end of it. So, in that browsers, it's recommended not to copy a long string, while there is a short one.

```js
var s1 = 'one';
var s3 = 'three';

/** not `var s = s1 + s3;` */
var s = s3 + s1;
```

These techniques don't apply to IE. They have little, if any, effect in IE8 and can actually make things slower in IE7 and earlier.

In IE8's implementation, concatenating strings merely stores references to the existing string parts that compose the new string, and when you actually use the concatenated string, it starts to copy and replace the previous references so that you can use it anytime.

> IE8'S implementation can throw off synthetic benchmarks, makin concatenation appear faster than it really is, unless you force it to occur.

IE7 has an earlier use an inferior (較次的) implementation of concatenation, in which each pair of concatenated strings must always be copied to a new memory location. Then, considering `largeStr = largeStr + s1 + s2;`, the variable `largeStr` will be copied twice in this case. Conversely, `largeStr += s1 + s2;` will be faster because IE7 and earlier browsers will firstly concatenate two small string `s1` and `s2`, then copy the `largeStr` only once.

When all strings concatenated are compile-time constants, Firefox automatically merges them at compile time:

```js
function folding() {
    var str = 'compile' + 'time' + 'folding';
    str += 'this' + 'works' + 'too';
    str = str + 'but' + 'not' + 'this';
}

console.log(foldingDemo.toString());
/** =>
 * function folding() {
 * 		var str = 'compiletimefolding';
 * 		str = 'thisworkstoo';
 * 		str = str + 'but' + 'not' + 'this';
 * }
 */
```

Since we have not often built strings from compile-time constants, it doesn't help very often at all.

> The YUI Compressor performs this optimization at build time.

#### Array Joining

The `Array.prototype.join` method can be used to merge all elements of an array into a string and accepts a separator string to insert between each element. By passing an empty string, you can perform a simple concatenation of all elements in an array.

In most browsers, using this way to concatenate strings is slower than other methods, but is the only efficient way to concatenate lots of strings in IE7 and earlier. To improve that, we're going to have a simple task:

Considering the following code:

```js
var str = 'I\'m a thirty-five character string';
var newStr = '';
var appends = 5000;

while (appends--) {
    newStr += str;
}
```

With changing the value of `appends`, we can have a statistic for how long this task will complete.

| Appends (times)   | 5,000     |10,000|15,000|20,000
| :------------- | :------------- |
| Time (ms)       | 226       |3,955|15,537|32,352

How about using array joining like this:

```js
var str = 'I\'m a thirty-five character string';
var strs = [];
var newStr;
var appends = 5000;

while (appends--) {
    strs[strs.lenght] = str;
}

newStr = strs.join('');
```

| Appends (times)   | 5,000     |10,000|15,000|20,000
| :------------- | :------------- |
| Time (ms)       | 10       |20|30|40

Apparently, the approach of using array joining has reduced so much time to complete this task. Why? IE7's native concatenation algorithm requires that the browser repeatedly copy and allocate memory for larger and larger strings each time through the loop. It's allocations that waste so much time.

#### `String.prototype.concat`

The `String.prototype.concat` is an convenient method, which accepts any number of arguments and appends each to the string.

```js
/** append one string */
str = str.concat(s1);

/** append three strings */
str = str.concat(s1, s2, s3);

/** using list and `apply` */
str = String.prototype.concat.apply(str, array);
```

Everything has two coins, and `concat` has paid for its convenience. `concat` is a little slower than simple `+` and `+=` operations in most cases, and can be very slower in IE, Opera, and Chrome. The reason is same as using `+` and `+=` when building large strings in IE7 and earlier.

### Regular Expression Optimization

Incautiously crafted regexes can be a major performance bottleneck, but there is a lot you can do to improve regex efficiency. Just because two regexes match the same text does not mean they do at the same speed.

#### How Regular Expressions Work

Before focusing on the improvement of performance, it's important to understand how regular expressions work.

- Step 1: Compilation

    When you create a regex object (using a regex literal or `RegExp` object), the browser will checks your pattern for errors and then converts it into a native code routine that is used to actually perform matches. (**If you assign the regex to a local variable, you can avoid performing this step more than once**)

- Step 2: Setting the starting position

    When a regex is firstly put to use, the first step is to determine the position within the target string, where to search (the start of the string or the position specified by the regex's `lastIndex` property).

    When a regex has succeed or failed to match, the position will be the next one character after where the last attempt started.

    Optimizations that browser makers build into their regex engines can help avoid a lot of unnecessary work in this step.

    - If a regex starts with `^`, IE and Chrome can usually determine that a match cannot be found after the start of a string and avoid foolishly searching subsequent positions.
    - If all possible matches contain `x` as the third character, recent version of Chrome will determine this, quickly search for the next `x`, and set the starting position two characters back from where it's found.
    - ...

- Step 3: Matching each regex token

    Since the regex has known where to start, it steps through the text and the regex pattern. When a particular token failed to match, the regex tries to **backtrack** to a prior point in the match attempt and follow other possible paths through the regex.

- Step 4: Success or failure

    If a complete match is found at the current position in the string, the regex declares success.

    If all possible paths through the regex has been attempted but a match was not found, the regex engine goes back to step 2 and try again at the next one character.

    Only after cycling each character in the string and no matches have been found does the regex declare overall failure.

#### Understanding backtracking

Backtracking is a fundamental component of regexes' matching process, but it's, however, computationally expensive and can easily get out of hand if you're not careful.

For each quantifier and alternation, a **decision** must be made about how to proceed. With a qualifier (such as `*`, `+?`, or `{2,}`), the regex must decide when to try matching additional characters. With alternation (via the `|` operator), it must also try one option from those available.

Each time the regex makes such a decision, it remembers the other options to return to later if necessary. If the chosen option can not find a match or anything later in the regex fails, the regex will backtrack to the last decision point where untried options remain and chooses one. This is the process of **backtracking**.

##### **Alternation and backtracking**

Consider the following case:

```js
/h(ello|appy) hippo/.test('hello there, happy hippo');
```

There are two main processes of backtracking we should focus on:

- Match attempt at character 1:

    ![case1](./case1.png)

- Match attempt at character 14:

    ![case2](./case2.png)

##### **Repetition and backtracking**

The next case shows how backtracking works with repetition quantifier.

```js
/<p>.*<\/p>/.test('<p>Para 1.</p><img src="small.jpg" /><p>Para 2.</p><div>Div. </div>');
```

This regex will firstly match the whole string from character 4 within the dot `.` qualifier, and then try backtracking to match `<`. Since `</` has been matched at the `</div>` tag, the character `p` does not match the character `d`. So, it still try backtracking continually until it match `</p>` after the string "Para 2.". Therefore, the matched result should be "**&lt;p&gt;Para 1.&lt;/p&gt;&lt;img src="small.jpg" /&gt;&lt;p&gt;Para 2.&lt;/p&gt;**".

If you want to change the regex to match individual paragraph, you can replace the greedy quantifier `*` with the lazy one `*?`. With the lazy quantifier, the regex engine will skip matching `.*?` and directly try to match `</p>`. If it fails, it will backtrack to match the next fewest number of characters, and finally match "**&lt;p&gt;Para 1.&lt;/p&gt;**".

However, if matching the same target with producing the same result, using lazy quantifier should be slower than the greedy one:

Target:|**&lt;p&gt;Para 1.&lt;\\/p&gt;**
:------|:-------
Greedy quantifier|Lazy quantifier:
**/&lt;p&gt;.&#42;&lt;\\/p&gt;/i**|**/&lt;p&gt;.&#42;?&lt;\\/p&gt;/i**
<ol><li>&lt;</li><li>&lt;p</li><li>&lt;p&gt;</li><li>&lt;p&gt;Para 1.&lt;/p&gt;</li><li>&lt;p&gt;Para 1.&lt;/p&gt;  <strong>[backtrack]</strong></li><li>&lt;p&gt;Para 1.&lt;/p</li><li>&lt;p&gt;Para 1.&lt;/p <strong>[backtrack]</strong></li><li>&lt;p&gt;Para 1.&lt;/</li><li>&lt;p&gt;Para 1.&lt;/ <strong>[backtrack]</strong></li><li>&lt;p&gt;Para 1.&lt;</li><li>&lt;p&gt;Para 1.&lt; <strong>[backtrack]</strong></li><li>&lt;p&gt;Para 1.</li><li>&lt;p&gt;Para 1.&lt;</li><li>&lt;p&gt;Para 1.&lt;/</li><li>&lt;p&gt;Para 1.&lt;/p</li><li>&lt;p&gt;Para 1.&lt;/p&gt; <strong>[success]</strong></li></ol>|<ol><li>&lt;</li><li>&lt;p</li><li>&lt;p&gt;</li><li>&lt;p&gt; <strong>[zero-length match]</strong></li><li>&lt;p&gt; <strong>[backtrack]</strong></li><li>&lt;p&gt;P</li><li>&lt;p&gt;P <strong>[backtrack]</strong></li><li>&lt;p&gt;Pa</li><li>&lt;p&gt;Pa <strong>[backtrack]</strong></li><li>&lt;p&gt;Par</li><li>&lt;p&gt;Par <strong>[backtrack]</strong></li><li>&lt;p&gt;Para</li><li>&lt;p&gt;Para <strong>[backtrack]</strong></li><li>&lt;p&gt;Para&nbsp;</li><li>&lt;p&gt;Para&nbsp; <strong>[backtrack]</strong></li><li>&lt;p&gt;Para 1</li><li>&lt;p&gt;Para 1 <strong>[backtrack]</strong></li><li>&lt;p&gt;Para 1.</li><li>&lt;p&gt;Para 1.&lt;</li><li>&lt;p&gt;Para 1.&lt;/</li><li>&lt;p&gt;Para 1.&lt;/p</li><li>&lt;p&gt;Para 1.&lt;/p&gt; <strong>[success]</strong></li></ol>

#### Runaway backtracking

When a regular expression cost browsers seconds, minutes, or longer to execute, the problem is most likely a bad case of runaway backtracking. Consider the following regex which is mainly used to match an entire HTML file:

**/&lt;html&gt;[\\s\\S]&#42;?&lt;head&gt;[\\s\\S]&#42;?&lt;title&gt;[\\s\\S]&#42;?&lt;\\/title&gt;[\\s\\S]&#42;?&lt;\\/head&gt;[\\s\\S]&#42;?&lt;body&gt;[\\s\\S]&#42;?&lt;\\/body&gt;[\\s\\S]&#42;?&lt;\\/html&gt;/**

This regex works fine when matching a suitable HTML string, but it turns ugly when the string is missing one or more required tags, such as `</html>`, `</body>`, or `</head>`, as the `[\s\S]*?` will expands to the end of the string more than once. Therefore, we have to use another more specific regular expression for optimization:

**/&lt;html&gt;(?:(?!&lt;head&gt;)[\\s\\S])&#42;&lt;head&gt;(?:(?!&lt;title&gt;)[\\s\\S])&#42;&lt;title&gt;(?:(?!&lt;\\/title&gt;)[\\s\\S])&#42;&lt;\\/title&gt;(?:(?!&lt;\\/head&gt;)[\\s\\S])&#42;&lt;\\/head&gt;(?:(?!&lt;body&gt;)[\\s\\S])&#42;&lt;body&gt;(?:(?!&lt;\\/body&gt;)[\\s\\S])&#42;&lt;\\/body&gt;(?:(?!&lt;\\/html&gt;)[\\s\\S])&#42;&lt;\\/html&gt;/**

Even if the regex has removed the potential for runaway backtracking and allowed to fail at matching incomplete HTML strings in linear time, it still has some problems of efficiency above repeating a lookahead for each matched character.

Some regex flavors, including .NET, Java, and Perl, support a feature called **atomic grouping**. As soon as a regex exit such an atomic group, any backtracking positions within the group are thrown away, which means that we can reduce the times of backtracking. However, in JavaScript, we need to use another way to emulate (模擬) atomic groups by using lookahead and backreferences.

**/(?=(pattern to make atomic))\\1/**

So the resolution should be changed like this:

**/&lt;html&gt;(?=([\\s\\S]&#42;?&lt;head&gt;))\\1(?=([\\s\\S]&#42;?&lt;title&gt;))\\2(?=([\\s\\S]&#42;?&lt;\\/title&gt;))\\3(?=([\\s\\S]&#42;?&lt;\\/head&gt;))\\4(?=([\\s\\S]&#42;?&lt;body&gt;))\\5(?=([\\s\\S]&#42;?&lt;\\/body&gt;))\\6[\\s\\S]&#42;?&lt;\\/html&gt;/**

Now, if there is no trailing `</html>` and the last `[\s\S]*?` expands to the end of the string, the regex immediately fails because there are no backtracking points to return to.
